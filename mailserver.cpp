static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


class MailServer {
	public:	
		std::string inbox(); 
		std::string getemail(int msgnum);
		void deletemail(int msgnum);
		MailServer(char *user,char *pass);
	private:
		char *username;
		char *password;	
};


MailServer::MailServer(char *user,char *pass){
	username = user;
	password = pass;
}

std::string MailServer::inbox(){
    CURL *curl;
    CURLcode res;
	std::string readBuffer;
    
    //inicializacion
    curl = curl_easy_init();


    //login
    curl_easy_setopt(curl,CURLOPT_USERNAME,username);
    curl_easy_setopt(curl,CURLOPT_PASSWORD,password);
     
	std::string m_popsAccount = "pop3s://pop.gmail.com:995/";  
    curl_easy_setopt(curl, CURLOPT_URL, m_popsAccount.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); 

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,WriteCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0); 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    //some servers needs this validation
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	
    res = curl_easy_perform(curl); 

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
    }
    else 
    {
        //printf("bundasbundasbundas\n");
        //std::cout << readBuffer << std::endl;
        //printf("bundasbundasbundas\n");
  }
    curl_easy_cleanup(curl);
    return readBuffer;
}

std::string MailServer::getemail(int msgnum){
	CURL *curl;
    CURLcode res;
	std::string readBuffer;
    
    //inicializacion
    curl = curl_easy_init();


    //login
    curl_easy_setopt(curl,CURLOPT_USERNAME,username);
    curl_easy_setopt(curl,CURLOPT_PASSWORD,password);
    
	std::string m_popsAccount = SSTR( "pop3s://pop.gmail.com:995/" << msgnum );
    //std::cout << m_popsAccount << std::endl;
	
	curl_easy_setopt(curl, CURLOPT_URL, m_popsAccount.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); 
	
	
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,WriteCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0); 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    //some servers needs this validation
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	
    res = curl_easy_perform(curl); 

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
    }
    else 
    {
        //printf("bundasbundasbundas\n");
        //std::cout << readBuffer << std::endl;
        //printf("bundasbundasbundas\n");
  }
    curl_easy_cleanup(curl);
    return readBuffer;
}

void MailServer::deletemail(int msgnum){
	CURL *curl;
    CURLcode res;
	std::string readBuffer;
    
    //inicializacion
    curl = curl_easy_init();


    //login
    curl_easy_setopt(curl,CURLOPT_USERNAME,username);
    curl_easy_setopt(curl,CURLOPT_PASSWORD,password);
    
	std::string m_popsAccount = SSTR( "pop3s://pop.gmail.com:995/" << msgnum );
    std::cout << m_popsAccount << std::endl;
	
	curl_easy_setopt(curl, CURLOPT_URL, m_popsAccount.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); 
    
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELE");

    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

    //some servers needs this validation
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	
    res = curl_easy_perform(curl); 

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
    }
    else 
    {
        //printf("bundasbundasbundas\n");
        //std::cout << readBuffer << std::endl;
        //printf("bundasbundasbundas\n");
  }
    curl_easy_cleanup(curl);
}

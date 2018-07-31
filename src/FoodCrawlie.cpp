/*
 * FoodCrawlie: A simple webcrawler for recipe websites to extract the HTML
 * All webrequests will use libcURL.
 * This is the main entry point for the program.
 * 
 */
#include <string>
#include <iostream>
#include <fstream>
#include "include\curl\curl.h"

using namespace std;

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);




int main()
{
    CURL *curl;
    CURLcode result;
    ofstream out;
    /* Global Initialization for libcURL with default parameter - this inits WIN32 socket libs & SSL*/
    curl_global_init(CURL_GLOBAL_DEFAULT);



    curl = curl_easy_init();
    if (curl) {
        string s;
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.allrecipes.com/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        /* Perform the request, res will get the return code */
        result = curl_easy_perform(curl);
        /* Check for errors */
        if (CURLE_OK != result)
            fprintf(stderr, "HTTP REQ failed: %s\n",
                curl_easy_strerror(result));
        cout << s << endl;

        out.open("test.html");
        out << s;
        out.close();
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    /* Global Cleanup for libcURL */
    curl_global_cleanup();
    return 0;
}

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



/*
 * FoodCrawlie: A simple webcrawler for recipe websites to extract the HTML
 * All webrequests will use libcURL.
 * This is the main entry point for the program.
 * 
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "include\curl\curl.h"

//using namespace std;

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
bool doesStringContainHook(std::string s);
size_t getRecipeURL(std::string s, std::string* url);

bool hookFound = false; /* this is a global variable to indicate the recipe hook is found */
bool recipeProcessed = false; /* global flag to indicate if a recipe has been processed, this is used after the hookFound */
std::string recipeHook = "fixed-recipe-card__h3"; /* The word to search for to indicate that a recipe has been found*/
std::string recipeUrlHook = "href="; /* This is the word that indicates it's the URL to the recipe after the recipeHook has been found */
std::string titleHook = "fixed-recipe-card__title-link"; /* The word to search for to get the title of the recipe*/

int main()
{
    int numberOfPages = 100;
    CURL *curl;
    CURLcode result;
    std::ofstream out;
    /* Global Initialization for libcURL with default parameter - this inits WIN32 socket libs & SSL*/
    curl_global_init(CURL_GLOBAL_DEFAULT);



    curl = curl_easy_init();
    if (curl) {
        std::string s;
        /* Set the website URL */
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.allrecipes.com/");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        for (int i = 0; i < numberOfPages; i++)
        {

        }

        /* Perform the request, res will get the return code */
        result = curl_easy_perform(curl);
        /* Check for errors */
        if (CURLE_OK != result)
            fprintf(stderr, "HTTP REQ failed: %s\n",
                curl_easy_strerror(result));

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

    std::istringstream sstream(std::string((char*)contents));
    std::string s;
    while (std::getline(sstream, s))
    {
        /******************* 
        THIS IS FOR ALLRECIPES ONLY
        *********************/
        hookFound = doesStringContainHook(s);
        /* After finishing processing a recipe, the title should be written */
        if (recipeProcessed)
        {
            recipeProcessed = false;
            hookFound = false;
        }

        /* Next up should be */
        if (hookFound)
        {

        }
        
    }
    sstream.str(std::string()); /* Clear the stringstream to be empty string */
    //std::cout << s << std::endl;
    return size * nmemb;
}

bool doesStringContainHook(std::string s)
{
    /* search whole string for hook and return true if found */
    return ((s.find(recipeHook, 0) != std::string::npos) ? true : false);
}

bool getRecipeURL(std::string s, std::string* url)
{

    bool urlInString = ((s.find(recipeUrlHook, 0) != std::string::npos ? true : false));

    if (urlInString)
    {
        *url = s; //TODO, temporarily set URl string
    }
    else
    {
    }
    return urlInString;
   
}


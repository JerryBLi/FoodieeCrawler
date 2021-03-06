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
#include "include\Recipe.h"

//using namespace std;

static size_t mainPageCallback(void *contents, size_t size, size_t nmemb, void *userp);
static size_t recipeCallback(void *contents, size_t size, size_t nmemb, void *userp);
bool doesStringContainHook(std::string s);
bool getRecipeURL(std::string s, std::string* url);
CURLcode retrieveRecipe(std::string url);

bool hookFound = false; /* this is a global variable to indicate the recipe hook is found */
bool recipeProcessed = false; /* global flag to indicate if a recipe has been processed, this is used after the hookFound */
std::string recipeHook = "fixed-recipe-card__h3"; /* The word to search for to indicate that a recipe has been found*/
std::string recipeUrlHook = "href=\""; /* This is the word that indicates it's the URL to the recipe after the recipeHook has been found */
std::string titleHook = "<span class=\"fixed-recipe-card__title-link\">"; /* The word to search for to get the title of the recipe*/

std::string currentRecipeTitle;
std::string currentRecipeUrl;


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
        std::string url("https://www.allrecipes.com/");
        /* Set the website URL */
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mainPageCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        for (int i = 0; i < numberOfPages; i++)
        {

        }

        /* Perform the request, res will get the return code */
        result = curl_easy_perform(curl);
        /* Check for errors */
        if (CURLE_OK != result)
            fprintf(stderr, "HTTP REQ failed: %s\n", curl_easy_strerror(result));

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

static size_t mainPageCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    //((std::string*)userp)->append((char*)contents, size * nmemb);

    std::istringstream sstream(std::string((char*)contents));
    std::string s;
    while (std::getline(sstream, s))
    {
        /******************* 
        THIS IS FOR ALLRECIPES ONLY
        *********************/

        /* If a recipe has been found, reset flags to search again */
        if (recipeProcessed)
        {
            recipeProcessed = false;
            hookFound = false;
        }

        /* If we find a hook for a recipe, we need to extract the URL and then get the title */
        if (hookFound)
        {
            std::string *recipeUrl = new std::string();
            /* Get URL*/
            if (getRecipeURL(s, recipeUrl))
            {
                std::cout << *recipeUrl << std::endl;
                //TODO - use a separate thread to retrieve the recipe
                retrieveRecipe(*recipeUrl);
                recipeProcessed = true;
            }
        }
        else
        {
            hookFound = doesStringContainHook(s);
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
    int startPosition;
    int endPosition;
    bool urlInString = (((startPosition = s.find(recipeUrlHook, 0)) != std::string::npos) ? true : false);

    /* if the string contains the url hook */
    if (urlInString)
    {
        /* The URL is in this string, we have to parse it out. It will be between the quotes in the href */
        startPosition += recipeUrlHook.length(); /* The startPos is the position of the first character, we add the rest of the hook so the location starts on the recipe URL */
        endPosition = s.find("\"", startPosition); /* find the end position of the URL from the first quotation mark after the start of the URL */
        *url = s.substr(startPosition, (endPosition - startPosition)); /* get the URL from the line; start at the start position and end after the number of characters */
    }
    return urlInString;
   
}


CURLcode retrieveRecipe(std::string url)
{
    CURL *curl;
    CURLcode result;

    result = CURLE_FAILED_INIT;

    curl = curl_easy_init();

    if (curl) {
        std::string s;
        /* Set the website URL */
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, recipeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        /* Perform the request, res will get the return code */
        result = curl_easy_perform(curl);
        /* Check for errors */
        if (CURLE_OK != result)
            fprintf(stderr, "HTTP REQ failed: %s\n", curl_easy_strerror(result));

        Recipe r(s);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return result;
}

static size_t recipeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{

    ((std::string*)userp)->append((char*)contents, size * nmemb);

    return size * nmemb;
}

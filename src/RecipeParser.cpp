
#include "include\MeasurementUnit.h"
#include "include\Ingredient.h"
#include <string>

using namespace std;

/* We need to specify the "hooks" to use to parse the HTML. We would call a request to the main page (aka www.allrecipes.com) and then find the CSS hook for an individual recipe and call that URL. From that HTML, we will find the "hooks" for the ingredients and steps */

/* Once we create a recipe object from the HTML, we must serialize (write it to a file) to a JSON file (or any other file type) and those will be stored in our database */
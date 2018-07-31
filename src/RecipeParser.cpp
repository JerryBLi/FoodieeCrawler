
#include "include\MeasurementUnit.h"
#include "include\Ingredient.h"
#include <string>

using namespace std;





class Recipe
{
public:
    Recipe()
    {

    }
    Recipe(string s)
    {

    }

private:
    int numberOfIngredients;
    int numberOfSteps;
    string *steps;
    Ingredient *ingredients;

};




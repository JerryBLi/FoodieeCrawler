
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

class Ingredient
{
public:
    
    string toString()
    {

    }
private:
    int amount;
    MeasurementUnit unit;
    string ingredientName;
    string rawString; 
};

enum MeasurementUnit
{
    /* No measurement specified or "to taste" or unknown */
    none,
    /* whole items*/
    piece,
    /* dry ingredient measurements */
    teaspoon,
    tablespoon,
    cup,
    /* liquid measurements */
    fluid_ounce,
    pint,
    quart,
    gallon
};
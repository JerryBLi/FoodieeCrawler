#include "include\Recipe.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Recipe::parseRecipe(std::string s)
{
    //TODO - find a better place for these hooks
    titleHook = "";
    ingredientHook = "recipeIngredient";
    RecipeStepHook = "recipe-directions__list--item";

    std::stringstream sstream(s);
    std::string t;

    /* Parse the html line by line to find recipe hooks such as title, ingredients, and steps */
    while (std::getline(sstream, t))
    {
        parseLine(t);
    }

    std::ofstream out;
    out.open("recipetest.html");
    out << s;
    out.close();
}

int Recipe::getNumberOfIngredients() { return numberOfIngredients; }

int Recipe::getNumberOfSteps() { return numberOfSteps; }

double Recipe::getNumberOfServings() { return servings; }

std::string Recipe::getRecipeName() { return recipeName; }

std::vector<std::string> Recipe::getRecipeSteps() { return steps; } 

std::vector<Ingredient> Recipe::getIngredients() { return ingredients; }

void Recipe::setRecipeName(std::string recipeName) { this->recipeName = recipeName; }

void Recipe::setRecipeSteps(std::vector<std::string> steps) { this->steps = steps; }

void Recipe::setRecipeIngredients(std::vector<Ingredient> ingredients) { this->ingredients = ingredients; }

void Recipe::addRecipeStep(std::string step) { this->steps.push_back(step); }

void Recipe::addRecipeIngredient(Ingredient ingredient) { this->ingredients.push_back(ingredient); }

void Recipe::removeRecipeStep(int stepNumber) { this->steps.erase(this->steps.begin + stepNumber); }

void Recipe::removeRecipeIngredient(int ingredientNumber) { this->ingredients.erase(this->ingredients.begin + ingredientNumber);  }

void Recipe::clearRecipeSteps() { this->steps.clear(); }

void Recipe::clearIngredientSteps() { this->ingredients.clear(); }

std::string Recipe::getRecipeStepAt(int i) { return steps.at(i); }

Ingredient Recipe::getRecipeIngredientAt(int i) { return ingredients.at(i); }


void Recipe::parseLine(std::string s)
{
    if (containsIngredientHook(s))
    {
        getIngredient(s);
        numberOfIngredients++;
    }
    if (containsRecipeStepHook(s))
    {
        getRecipeStep(s);
        numberOfSteps++;
    }
}

/* Checks whether or not the current string has the hook for the title */
bool Recipe::containsTitleHook(std::string s)
{  
    return ((s.find(titleHook, 0) != std::string::npos) ? true : false);
}

/* Checks whether or not the current string has the hook for an ingredient */
bool Recipe::containsIngredientHook(std::string s)
{
    return ((s.find(ingredientHook, 0) != std::string::npos) ? true : false);
}

/* Checks whether or not the current string has the hook for a recipe step */
bool Recipe::containsRecipeStepHook(std::string s)
{
    return ((s.find(RecipeStepHook, 0) != std::string::npos) ? true : false);
}

void Recipe::getIngredient(std::string s)
{
    int hookStartPosition = s.find(ingredientHook, 0);
    int valueStartPosition = s.find(">", hookStartPosition)+1; /* +1 for the beginning of the ingredient */
    int valueEndPosition = s.find("<", hookStartPosition); /* Find the end of the ingredient, it'll end with an HTML tag so that's why we're seaching for a "<" */
    std::string value = s.substr(valueStartPosition, (valueEndPosition-valueStartPosition)); /* Stop forgetting that the substr() func takes the beginning and length as arguments! */
    std::cout << value << std::endl;
    //TODO - by this point, the string value is the string representation of an ingredient
}

void Recipe::getRecipeStep(std::string s)
{
    int hookStartPosition = s.find(RecipeStepHook, 0);
    int valueStartPosition = s.find(">", hookStartPosition)+1; /* +1 for the beginning of the recipe step without the ">" */
    int valueEndPosition = s.find("<", hookStartPosition); /* HTML tag will end the recipe step */
    std::string value = s.substr(valueStartPosition, (valueEndPosition - valueStartPosition));
    
}

/* Find the value from a string from a hook. Because this is HTML, it will always be nested between ">" and "<" */
std::string Recipe::getValueFromString(std::string s)
{
    int startPosition;
    int EndPosition;
    return std::string();
}



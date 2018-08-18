#include "include\Recipe.h"
#include <iostream>
#include <fstream>

void Recipe::parseRecipe(std::string s)
{
    //TODO - find a better place for these hooks



    std::ofstream out;
    out.open("recipetest.html");
    out << s;
    out.close();
}

int Recipe::getNumberOfIngredients()
{
    return 0;
}

int Recipe::getNumberOfSteps()
{
    return 0;
}

double Recipe::getNumberOfServers()
{
    return 0.0;
}

std::string Recipe::getRecipeName()
{
    return std::string();
}

std::vector<std::string> Recipe::getRecipeSteps()
{
    return std::vector<std::string>();
}

std::vector<Ingredient> Recipe::getIngredients()
{
    return std::vector<Ingredient>();
}

void Recipe::setRecipeName(std::string recipeName)
{
}

void Recipe::setRecipeSteps(std::vector<std::string> steps)
{
}

void Recipe::setRecipeIngredients(std::vector<Ingredient> ingredients)
{
}

void Recipe::addRecipeStep(std::string step)
{
}

void Recipe::addRecipeIngredient(Ingredient ingredient)
{
}

void Recipe::removeRecipeStep(int stepNumber)
{
}

void Recipe::removeRecipeIngredient(int ingredientNumber)
{
}

void Recipe::clearRecipeSteps()
{
}

void Recipe::clearIngredientSteps()
{
}

std::string Recipe::getRecipeStepAt(int i)
{
    return std::string();
}

Ingredient Recipe::getRecipeIngredientAt(int i)
{
    return Ingredient();
}

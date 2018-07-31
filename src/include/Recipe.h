#pragma once
#include "Recipe.h"
#include "Ingredient.h"
#include <string>

/* This is the class representation for a recipe */
class Recipe
{
public:
    Recipe()
    {

    }
    Recipe(std::string s)
    {

    }

private:
    int numberOfIngredients;
    int numberOfSteps;
    std::string *steps;
    Ingredient *ingredients;

};
#pragma once
#include "Recipe.h"
#include "Ingredient.h"
#include "NutritionalInformation.h"
#include <string>
#include <vector>

/* This is the class representation for a recipe */
class Recipe
{
public:
    Recipe()
    {

    }
    Recipe(std::string s)
    {
        parseRecipe(s);
    }
  
    void parseRecipe(std::string s);

    /* Getters and Setters*/
    int getNumberOfIngredients();
    int getNumberOfSteps();
    double getNumberOfServings();
    std::string getRecipeName();
    std::vector<std::string> getRecipeSteps();
    std::vector<Ingredient> getIngredients();

    void setRecipeName(std::string recipeName);
    void setRecipeSteps(std::vector<std::string> steps);
    void setRecipeIngredients(std::vector<Ingredient> ingredients);

    /* Auxillary functions to help create/get recipe */
    void addRecipeStep(std::string step);
    void addRecipeIngredient(Ingredient ingredient);
    void removeRecipeStep(int stepNumber);
    void removeRecipeIngredient(int ingredientNumber);
    void clearRecipeSteps();
    void clearIngredientSteps();

    std::string getRecipeStepAt(int i);
    Ingredient getRecipeIngredientAt(int i);



private:
    int numberOfIngredients;
    int numberOfSteps;
    double servings;
    std::string recipeName;
    std::vector<std::string> steps;
    std::vector<Ingredient> ingredients;

    /* helper variables */
    std::string titleHook;
    std::string ingredientHook;
    std::string RecipeStepHook;

    /* helper functions */
    void parseLine(std::string s);
    bool containsTitleHook(std::string s);
    bool containsIngredientHook(std::string s);
    bool containsRecipeStepHook(std::string s);
    void getIngredient(std::string s);
    void getRecipeStep(std::string s);
    std::string getValueFromString(std::string s);
};
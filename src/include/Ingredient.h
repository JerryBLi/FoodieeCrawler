#pragma once
#include <string>
#include "MeasurementUnit.h"

/* This is the class representation of an Ingredient. Each ingredient has an amount, a unit, and a ingredient name. */
class Ingredient
{
public:
    /* Default constructor */
    Ingredient();
    /* Constructor where you can pass in the string and it'll parse the ingredient into the amount, unit, and name */
    Ingredient(std::string s);
    /* Constructor where you specify the amount, unit, and name */
    Ingredient(double amount, MeasurementUnit unit, std::string ingredientName);
    std::string toString();
    /* Getters */
    double getAmount();
    MeasurementUnit getUnit();
    std::string getIngredientName();

    /* Setters */
    void setAmount(double amount);
    void setUnit(MeasurementUnit unit);
    void setIngredientName(std::string ingredientName);

private:
    double amount;
    MeasurementUnit unit;
    std::string ingredientName;
    std::string rawString;
};
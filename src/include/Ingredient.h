#pragma once
#include <string>
#include "MeasurementUnit.h"

class Ingredient
{
public:
    std::string toString();

private:
    int amount;
    MeasurementUnit unit;
    std::string ingredientName;
    std::string rawString;
};
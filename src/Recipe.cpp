#include "include\Recipe.h"
#include <iostream>
#include <fstream>

void Recipe::parseRecipe(std::string s)
{
    std::ofstream out;
    out.open("recipetest.html");
    out << s;
    out.close();
}

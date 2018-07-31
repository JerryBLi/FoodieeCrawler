#pragma once
/* This is the enum to specify the measurement unit. If none of them match, then it should be set to none */
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
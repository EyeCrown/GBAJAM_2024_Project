#pragma once 

#include "bn_fixed.h"

namespace mygame
{
    struct vector
    {
        bn::fixed x;
        bn::fixed y;
        bn::fixed z;

        vector() : x(0), y(0), z(0) {}
        vector(bn::fixed xValue, bn::fixed yValue, bn::fixed zValue) : x(xValue), y(yValue), z(zValue) {}
    };
}
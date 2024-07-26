#pragma once 

#include "bn_fixed.h"

namespace mygame
{
    struct vector2
    {
        bn::fixed x;
        bn::fixed y;

        vector2() : x(0), y(0) {}
        vector2(bn::fixed xValue, bn::fixed yValue) : x(xValue), y(yValue) {}
    };

    struct vector3
    {
        bn::fixed x;
        bn::fixed y;
        bn::fixed z;

        vector3() : x(0), y(0), z(0) {}
        vector3(bn::fixed xValue, bn::fixed yValue, bn::fixed zValue) : x(xValue), y(yValue), z(zValue) {}

        bn::fixed dot(const vector3 other)
        {
            return x * other.x + y * other.y + z * other.z;
        }

        vector3& operator+(const vector3 other) 
        {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        vector3& operator-(const vector3 other) 
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }
    };

    struct matrix 
    {

    };
}
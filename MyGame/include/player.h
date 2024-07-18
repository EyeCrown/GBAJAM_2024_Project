#pragma once

#include "bn_fixed.h"

namespace mygame
{
    struct camera
    {
        bn::fixed x = 0;
        bn::fixed y = 32;
        bn::fixed z = 0;
        int phi = 0;
        int cos = 0;
        int sin = 0;
    };
    
    class Player 
    {
        public:

        bn::fixed xPos;
        bn::fixed zPos;
        int phi = 0;
        int cos = 0;
        int sin = 0;

        mygame::camera camera;

        Player(bn::fixed xStart, bn::fixed zStart);

        void _update();

        void _update_dir_z(bn::fixed& dir_z);

        void _move();

        void _setPosition(bn::fixed xValue, bn::fixed zValue);
        void _rotate();

        void _update_camera_data();

    
        private:

        const bn::fixed mOffsetCameraX = 0;  // 5.0
        const bn::fixed mOffsetCameraZ = 1;  // 5.0

    };
}

    
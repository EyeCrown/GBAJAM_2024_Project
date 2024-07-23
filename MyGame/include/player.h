#pragma once

#include "bn_fixed.h"

#include "bn_sprite_actions.h"

#include "bn_sprite_items_player_body.h" // Player sprite
#include "bn_sprite_items_red_sprite.h"

#include "mg_vector.h"

namespace mygame
{
    struct camera
    {
        bn::fixed x = 0;
        bn::fixed y = 32;
        bn::fixed z = 0;

        mygame::vector position;
        mygame::vector direction;

        int phi = 0;
        int cos = 0;
        int sin = 0;

        
    };
    
    class Player 
    {
        public:

        mygame::vector position;

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

        bn::sprite_ptr mSprite = bn::sprite_items::red_sprite.create_sprite(0,100);
    };
}

    
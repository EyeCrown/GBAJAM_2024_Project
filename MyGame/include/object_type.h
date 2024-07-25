#pragma once

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "player.h"

namespace mygame
{

    class Object
    {
        public:
        Object(bn::fixed x, bn::fixed z, bn::sprite_ptr* sprite);

        
        mygame::vector3 position { mygame::vector3(0, 0, 0) };

        bn::sprite_ptr spriteObj;

        void _update(mygame::Player* player);

        private:


        bn::fixed xSpritePos { 0 };
        bn::fixed ySpritePos { 0 };
    };

}
#pragma once

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "player.h"

namespace mygame
{

    class Object
    {
        public:
        Object();
        Object(bn::fixed x, bn::fixed z, bn::sprite_ptr* sprite);

        bn::sprite_ptr spriteObj;

        void _update(mygame::Player* player);

        private:
        bn::fixed xPos { 0 };
        bn::fixed zPos { 0 };

        bn::fixed xSpritePos { 0 };
        bn::fixed ySpritePos { 0 };
    };

}
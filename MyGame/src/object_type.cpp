#include "object_type.h"

namespace mygame
{
    Object::Object(bn::fixed x, bn::fixed z, bn::sprite_ptr* sprite) : 
    xPos(x), zPos(z), spriteObj(*sprite) {}


    void Object::_update(mygame::Player* player)
    {
        bn::fixed sizeSpriteValue = spriteObj.horizontal_scale();

        bn::fixed dist[2] = 
        {
            xPos - player->xPos,
            zPos - player->zPos
        };

        bn::fixed norm = (dist[0] * dist[0]) + (dist[1] * dist[1]);

        bn::fixed distMin = 0.1, distMax = 1000;

        sizeSpriteValue = norm * (distMax - bn::max(distMin, bn::min(norm, distMax))); 

        if (sizeSpriteValue <= 0)
        {
            //spriteObj.set_visible(false);
        }
        else
        {
            spriteObj.set_visible(true);
            spriteObj.set_horizontal_scale(sizeSpriteValue);
            spriteObj.set_vertical_scale(sizeSpriteValue);
        }

        // bn::fixed xPosSpriteValue   = 0;
        // bn::fixed yPosSpriteValue   = 0;
        // spriteObj.set_x(xPosSpriteValue);
        // spriteObj.set_y(yPosSpriteValue);
    }
}
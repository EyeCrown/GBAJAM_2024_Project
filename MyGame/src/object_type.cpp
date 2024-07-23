#include "object_type.h"

namespace mygame
{
    Object::Object(bn::fixed x, bn::fixed z, bn::sprite_ptr* sprite) : 
    xPos(x), zPos(z), spriteObj(*sprite) {}


    void Object::_update(mygame::Player* player)
    {

        bn::fixed vectPlayerToObject[2] = 
        {
            xPos - player->position.x,
            zPos - player->position.z
        };

        bn::fixed distPlayerToObject = (vectPlayerToObject[0] * vectPlayerToObject[0]) + 
                (vectPlayerToObject[1] * vectPlayerToObject[1]); // ||u||² = x² + y²

        bn::fixed distMaxVisible = 30000;
        bn::fixed distClose = 8000;
        bn::fixed sizeSpriteValue;

        if (distPlayerToObject > distMaxVisible)
        {
            spriteObj.set_visible(false);
        }
        else if (distPlayerToObject > distClose)
        {
            spriteObj.set_visible(true);

            sizeSpriteValue = 0.2;
            spriteObj.set_horizontal_scale(sizeSpriteValue); // Put it in function
            spriteObj.set_vertical_scale(sizeSpriteValue);
        }
        else
        {
            spriteObj.set_visible(true);
            sizeSpriteValue = 1 - (distPlayerToObject / distClose);

            sizeSpriteValue *= 2;

            spriteObj.set_horizontal_scale(sizeSpriteValue);
            spriteObj.set_vertical_scale(sizeSpriteValue);
        }

        bn::fixed xPosSpriteValue   = spriteObj.x();
        
        // bn::fixed yPosSpriteValue   = 0;

       



        spriteObj.set_x(xPosSpriteValue);
        // spriteObj.set_y(yPosSpriteValue);
    }
}
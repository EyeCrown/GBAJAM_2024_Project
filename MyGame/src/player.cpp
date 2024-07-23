#include "player.h"

#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_fixed.h"

namespace mygame
{

    Player::Player(bn::fixed xStart, bn::fixed zStart)
    {
        position = mygame::vector(xStart, 0, zStart);
        
        camera.position = mygame::vector(0, 32, 0);

        mSprite = bn::sprite_items::red_sprite.create_sprite(0,0);
    }


    void Player::_update()
    {
        bn::fixed dir_x = 0;
        bn::fixed dir_z = 0;

        _update_dir_z(dir_z);

        if(bn::keypad::b_held())
        {
            camera.position.y -= bn::fixed::from_data(2048);

            if(camera.position.y < 0)
                camera.position.y = 0;
        }
        else if(bn::keypad::a_held())
        {
            camera.position.y += bn::fixed::from_data(2048);
        }

        if(bn::keypad::left_held())
        {
            camera.phi -= 4;

            //body_sprite.set_tiles(bn::sprite_items::player_body.tiles_item().create_tiles(8));

            if(camera.phi < 0)
                camera.phi += 2048;
        }
        else if(bn::keypad::right_held())
        {
            camera.phi += 4;

            //body_sprite.set_tiles(bn::sprite_items::player_body.tiles_item().create_tiles(8));

            if(camera.phi >= 2048)
                camera.phi -= 2048;
        }

        camera.cos = bn::lut_cos(camera.phi).data() >> 4;
        camera.sin = bn::lut_sin(camera.phi).data() >> 4;

        position.x += (0 * camera.cos) - (dir_z * camera.sin);
        position.z += (0 * camera.sin) + (dir_z * camera.cos);

        camera.position.x = position.x + (mOffsetCameraX * camera.cos) - (mOffsetCameraZ * camera.sin);
        camera.position.z = position.z - (mOffsetCameraX * camera.sin) + (mOffsetCameraZ * camera.cos);
    }


    void Player::_update_dir_z(bn::fixed& dir_z)
    {
        if(bn::keypad::down_held())
        {
            dir_z += bn::fixed::from_data(32);
            //body_sprite.set_tiles(bn::sprite_items::player_body.tiles_item().create_tiles(8));
        }
        else if(bn::keypad::up_held())
        {
            dir_z -= bn::fixed::from_data(32);
            //body_sprite.set_tiles(bn::sprite_items::player_body.tiles_item().create_tiles(8));
        }
    }



    void Player::_move()
    {
        //bn::fixed dir_x = 0;
        bn::fixed dir_z = 0;

        if(bn::keypad::down_held())
        {
            dir_z += bn::fixed::from_data(16);
        }
        else if(bn::keypad::up_held())
        {
            dir_z -= bn::fixed::from_data(16);
        }

        position.x += (position.x * camera.cos) - (dir_z * camera.sin);
        position.z += (position.x * camera.sin) + (dir_z * camera.cos);
    }

    void Player::_setPosition(bn::fixed xValue, bn::fixed zValue)
    {
        position.x = xValue;
        position.z = zValue;
    }

    void Player::_rotate()
    {
        if(bn::keypad::left_held())
        {
            phi -= 4;

            if(phi < 0)
            {
                phi += 2048;
            }
        }
        else if(bn::keypad::right_held())
        {
            phi += 4;

            if(phi >= 2048)
            {
                phi -= 2048;
            }
        }

        cos = bn::lut_cos(phi).data() >> 4;
        sin = bn::lut_sin(phi).data() >> 4;
    }
    
    void Player::_update_camera_data()
    {
        bn::fixed dir_x = bn::fixed::from_data(position.x.data()); // - mOffsetCameraX.data());
        bn::fixed dir_z = bn::fixed::from_data(position.z.data()); // - mOffsetCameraZ.data());

        camera.x += (dir_x * cos) - (dir_z * sin);
        camera.z += (dir_x * sin) + (dir_z * cos);
    }

}
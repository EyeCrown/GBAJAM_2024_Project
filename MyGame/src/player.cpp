#include "player.h"

#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_fixed.h"

namespace mygame
{

    Player::Player(bn::fixed xStart, bn::fixed zStart)
    {
        xPos = xStart;
        zPos = zStart;

        //camera = dsd::camera;

        mSprite = bn::sprite_items::red_sprite.create_sprite(0,0);
    }


    void Player::_update()
    {
        bn::fixed dir_x = 0;
        bn::fixed dir_z = 0;

        _update_dir_z(dir_z);

        if(bn::keypad::b_held())
        {
            camera.y -= bn::fixed::from_data(2048);

            if(camera.y < 0)
                camera.y = 0;
        }
        else if(bn::keypad::a_held())
        {
            camera.y += bn::fixed::from_data(2048);
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
        xPos += (dir_x * camera.cos) - (dir_z * camera.sin);
        zPos += (dir_x * camera.sin) + (dir_z * camera.cos);

        camera.x = xPos + (mOffsetCameraX * camera.cos) - (mOffsetCameraZ * camera.sin);
        camera.z = zPos - (mOffsetCameraX * camera.sin) + (mOffsetCameraZ * camera.cos);
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

        // if(bn::keypad::left_held())
        // {
        //     dir_x -= bn::fixed::from_data(16);
        // }
        // else if(bn::keypad::right_held())
        // {
        //     dir_x += bn::fixed::from_data(16);
        // }

        if(bn::keypad::down_held())
        {
            dir_z += bn::fixed::from_data(16);
        }
        else if(bn::keypad::up_held())
        {
            dir_z -= bn::fixed::from_data(16);
        }

        xPos += (xPos * camera.cos) - (dir_z * camera.sin);
        zPos += (xPos * camera.sin) + (dir_z * camera.cos);
    }

    void Player::_setPosition(bn::fixed xValue, bn::fixed zValue)
    {
        xPos = xValue;
        zPos = zValue;
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
        bn::fixed dir_x = bn::fixed::from_data(xPos.data()); // - mOffsetCameraX.data());
        bn::fixed dir_z = bn::fixed::from_data(zPos.data()); // - mOffsetCameraZ.data());

        camera.x += (dir_x * cos) - (dir_z * sin);
        camera.z += (dir_x * sin) + (dir_z * cos);
    }

}
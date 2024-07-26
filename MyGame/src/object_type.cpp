#include "object_type.h"

namespace mygame
{
    Object::Object(bn::fixed x, bn::fixed z, bn::sprite_ptr* sprite) : spriteObj(*sprite) {}

    void Object::_update(mygame::Player* player)
    {
        mygame::vector3 interverted_cam_vect;

        mygame::vector3 pos_minus_camera_pos = position - player->camera.position;

        interverted_cam_vect.x =  pos_minus_camera_pos.dot(player->camera.local_x_axis);
        interverted_cam_vect.y = -pos_minus_camera_pos.dot(player->camera.local_y_axis);
        interverted_cam_vect.z = -pos_minus_camera_pos.dot(player->camera.local_z_axis);

        bn::fixed size_x = spriteObj.horizontal_scale();
        bn::fixed size_y = spriteObj.vertical_scale();

        bn::fixed plan_near = 24;
        bn::fixed plan_far  = 512;

        if (interverted_cam_vect.z < plan_near || plan_far < interverted_cam_vect.z)
        {    break; }

        // update world position
        // _update_world_position()

        // from world space to camera space
        mygame::vector3 position_relative_camera;


        int camera_cos = player->camera.cos;
        int camera_sin = player->camera.sin;



        position_relative_camera.x = (camera_cos * pos_minus_camera_pos.x) - (camera_sin * pos_minus_camera_pos.z);
        position_relative_camera.y = pos_minus_camera_pos.y;
        position_relative_camera.z = 1;
       
        // from camera space to projection space
        // λ = −zc / D  => zc = -1
        mygame::vector3 position_relative_projection = position_relative_camera;


        // TODO: Finish calcul from projection to viewing



        bn::fixed sizeSpriteValue   = spriteObj.x();
        

        spriteObj.set_visible(true);

        sizeSpriteValue = 0.2;
        spriteObj.set_horizontal_scale(sizeSpriteValue); // Put it in function
        spriteObj.set_vertical_scale(sizeSpriteValue);  


        // spriteObj.set_x(xPosSpriteValue);
        // spriteObj.set_y(yPosSpriteValue);
    }
}
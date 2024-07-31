#include "object_type.h"

#include "bn_math.h"

namespace mygame
{
    Object::Object(bn::fixed x, bn::fixed z, bn::sprite_ptr* sprite) : spriteObj(*sprite) {}

    void Object::_update(mygame::Player* player)
    {
        mygame::vector3 interverted_cam_vect;

        mygame::vector3 pos_minus_camera_pos = position - player->camera.position;

        bn::fixed fov_angle = 512;

        // left border vector

        bn::fixed left_angle = player->camera.phi - (fov_angle/2);

        bn::fixed left_cos = bn::lut_cos(left_angle.data()).data() >> 4;
        bn::fixed left_sin = bn::lut_sin(left_angle.data()).data() >> 4;

        mygame::vector3 left_vect;

        left_vect.x = - 32 * left_sin;
        left_vect.y = 0;
        left_vect.z =   32 * left_cos;

        // right border vector

        bn::fixed right_angle = player->camera.phi + (fov_angle/2);

        bn::fixed right_cos = bn::lut_cos(right_angle.data()).data() >> 4;
        bn::fixed right_sin = bn::lut_sin(right_angle.data()).data() >> 4;

        mygame::vector3 right_vect;

        right_vect.x = - 32 * right_sin;
        right_vect.y = 0;
        right_vect.z =   32 * right_cos;



        interverted_cam_vect.x =  pos_minus_camera_pos.dot(player->camera.local_x_axis);
        interverted_cam_vect.y = -pos_minus_camera_pos.dot(player->camera.local_y_axis);
        interverted_cam_vect.z = -pos_minus_camera_pos.dot(player->camera.local_z_axis);

        bn::fixed size_x = spriteObj.horizontal_scale();
        bn::fixed size_y = spriteObj.vertical_scale();

        bn::fixed plan_near = 24;
        bn::fixed plan_far  = 512;

        // if (interverted_cam_vect.z < plan_near || plan_far < interverted_cam_vect.z)
        // {    break; }

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
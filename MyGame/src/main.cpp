#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_affine_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_affine_bg_pa_register_hbe_ptr.h"
#include "bn_affine_bg_pc_register_hbe_ptr.h"
#include "bn_affine_bg_dx_register_hbe_ptr.h"
#include "bn_affine_bg_dy_register_hbe_ptr.h"

#include "bn_affine_bg_items_land.h"
#include "bn_sprite_items_enemy01idle.h"


#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#include "player.h"
#include "object_type.h"

namespace
{
    void update_hbe_values(const mygame::Player& player, int16_t* pa_values, int16_t* pc_values, int* dx_values, int* dy_values)
    {
        int camera_x = player.camera.position.x.data();
        int camera_y = player.camera.position.y.data() >> 4;
        int camera_z = player.camera.position.z.data();
        int camera_cos = player.camera.cos;
        int camera_sin = player.camera.sin;
        int y_shift = 1024;

        for(int index = 0; index < bn::display::height(); ++index)
        {
            int reciprocal = bn::reciprocal_lut[index].data() >> 4;
            int lam = camera_y * reciprocal >> 12;
            int lcf = lam * camera_cos >> 8;
            int lsf = lam * camera_sin >> 8;

            pa_values[index] = int16_t(lcf >> 4);
            pc_values[index] = int16_t(lsf >> 4);

            int lxr = (bn::display::width() / 2) * lcf;
            int lyr = y_shift * lsf;
            dx_values[index] = (camera_x - lxr + lyr) >> 4;

            lxr = (bn::display::width() / 2) * lsf;
            lyr = y_shift * lcf;
            dy_values[index] = (camera_z - lxr - lyr) >> 4;
        }
    }
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

    constexpr bn::string_view info_text_lines[] = {
        "Left/Right: Rotate",
        "Up/Down: Move front/back",
        "B/A: move camera y",
    };

    common::info info("My Game", info_text_lines, text_generator);


    bn::affine_bg_ptr bg = bn::affine_bg_items::land.create_bg(0, 0);

    bg.set_wrapping_enabled(false);

    int16_t pa_values[bn::display::height()];
    bn::affine_bg_pa_register_hbe_ptr pa_hbe = bn::affine_bg_pa_register_hbe_ptr::create(bg, pa_values);

    int16_t pc_values[bn::display::height()];
    bn::affine_bg_pc_register_hbe_ptr pc_hbe = bn::affine_bg_pc_register_hbe_ptr::create(bg, pc_values);

    int dx_values[bn::display::height()];
    bn::affine_bg_dx_register_hbe_ptr dx_hbe = bn::affine_bg_dx_register_hbe_ptr::create(bg, dx_values);

    int dy_values[bn::display::height()];
    bn::affine_bg_dy_register_hbe_ptr dy_hbe = bn::affine_bg_dy_register_hbe_ptr::create(bg, dy_values);

    int xStart = bg.dimensions().width()  / 2;
    int zStart = bg.dimensions().height() / 2;

    mygame::Player* player = new mygame::Player(xStart, zStart);


    // Player sprite
    bn::sprite_ptr player_body_sprite = bn::sprite_items::player_body.create_sprite(-112, 72);

    bn::sprite_animate_action<4> action = bn::create_sprite_animate_action_forever(
                    player_body_sprite, 16, bn::sprite_items::player_body.tiles_item(), 0, 1, 2, 3);




    bn::sprite_ptr enemy_sprite = bn::sprite_items::enemy01idle.create_sprite(70, 0);
    
    // bn::sprite_animate_action<8> enemy_sprite_action = bn::create_sprite_animate_action_forever(
    //                 enemy_sprite, 8, bn::sprite_items::enemy01idle.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7);

    mygame::Object enemy = mygame::Object(xStart, zStart, &enemy_sprite);


    while(true)
    {
        player->_update();

        update_hbe_values(*player, pa_values, pc_values, dx_values, dy_values);

        pa_hbe.reload_values_ref();
        pc_hbe.reload_values_ref();

        dx_hbe.reload_values_ref();
        dy_hbe.reload_values_ref();


        if(bn::keypad::left_pressed())
        {
            action = bn::create_sprite_animate_action_forever(
                        player_body_sprite, 16, bn::sprite_items::player_body.tiles_item(), 8, 9, 10, 11);
        }
        else if(bn::keypad::right_pressed())
        {
            action = bn::create_sprite_animate_action_forever(
                        player_body_sprite, 16, bn::sprite_items::player_body.tiles_item(), 12, 13, 14, 15);
        }

        if(bn::keypad::up_pressed())
        {
            action = bn::create_sprite_animate_action_forever(
                        player_body_sprite, 16, bn::sprite_items::player_body.tiles_item(), 4, 5, 6, 7);
        }
        else if(bn::keypad::down_pressed())
        {
            action = bn::create_sprite_animate_action_forever(
                        player_body_sprite, 16, bn::sprite_items::player_body.tiles_item(), 0, 1, 2, 3);
        }


        bn::fixed scale = enemy.spriteObj.horizontal_scale();

        if(bn::keypad::l_held())
        {
            scale -= 0.01;
            enemy.spriteObj.set_horizontal_scale(bn::max(scale, bn::fixed(0.01)));
            enemy.spriteObj.set_vertical_scale(bn::max(scale, bn::fixed(0.01)));

        }
        else if(bn::keypad::r_held())
        {
            scale += 0.01;
            enemy.spriteObj.set_horizontal_scale(bn::min(scale, bn::fixed(2)));
            enemy.spriteObj.set_vertical_scale(bn::min(scale, bn::fixed(2)));

        }

        action.update();

        enemy._update(player);
    
        info.update();
        bn::core::update();
    }
}
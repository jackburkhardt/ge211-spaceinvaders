#include "game_config.hxx"


const int player_side = 50;
const int spacing = 20;

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims{1024, 768},
          player_dims{player_side, player_side},
          alien_cols{11},
          alien_rows{5},
          alien_spacing{spacing, spacing},
          top_margin{64},
          side_margin{200},
          bottom_margin{32},
          laser_size{5, 10},
          player_laser_velocity{500},
          alien_laser_velocity{-400},
          player_lives{3},
          shield_hitpoints{5},
          shield_size{128, 75},
          player_movement_speed{16}
{ }

ge211::Posn<int>
Game_config::player_top_left_0() const
{
    ge211::Posn<int> result(scene_dims);
    result.x /= 2;
    return result.up_by(bottom_margin + player_dims.height);
}

/// Computes how large each alien can be (in a given dimension), given the
/// total number of pixels available in that dimension, the number of aliens
/// in that dimensions, and the number of space pixels to leave in between.
///
/// PRECONDITION: divisor > 0
static int
div_w_spacing(int total, int divisor, int space)
{
    if (divisor < 0) {
        throw ge211::Client_logic_error("need at least 1 row & 1 column");
    }

    return (total - (divisor - 1) * space) / divisor;
}

/// Computes the dimensions of each alien from the other parameters.
ge211::Dims<int>
Game_config::alien_dims() const
{
    int field_width = scene_dims.width - 2 * side_margin;
    int width = div_w_spacing(field_width, alien_cols, alien_spacing.width);
    int height = width;
    return {width, height};
}
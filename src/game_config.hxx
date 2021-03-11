#pragma once

#include <ge211.hxx>


struct Game_config
{
    /// Constructs an instance with the default parameters.
    Game_config();

    /// The dimensions of the whole window:
    ge211::Dims<int> scene_dims;

    /// The dimensions of the ship:
    ge211::Dims<int> player_dims;

    /// Number of columns of aliens:
    int alien_cols;

    /// Number of rows of aliens:
    int alien_rows;

    /// The number of pixels of space between each column and row of
    /// aliens:
    ge211::Dims<int> alien_spacing;

    /// Number of pixels from top of screen to top of alien formation:
    int top_margin;

    /// Number of pixels from sides of screen to sides of max alien formation:
    int side_margin;

    /// Number of pixels from bottom of screen to bottom of ship.
    int bottom_margin;

    /// Size of the laser block
    ge211::Dims<int> laser_size;

    /// Positive "velocity" value to represent the lasers moving upwards
    int player_laser_velocity;

    /// Negative "velocity" value to represent the lasers moving downwards
    int alien_laser_velocity;

    /// Number of hits the player can survive.
    int player_lives;

    /// Number of hits a shield can take before breaking.
    int shield_hitpoints;

    /// Size of the shields
    ge211::Dims<int> shield_size;

    /// How fast the player can move on each frame, when holding an arrow key
    int player_movement_speed;

    /// The initial state of the ship
    ge211::Posn<int> player_top_left_0() const;

    /// The dimensions of each alien
    ge211::Dims<int> alien_dims() const;
};
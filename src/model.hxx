#pragma once

#include "game_config.hxx"
#include "alien.hxx"
#include "laser.hxx"
#include "shield.hxx"
#include "alien_laser.hxx"
#include <ge211.hxx>
#include <vector>


using Position = ge211::Posn<float>;
using Block = ge211::Rect<int>;

struct Model
{
    /// Model constructor, automatically assigning a Game_config()
    explicit Model(Game_config const& config = Game_config());

    /// A helper function to perform the alien movements throughout the game
    void alien_movement();

    /// Called every frame, takes care of all basic game actions
    void on_frame(double dt);

    /// Moves the player left, called in Controller
    void move_player_left();

    /// Moves the player right, called in Controller
    void move_player_right();

    /// Handles the logic for a player shooting a laser
    void player_shoot_laser();

    /// Handles the logic for an alien shooting a laser
    void alien_shoot_laser();

    /// Sets game over at appropriate times
    void set_game_over();

    /// A random number
    int next_random();



    ///
    /// MEMBER VARIABLES
    ///

    Game_config const config;

    Block player;
    int player_lives;
    int player_score;

    bool game_over;
    bool player_win;

    std::vector<Alien> aliens;
    std::vector<Laser> active_player_lasers;
    std::vector<AlienLaser> active_alien_lasers;
    std::vector<Shield> shields;

    ge211::Pausable_timer respawn_timer;

#ifdef CS211_TESTING
    friend struct Test_access;
#endif

private:
    double elapsed_time;
    ge211::Timer player_timer;
    ge211::Timer alien_timer;

};
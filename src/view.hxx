#pragma once

#include "model.hxx"

const int font_size = 20;

class View
{

public:
    /// View constructor, taking a Model
    explicit View(Model const&);

    /// View draw function, called every frame. Draws all of the sprites on
    /// the screen at the apprpriate times
    void draw(ge211::Sprite_set& set);

    /// The dimensions of the screen, from Model
    ge211::Dims<int> initial_window_dimensions() const;

    /// Tells whether the game is in a playable state
    bool game_live = false;


private:
    Model const& model_;

    ge211::Image_sprite const player_sprite;
    ge211::Image_sprite const alien_sprite;
    ge211::Rectangle_sprite const player_laser_sprite;
    ge211::Rectangle_sprite const alien_laser_sprite;
    ge211::Image_sprite const shield_sprite1;
    ge211::Image_sprite const shield_sprite2;
    ge211::Image_sprite const shield_sprite3;
    ge211::Image_sprite const shield_sprite4;
    ge211::Image_sprite const shield_sprite5;
    ge211::Image_sprite const player_explode_sprite;
    ge211::Image_sprite const game_over_sprite;
    ge211::Image_sprite const player_win_sprite;
    ge211::Image_sprite const life_sprite;
    ge211::Font const font{"sans.ttf", font_size};
    ge211::Text_sprite const info_sprite1;
    ge211::Text_sprite const info_sprite2;
    ge211::Text_sprite const info_sprite3;
    ge211::Text_sprite const info_sprite4;
    ge211::Text_sprite score_sprite;


    int x_helper(ge211::Text_sprite);
    int y_helper(ge211::Text_sprite, int);
    int life_sprite_helper(int, int);

};
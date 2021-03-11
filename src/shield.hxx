#pragma once

#include "game_config.hxx"
#include <ge211.hxx>
#include <vector>

using Position = ge211::Posn<float>;
using Health = size_t;
using Block = ge211::Rect<int>;

struct Shield : Block
{
    /// Includes ship of origin(?) and a config.

    Shield(int x, int y, Game_config const&);

    /// The velocity of the laser blast in pixels per tick.
    Health health;


    int x_;
    int y_;
    int width_;
    int height_;

};
#pragma once

#include "game_config.hxx"
#include "alien.hxx"
#include "shield.hxx"
#include "laser.hxx"
#include <ge211.hxx>
#include <vector>
#include <iostream>

using Position = ge211::Posn<float>;
using Block = ge211::Rect<int>;
using Laser_Velocity = int;

struct AlienLaser
{
    /// Includes ship of origin(?) and a config.
    AlienLaser(Alien const&, Game_config const&);

    /// Returns top left of the laser sprite.
    Position top_left() const;

    /// Checks the next position of the laser after time period dt and
    /// at the current velocity and returns it.
    AlienLaser next(double dt) const;

    /// Collision detection between the laser and a given ship. If the laser
    /// hits a ship, this will return true. Uses a similar hit detection
    /// system to hw05.
    bool hits_shield(Shield const&) const;

    bool hits_player(Block const& player) const;

    /// Runs through every Ship in ships and checks if the laser collides
    /// with them using hits_shielf(). If it does, this will damage the
    /// shield and return true, otherwise return false.
    bool destroy_shield(std::vector<Shield>&) const;

    /// The width of the laser beam.
    int width;

    /// The height of the laser beam.
    int height;

    /// The position of the center of the laser.
    Position center;

    /// The velocity of the laser blast in pixels per tick.
    Laser_Velocity velocity;
};
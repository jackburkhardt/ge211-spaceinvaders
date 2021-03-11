#pragma once

#include "game_config.hxx"
#include "alien.hxx"
#include "shield.hxx"
#include <ge211.hxx>
#include <vector>

using Position = ge211::Posn<float>;
using Block = ge211::Rect<int>;
using Laser_Velocity = int;

struct Laser
{
    /// Includes ship of origin(?) and a config.
    Laser(Block const& ship, Game_config const&);

    /// Returns top left of the laser sprite.
    Position top_left() const;

    /// Checks the next position of the laser after time period dt and
    /// at the current velocity and returns it.
    Laser next(double dt) const;

    /// Collision detection between the laser and a given ship. If the laser
    /// hits a ship, this will return true. Uses a similar hit detection
    /// system to hw05.
    bool hits_alien(Alien const&) const;

    /// Same as above, but with player lasers and the shields
    bool hits_shield(Shield const&) const;

    /// Runs through every Ship in ships and checks if the laser collides
    /// with them using hits_alien() or hits_shield(). If it does, this will
    /// remove the enemy ship damage the shield and return true,
    /// otherwise return false.
    bool destroy_alien(std::vector<Alien>&) const;
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
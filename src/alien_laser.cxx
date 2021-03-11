#include "alien_laser.hxx"

static Position
laser_initpos(
        Alien const& alien,
        Game_config const& config)
{
    float x = alien.x_ + 0.5 * alien.width_;
    float y = alien.y_ + 1 + config.laser_size.height;
    return {x, y};
}

AlienLaser::AlienLaser(Alien const& alien, Game_config const& config)
        :
        width(config.laser_size.width),
        height(config.laser_size.height),
        center(laser_initpos(alien, config)),
        velocity(Laser_Velocity(config.alien_laser_velocity))
{ }

Position
AlienLaser::top_left() const
{
    float x = AlienLaser::center.x - AlienLaser::width;
    float y = AlienLaser::center.y - AlienLaser::height/2;
    return {x, y};
}

AlienLaser
AlienLaser::next(double dt) const
{
    AlienLaser result(*this);
    result.center.y -= (velocity * dt);
    return result;
}

bool
AlienLaser::hits_shield(Shield const& shield) const
{
    int alien_laser_right_side = AlienLaser::center.x + AlienLaser::width / 2;
    int alien_laser_left_side = AlienLaser::center.x - AlienLaser::width / 2;
    int alien_laser_top_side = AlienLaser::center.y - AlienLaser::height / 2;
    int alien_laser_bottom_side = AlienLaser::center.y + AlienLaser::height / 2;

    int shield_right_side = shield.x_ + shield.width_;
    int shield_left_side = shield.x_;
    int shield_top_side = shield.y_;
    int shield_bottom_side = shield.y_ + shield.height_;


    return (alien_laser_right_side >= shield_left_side &&
            shield_right_side >= alien_laser_left_side &&
            alien_laser_bottom_side >= shield_top_side &&
            shield_bottom_side >= alien_laser_top_side);
}

bool
AlienLaser::hits_player(Block const& player) const
{
    int alien_laser_right_side = AlienLaser::center.x + AlienLaser::width / 2;
    int alien_laser_left_side = AlienLaser::center.x - AlienLaser::width / 2;
    int alien_laser_top_side = AlienLaser::center.y - AlienLaser::height / 2;
    int alien_laser_bottom_side = AlienLaser::center.y + AlienLaser::height / 2;

    int player_right_side = player.x + player.width;
    int player_left_side = player.x;
    int player_top_side = player.y;
    int player_bottom_side = player.y + player.height;


    return (alien_laser_right_side >= player_left_side &&
            player_right_side >= alien_laser_left_side &&
            alien_laser_bottom_side >= player_top_side &&
            player_bottom_side >= alien_laser_top_side);
}


bool
AlienLaser::destroy_shield(std::vector<Shield>& shields) const
{
    for (Shield& shield : shields) {
        if (hits_shield(shield)) {
            shield.health -= 1;
            if (shield.health == 0) {
                shield = shields.back();
                shields.pop_back();
            }
            return true;
        }
    }
    return false;
}
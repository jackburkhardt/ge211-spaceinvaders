#include "laser.hxx"

static Position
laser_initpos(
        Block const& block,
        Game_config const& config)
{
    float x = block.top_left().right_by(0.5 * block.width).x;
    float y = block.top_left().up_by(1+ config.laser_size.height / 2).y;
    return {x, y};
}

Laser::Laser(Block const& ship, Game_config const& config)
        :
        width(config.laser_size.width),
        height(config.laser_size.height),
        center(laser_initpos(ship, config)),
        velocity(Laser_Velocity(config.player_laser_velocity))
{ }

Position
Laser::top_left() const
{
    float x = Laser::center.x - Laser::width;
    float y = Laser::center.y - Laser::height / 2;
    return {x, y};
}

Laser
Laser::next(double dt) const
{
    Laser result(*this);
    result.center.y -= (velocity * dt);
    return result;
}

bool
Laser::hits_alien(Alien const& alien) const
{
    int laser_right_side = Laser::center.x + Laser::width / 2;
    int laser_left_side = Laser::center.x - Laser::width / 2;
    int laser_top_side = Laser::center.y - Laser::height / 2;
    int laser_bottom_side = Laser::center.y + Laser::height / 2;

    int object_right_side = alien.x_ + alien.width_;
    int object_left_side = alien.x_;
    int object_top_side = alien.y_;
    int object_bottom_side = alien.y_ + alien.height_;


    return (laser_right_side >= object_left_side &&
            object_right_side >= laser_left_side &&
            laser_bottom_side >= object_top_side &&
            object_bottom_side >= laser_top_side);
}


bool
Laser::hits_shield(Shield const& shield) const
{
    int laser_right_side = Laser::center.x + Laser::width / 2;
    int laser_left_side = Laser::center.x - Laser::width / 2;
    int laser_top_side = Laser::center.y - Laser::height / 2;
    int laser_bottom_side = Laser::center.y + Laser::height / 2;

    int shield_right_side = shield.x_ + shield.width_;
    int shield_left_side = shield.x_;
    int shield_top_side = shield.y_;
    int shield_bottom_side = shield.y_ + shield.height_;


    return (laser_right_side >= shield_left_side &&
            shield_right_side >= laser_left_side &&
            laser_bottom_side >= shield_top_side &&
            shield_bottom_side >= laser_top_side);
}

bool
Laser::destroy_alien(std::vector<Alien>& aliens) const
{
    for(int i = 0; i < aliens.size(); ++i){
        if(hits_alien(aliens[i])){
            aliens[i] = aliens.back();
            aliens.pop_back();
            return true;
        }
    }
    return false;
}

bool
Laser::destroy_shield(std::vector<Shield>& shields) const
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
#include "model.hxx"

Model::Model(Game_config const& config)
        : config(config),
          player(Block::from_top_left({config.player_top_left_0().x -
                                       config.player_dims.width / 2,
                                       config.player_top_left_0().y},
                                      config.player_dims)),
          player_lives(config.player_lives),
          player_score(0)

{
    int x_now = config.side_margin;
    int y_now = config.top_margin;

    for(int c = 0; c < config.alien_cols; c++){
        for(int r = 0; r < config.alien_rows; r++){
            Alien a{x_now, y_now,
                    config.alien_dims().width, config.alien_dims().height};

            aliens.push_back(a);
            y_now += config.alien_spacing.height + config.alien_dims().height;
        }
        x_now += config.alien_spacing.width + config.alien_dims().width;
        y_now = config.top_margin;
    }

    for(int i = 0; i < 3; i++) {
        Shield s{config.shield_size.width + 320 * i,
                 config.player_top_left_0().y - 100,
                 config};
        shields.push_back(s);
    }

    respawn_timer.pause();
    respawn_timer.reset();
}


void Model::alien_movement()
{
    std::vector<Alien> temp_aliens;
    bool bounce = false;

    for (Alien alien : aliens) {
        Alien temp = alien;
        temp.x_ += Alien::dir;
        if (temp.x_ + temp.width_ >= config.scene_dims.width || temp.x_ <= 0) {
            bounce = true;
            Alien::dir *= -1;
        }
        temp_aliens.push_back(temp);
    }

    if (bounce) {
        for (Alien& a : temp_aliens) {
            a.y_ += 58;
            if(a.y_ + a.height_ >= player.y){
                set_game_over();
                player_win = false;
            }
        }
    }
    aliens = temp_aliens;
}

void Model::on_frame(double dt)
{
    elapsed_time += dt;
    if (elapsed_time > 0.025) {
        elapsed_time = 0.0;
        alien_movement();
    }

    alien_shoot_laser();

    if(respawn_timer.elapsed_time() > ge211::Duration(2.0)) {
        player.x = config.player_top_left_0().x - config.player_dims.width / 2;
        player.y = config.player_top_left_0().y;
        respawn_timer.pause();
        respawn_timer.reset();
    }

    if (aliens.empty()) {
        player_win = true;
        set_game_over();
    }

    for (Laser& l : active_player_lasers) {
        Laser next = l.next(dt);
        if (next.destroy_alien(aliens)) {
            l = next;
            active_player_lasers.pop_back();
            player_score += 100;
        } else if (next.destroy_shield(shields)) {
            l = next;
            active_player_lasers.pop_back();
        } else {
            l = next;
        }
    }

    for (AlienLaser& al : active_alien_lasers) {
        AlienLaser al_next = al.next(dt);
        if (al_next.destroy_shield(shields)) {
            al = al_next;
            active_alien_lasers.pop_back();
        } else if (al_next.hits_player(player) &&
                   respawn_timer.elapsed_time() == ge211::Duration(0.0) ) {
            player_lives -= 1;
            player_score -= 300;

            respawn_timer.resume();

            if (player_lives <= 0) {
                set_game_over();
                player_win = false;
            }
            al = al_next;
            active_alien_lasers.pop_back();
        } else {
            al = al_next;
        }
    }
}


void Model::move_player_left()
{
    if(player.x + config.player_movement_speed > 0 &&
       respawn_timer.elapsed_time() == ge211::Duration(0.0)) {
        player.x -= config.player_movement_speed;
    }
}

void Model::move_player_right()
{
    if(player.x + config.player_dims.width + config.player_movement_speed
            < config.scene_dims.width &&
       respawn_timer.elapsed_time() == ge211::Duration(0.0)) {
        player.x += config.player_movement_speed;
    }
}

void Model::player_shoot_laser()
{
    if(player_timer.elapsed_time() >= ge211::Duration(1.0) &&
       respawn_timer.elapsed_time() == ge211::Duration(0.0)) {
        Laser laser{player, config};
        active_player_lasers.push_back(laser);
        player_timer.reset();
    }

}

void Model::alien_shoot_laser()
{
    if(alien_timer.elapsed_time() >= ge211::Duration(1.5)) {
        AlienLaser laser{aliens[next_random()], config};
        active_alien_lasers.push_back(laser);
        alien_timer.reset();
    }
}
void Model::set_game_over()
{
    game_over = true;
}

int Model::next_random() {
    ge211::Random_source<int> copy(0, aliens.size() - 1);
    return copy.next();
}

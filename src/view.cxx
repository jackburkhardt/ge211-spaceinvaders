#include "view.hxx"


const ge211::Color pl_ls_sp_color{ge211::Color{107,196,255}};
const ge211::Color al_ls_sp_color{ge211::Color{235,107,255}};
const int life_sprite_size = 15;

View::View(Model const& model)
        : model_(model),
          player_sprite{"player.png"},
          alien_sprite{"alien.png"},
          player_laser_sprite(model_.config.laser_size, pl_ls_sp_color),
          alien_laser_sprite(model_.config.laser_size, al_ls_sp_color),
          shield_sprite1("shield-full.png"),
          shield_sprite2("shield-2.png"),
          shield_sprite3("shield-3.png"),
          shield_sprite4("shield-4.png"),
          shield_sprite5("shield-final.png"),
          player_explode_sprite("explode_player.png"),
          game_over_sprite("game_over.jpg"),
          player_win_sprite("game_win.png"),
          life_sprite("player_life.png"),
          info_sprite1("Use left and right arrow keys to move, and SPACE ",
                       font),
          info_sprite2("to shoot. Destroy every alien before they reach the "
                       "bottom. ",
                       font),
          info_sprite3("Shields can protect you, but have limited health. ",
                       font),
          info_sprite4("Press an arrow button to begin.", font),
          score_sprite({"Score: " + std::to_string(model_.player_score)}
                  , font)
{ }

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}

int
View::x_helper(ge211::Text_sprite const sprite){
    return
    initial_window_dimensions().width / 2 - sprite.dimensions().width / 2;
}

int
View::y_helper(ge211::Text_sprite const sprite, int num){
    return
    initial_window_dimensions().height / 2 +
    num * sprite.dimensions().height / 2;
}

int
View::life_sprite_helper(int num1, int num2){
    return
    initial_window_dimensions().width - num1 *
    life_sprite.dimensions().width - num2;
}

void
View::draw(ge211::Sprite_set& sprites)
{
    if (!model_.game_over) {
        if (!game_live) {
            sprites.add_sprite(info_sprite1, {x_helper(info_sprite1),
                                                  y_helper(info_sprite1, 1)});
            sprites.add_sprite(info_sprite2, {x_helper(info_sprite2),
                                                  y_helper(info_sprite2, 2)});
            sprites.add_sprite(info_sprite3, {x_helper(info_sprite3),
                                                  y_helper(info_sprite3, 3)});
            sprites.add_sprite(info_sprite4, {x_helper(info_sprite4),
                                                  y_helper(info_sprite4, 4)});
        }

        if(model_.respawn_timer.elapsed_time() == ge211::Duration(0.0)) {
            sprites.add_sprite(player_sprite, model_.player.top_left(),0);
        } else {
            sprites.add_sprite(player_explode_sprite,
                               model_.player.top_left(), 0);
        }

        score_sprite = ge211::Text_sprite({"Score: " +
                                           std::to_string(model_.player_score)},
                                          font);
        sprites.add_sprite(score_sprite, {life_sprite.dimensions().width,10});

        switch (model_.player_lives) {
        case 3:
            sprites.add_sprite(life_sprite, {life_sprite_helper(4, 20),
                                             life_sprite_size});
            sprites.add_sprite(life_sprite, {life_sprite_helper(3,
                                                                life_sprite_size
                                                                ),
                                             life_sprite_size});
            sprites.add_sprite(life_sprite, {life_sprite_helper(2, 10),
                                             life_sprite_size});
            break;
        case 2:
            sprites.add_sprite(life_sprite, {life_sprite_helper(3,
                                                                life_sprite_size
                                                                ),
                                             life_sprite_size});
            sprites.add_sprite(life_sprite, {life_sprite_helper(2, 10),
                                             life_sprite_size});
            break;
        case 1:
            sprites.add_sprite(life_sprite, {life_sprite_helper(2, 10),
                                             life_sprite_size});
            break;
        }

        for (Alien alien : model_.aliens) {
            sprites.add_sprite(alien_sprite, {alien.x_, alien.y_},1);
        }
        for (Laser laser : model_.active_player_lasers) {
            sprites.add_sprite(player_laser_sprite,
                               {laser.top_left().into<int>()},2);
        }
        for (AlienLaser laser : model_.active_alien_lasers) {
            sprites.add_sprite(alien_laser_sprite,
                               {laser.top_left().into<int>()},2);
        }
        for (Shield shield : model_.shields) {
            if (shield.health == 5) {
                sprites.add_sprite(shield_sprite1, {shield.x_, shield.y_}, 3);
            } else if (shield.health == 4) {
                sprites.add_sprite(shield_sprite2, {shield.x_, shield.y_},3);
            } else if (shield.health == 3) {
                sprites.add_sprite(shield_sprite3, {shield.x_, shield.y_}, 3);
            } else if (shield.health == 2) {
                sprites.add_sprite(shield_sprite4, {shield.x_, shield.y_}, 3);
            } else if (shield.health == 1) {
                sprites.add_sprite(shield_sprite5, {shield.x_, shield.y_},3);
            }
        }
    } else if (model_.game_over && !model_.player_win){
        game_live = false;

        sprites.add_sprite(game_over_sprite, {initial_window_dimensions()
                        .width / 2 - game_over_sprite.dimensions().width / 2,
                                              initial_window_dimensions()
                        .height / 2 - game_over_sprite.dimensions().height/2});

        sprites.add_sprite(player_explode_sprite, model_.player.top_left());
        sprites.add_sprite(score_sprite, {life_sprite.dimensions().width,10});

    } else if (model_.game_over && model_.player_win) {
        game_live = false;

        sprites.add_sprite(player_win_sprite, {initial_window_dimensions()
                        .width / 2 - player_win_sprite.dimensions().width / 2,
                                               initial_window_dimensions()
                        .height/2 - player_win_sprite.dimensions().height/2});

        sprites.add_sprite(score_sprite, {life_sprite.dimensions().width,10});
    }
}
#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    if(key == ge211::Key::code(' ')){
        if (!model_.game_over && view_.game_live) {
            model_.player_shoot_laser();
        }
    }

    if(key == ge211::Key::left()){
        view_.game_live = true;
        if (!model_.game_over) {
            model_.move_player_left();
        }
    }

    if(key == ge211::Key::right()){
        view_.game_live = true;
        if (!model_.game_over) {
            model_.move_player_right();
        }
    }
}

void Controller::on_frame(double dt)
{
    if (view_.game_live && !model_.game_over) {
        model_.on_frame(dt);
    }
}
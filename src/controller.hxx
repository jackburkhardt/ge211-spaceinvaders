#pragma once

#include "model.hxx"
#include "view.hxx"


class Controller : public ge211::Abstract_game
{
public:
    explicit Controller();

protected:
    void draw(ge211::Sprite_set&) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    void on_key(ge211::Key) override;

    void on_frame(double dt) override;

    bool game_live = false;

private:
    Model model_;
    View view_;
};
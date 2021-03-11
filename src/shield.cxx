#include "shield.hxx"

Shield::Shield(int x, int y, Game_config const& config)
        : health(config.shield_hitpoints),
          x_(x),
          y_(y),
          width_(config.shield_size.width),
          height_(config.shield_size.height)
{ }
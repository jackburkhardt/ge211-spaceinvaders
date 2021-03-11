#include "alien.hxx"

Alien::Alien(Coordinate x, Coordinate y,
             Coordinate width, Coordinate height)
        : x_(x),
          y_(y),
          width_(width),
          height_(height)
{ }

int Alien::dir = 1;

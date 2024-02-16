#pragma once
#include <string>
#include <glm.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <random>


class Tile
{
private:

public:
    Tile(std::string Material, SDL_Renderer* renderer);

    ~Tile();

};

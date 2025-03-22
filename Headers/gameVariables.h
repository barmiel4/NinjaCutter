#pragma once
#include "SFML/Graphics.hpp"

#define LOCKED_FPS -INFINITY
//constexpr auto LOCKED_FPS = 1/60.f;

extern float fElapsedTime;

extern const short wi;
extern const short hi;
extern sf::ContextSettings settings;
extern sf::RenderWindow window;
extern sf::Event e;
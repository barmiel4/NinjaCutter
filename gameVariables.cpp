#include "gameVariables.h"


float fElapsedTime = 0.0f;

const short wi = 1280;
const short hi = 720;


sf::ContextSettings settings(0, 0, 16, 0);
sf::RenderWindow window(sf::VideoMode(wi, hi), "ninja cutter", sf::Style::Default, settings);
sf::Event e;
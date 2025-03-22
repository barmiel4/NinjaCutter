#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "line.h"


#define logS std::cout << "==================================================\n"

extern std::vector<line> debugLines;

//print a vector of ints
void print(const sf::Vector2i& v);

//print a vector of floats
void print(const sf::Vector2f& v);

void fInfo(const char* const fName, const char* const location, const char* const message);
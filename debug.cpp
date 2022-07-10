#include "debug.h"

std::vector<line> debugLines;

//print a vector of ints
void print(const sf::Vector2i& v)
{
	std::cout << "x: " << v.x << ", y: " << v.y << std::endl;
}

//print a vector of floats
void print(const sf::Vector2f& v)
{
	std::cout << "x: " << v.x << ", y: " << v.y << std::endl;
}

void fInfo(const char* const fName, const char* const location, const char* const message) 
{
	std::cout << "[function: " << fName << " inside: " << location << "]: " << message << '\n';
}
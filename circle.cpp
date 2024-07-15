#include <iostream>
#include "circle.h"


circle::circle() {}

circle::circle(float radius, const properties& p_in) 
{
	//vertex = 40;
	vertCount = 35;			
	//vertex = 360;			//slow AS FUCK
	setPointCount(vertCount);
	//radius *= sqrt(2 - 2 * cos(2 * M_PI / vertex));
	draw(radius);

	prop = p_in;
	dispenseProperites();
}


//	[PROBLEM]		drawing circle this way(with sin and cos) generated weird problem with cutting: the side were flipped and in some cases cut debris were "mirrored"
//	[WORK-AROUND]	calculate side based on provided radius via law of cosines and use base polygon struct's method to draw a polygon.

//	[SOLVED?]		for now it behaves correctly
void circle::draw(const float& r)
{
	constexpr float TWOPI = 2 * M_PI;
	float step = TWOPI / vertCount;
	float angle = 0.0f;

	for (int a = 0; a < vertCount; a++)
	{
		//std::cout << "sin: " << sin(angle) << ", cos: " << cos(angle) << std::endl;
		setPoint(a, sf::Vector2f(cos(angle) * r, sin(angle) * r));
		angle += step;
	}
}
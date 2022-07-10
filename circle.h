#pragma once
#include "polygon.h"


struct circle : public polygon
{
	circle();

	circle(float radius, const properties& p_in);

	void draw(const float& r);
};
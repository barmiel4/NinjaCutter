#pragma once
#include "polygon.h"


struct rectangle : public polygon
{
	rectangle(float a, const properties& p_in);						//one side provided == square
	rectangle(float a, float b, const properties& p_in);			//both sides provided == rectangle

};


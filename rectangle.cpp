#include "rectangle.h"
#include "debug.h"

rectangle::rectangle(float a, const properties& p_in)
{
	a /= 2.0f;
	
	setPointCount(4);
	setPoint(0, { -a, -a });
	setPoint(1, { a, -a });
	setPoint(2, { a, a });
	setPoint(3, { -a, a });

	
	prop = p_in;
	dispenseProperites();
	/*std::cout << "origin is: ";
	print(getOrigin());*/
	
}

rectangle::rectangle(float a, float b, const properties& p_in)
{
	a /= 2.0f;
	b /= 2.0f;

	setPointCount(4);
	setPoint(0, { -a, -b });
	setPoint(1, { a, -b });
	setPoint(2, { a, b });
	setPoint(3, { -a, b });

	prop = p_in;
	dispenseProperites();
}

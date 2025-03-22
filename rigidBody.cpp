#include "rigidBody.h"
#include "debug.h"

//#define DETAILED_DEBUG

rigidBody::rigidBody()
{

}

rigidBody::rigidBody(const polygon& poly_in)
	: poly(poly_in)
{
	mass = -1.0f;
}

rigidBody::rigidBody(const polygon& poly_in, const float& mass_in)
	: poly(poly_in), mass(mass_in)
{
	linearVelocity = { 0.0f, 0.0f };
	force = { 0.0f, 0.0f };
	angularVelocity = 0.0f;
	torque = 0.0f;

	auto d = poly.getLocalBounds();
	//from centimeters to meters:
	d.width /= 100.0f;
	d.height /= 100.0f;
	momentOfInertia = (d.width * d.width + d.height * d.height) * (mass / 12.0f)/* / 10000.0f*/;

#ifdef DETAILED_DEBUG 

	std::cout << "assumes that all shapes deriving from polygon are rectangular[FOR NOW]!!!\n";
	std::cout << "Shape info:\n";
	std::cout << "width; heigth in m\t" << d.width << "; " << d.height << std::endl;
	std::cout << "moment of inertia\t" << momentOfInertia << std::endl;

#endif //DETAILED_DEBUG
}

// add force_in at effector(location). inWorldSpace tell whether effector is expressed in world space or in body space - by default it, 
// method assumes effctor is in world space.
// same for the second addForce method
void rigidBody::addForce(const sf::Vector2f& force_in, const sf::Vector2f& effector, bool inWorldSpace)	
{
	sf::Vector2f arm = effector;

	//scale the effector to be in body space not world space(if is in world space):
	//if (inWorldSpace)
		arm -= (float)inWorldSpace * poly.getPosition();

	line armLine(poly.getPosition(), poly.getPosition() + arm, sf::Color::Yellow, 1);

#if VIS_DEBUG
	debugLines.push_back(armLine);
#endif

	scaleArm(arm);

	force = force_in;

	linearVelocity += (force / mass);

	//angular movement:
	auto d = poly.getLocalBounds();
	torque += math::crossZ(arm, force);
	angularVelocity += torque / momentOfInertia;

	//detailed debug:
	#ifdef DETAILED_DEBUG 
	static int count = 1;
	std::cout << "Force addition #" << count++ << std::endl;
	std::cout << "angular velocity per frame:\t" << angularVelocity << std::endl;
	std::cout << "linear velocity per second:\t";
	print(linearVelocity);
	std::cout << "torque:\t" << torque << std::endl;
	#endif
}

void rigidBody::addForce(const sf::Vector2f& fDirection, const float& fStrength, const sf::Vector2f& effector, bool inWorldSpace)
{
	sf::Vector2f arm = effector;

	//scale the effector to be in body space not world space(if is in world space):
	if (inWorldSpace)
		arm -= poly.getPosition();

	force = fDirection * fStrength;

	line armLine(poly.getPosition(), poly.getPosition() + arm, sf::Color::Yellow, 1);

#if VIS_DEBUG
	debugLines.push_back(armLine);
#endif

	scaleArm(arm);

	//linear movement:
	//linearAcceleration = 
	linearVelocity += (force / mass);

	//angular movement:
	auto d = poly.getLocalBounds();
	torque += math::crossZ(arm, force);
	angularVelocity += torque / momentOfInertia;

	//detailed debug:
	#ifdef DETAILED_DEBUG 
	static int count = 1;
	std::cout << "Force addition #" << count++ << std::endl;
	std::cout << "angular velocity per frame:\t" << angularVelocity  << std::endl;
	std::cout << "linear velocity per second:\t";
	print(linearVelocity);
	std::cout << "torque:\t" << torque << std::endl;
	#endif
}

void placeForce(const sf::Vector2f& force_in, sf::Vector2f arm, const forcesphere& area) 
{
	fInfo("placeForce", "rigidBody", "does nothing!!");
}

//implement later:
/*void addImpulse(const sf::Vector2f& impulse)
{

}

void addImpulse(const sf::Vector2f& iDirection, const float& iStrength)
{

}*/

void rigidBody::update(const float& elapsedTime)
{
	poly.rotate(fElapsedTime * angularVelocity);
	poly.move(fElapsedTime * linearVelocity);
}

//by default: one px == one cm
//so if shape has side of 100px(cm) 
//it has to be scaled from cm back to m by division over 100(since all equations assume kg and m)
void rigidBody::scaleArm(sf::Vector2f& arm)
{
	arm *= 0.01f;
}
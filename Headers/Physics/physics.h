#pragma once
#include "Physics/rigidBody.h"
#include "Geometry/line.h"
#include "gameVariables.h"

//moved to the polygon code
//test each edge of given polygon with a given line to check if fully penetrates it
//std::optional<std::vector<vertecies>> checkEdges(const rigidBody& s, line cut);

//go through the array of all polygon in the scene, check collision with given line and cut them into pieces if it occured
void cutShapes(std::vector<rigidBody>& shapes, line& cut);

class physics
{
public:
	std::vector<rigidBody> bodies;

	physics(const std::vector<rigidBody>&);

	void simulate();

	void addBody(const rigidBody&);

	void addBodies(const std::vector<rigidBody>&);

	void addPolygonsAsBodies(const std::vector<polygon>&);

	//the object of a this class can be passed and will be implicitly converted to bodies if needed(i.e. for functions like cutShapes that need access to rigidBodies in the game)
	operator std::vector<rigidBody>() const { return bodies; }

private:
	void printBodies();
};


#include "Field.h"

using namespace DHAStar5000;

Field::Field(Field *parent, Map *map, int x, int y)
	:Node(parent)
{
	this->map = map;
	this->x = x;
	this->y = y;
}


Field::~Field()
{
}

void Field::generateKids()
{
	 
}

float Field::getHeuristic()
{

}

float Field::getNodePrice()
{

}

float Field::getTotalPrice()
{

}

bool Field::operator==(const Node &other) const
{
	if (x == dynamic_cast<const Field&>(other).x && y == dynamic_cast<const Field&>(other).y) {
		return true;
	}

	return false;
}

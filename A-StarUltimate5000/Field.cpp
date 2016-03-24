#include "Field.h"
#include <algorithm>

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
	for (auto i = kids.begin(); i != kids.end(); ++i) {
		delete (*i);
	}

	kids.clear();
}

bool Field::isIt() const
{
	int Fx, Fy;
	map->getFinish(Fx, Fy);

	return (Fx == x && Fy == y);
}

bool Field::compare(Node *a, Node *b) const
{
	return a->getTotalPrice() < b->getTotalPrice();
}

void Field::generateKids()
{
	int m_width = map->getWidth();
	int m_height = map->getHeight();
	Field *tmp;

	bool up = false;
	bool down = false;

	if (x > 0) {
		tmp = new Field(this, map, x - 1, y);
		kids.push_back(tmp);

		if (y > 0) {
			tmp = new Field(this, map, x - 1, y - 1);
			kids.push_back(tmp);

			tmp = new Field(this, map, x, y - 1);
			up = true;
			kids.push_back(tmp);
		}

		if (y < (m_height - 1)) {
			tmp = new Field(this, map, x - 1, y + 1);
			kids.push_back(tmp);

			tmp = new Field(this, map, x, y + 1);
			down = true;
			kids.push_back(tmp);
		}
	}

	if (x < (m_width - 1)) {
		tmp = new Field(this, map, x + 1, y);
		kids.push_back(tmp);

		if (y > 0) {
			tmp = new Field(this, map, x + 1, y - 1);
			kids.push_back(tmp);

			if (!up) {
				tmp = new Field(this, map, x, y - 1);
				kids.push_back(tmp);
			}
		}

		if (y < (m_height - 1)) {
			tmp = new Field(this, map, x + 1, y + 1);
			kids.push_back(tmp);

			if (!down) {
				tmp = new Field(this, map, x, y + 1);
				kids.push_back(tmp);
			}
		}
	}

	std::sort(kids.begin(), kids.end(), compare);
}

float Field::getHeuristic()
{
	int Fx;
	int Fy;
	map->getFinish(Fx, Fy);

	return (abs(Fx - x) + abs(Fy - y)) * 10;
}

float Field::getNodePrice()
{
	if (parent == nullptr) {
		return 0;
	}

	Field *p = dynamic_cast<Field *>(parent);

	if (p->x != x && p->y != y) {
		return p->getNodePrice() + 14;
	}

	return p->getNodePrice() + 10;
}

float Field::getTotalPrice()
{
	return getNodePrice() + getHeuristic();
}

bool Field::operator==(const Node &other) const
{
	if (x == dynamic_cast<const Field&>(other).x && y == dynamic_cast<const Field&>(other).y) {
		return true;
	}

	return false;
}

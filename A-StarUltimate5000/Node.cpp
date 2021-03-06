#include "Node.h"

using namespace DHAlgos;

Node::Node(Node *parent)
{
	this->parent = parent;
	dead = false;
}

Node::~Node()
{
	deleteKids();
}

void Node::deleteKids()
{
	for (auto i = kids.begin(); i != kids.end(); ++i) {
		(*i)->deleteKids();
		delete (*i);
	}

	kids.clear();
}

std::vector<Node *> *Node::getPathToStart() const
{
	if (parent == nullptr) {
		std::vector<Node *> *out = new std::vector<Node *>();
		return out;
	}

	std::vector<Node *> *o = parent->getPathToStart();
	o->push_back(parent);
	return o;
}

bool Node::isDead() const
{
	return dead;
}

void Node::kill()
{
	dead = true;
}

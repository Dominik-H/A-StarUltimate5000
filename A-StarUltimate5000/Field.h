#pragma once
#include "Node.h"
#include "Map.h"

namespace DHAStar5000 {

	class Field :
		public DHAlgos::Node
	{
	public:
		Field(Field *parent, Map *map, int x, int y);
		~Field();

		virtual float getHeuristic();
		virtual float getNodePrice();
		virtual float getTotalPrice();
		virtual bool operator==(const Node &other) const;

		virtual void generateKids();

		virtual bool isIt() const;
		virtual bool compare(Node *a, Node *b) const;

	private:
		int x, y;
		Map *map;
	};

}


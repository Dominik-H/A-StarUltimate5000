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
		virtual void deleteKids();

		virtual float getHeuristic();
		virtual float getNodePrice();
		virtual float getTotalPrice();

		virtual void generateKids();

		virtual bool isIt() const;

		int getX() const { return x; }
		int getY() const { return y; }

	private:
		int x, y;
		Map *map;
	};

}


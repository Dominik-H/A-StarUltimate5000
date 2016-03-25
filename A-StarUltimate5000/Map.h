#pragma once
#include <vector>
#include <string>

typedef unsigned int uint32;

namespace DHAStar5000 {

	enum FieldType {
		EMPTY = 0,
		WALL = 1,
		START = 2,
		FINISH = 3,
		OoB = 4
	};

	class Map
	{
	public:
		Map(std::string filename);
		~Map();

		FieldType getFieldType(const uint32 x, const uint32 y) const;
		void getStart(int &x, int &y) const;
		void getFinish(int &x, int &y) const;
		uint32 getHeight() const;
		uint32 getWidth() const;

	private:
		std::vector<std::vector<char>> map;
	};

}
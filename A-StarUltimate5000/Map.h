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

		FieldType getFieldType(const int x, const int y) const;
		void getStart(int &x, int &y) const;
		void getFinish(int &x, int &y) const;
		int getHeight() const;
		int getWidth() const;

	private:
		std::vector<std::vector<char>> map;
	};

}
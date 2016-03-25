#include "Map.h"
#include <fstream>
#include <iostream>

using namespace DHAStar5000;

Map::Map(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		std::string s_width, s_height;
		uint32 width, height;
		std::getline(file, s_width);
		std::getline(file, s_height);

		width = std::stoi(s_width);
		height = std::stoi(s_height);

		for (uint32 i = 0; i < height; ++i) {
			std::string line;
			std::getline(file, line);
			std::vector<char> map_line(line.begin(), line.end());

			if (map_line.size() != width) {
				file.close();
				exit(-1);
			}

			map.push_back(map_line);
			map_line.clear();
		}

		file.close();
	}
}


Map::~Map()
{
	for (uint32 i = 0; i < map.size(); ++i) {
		map[i].clear();
	}
	map.clear();
}

FieldType Map::getFieldType(const uint32 x, const uint32 y) const
{
	if (x >= getWidth() || y >= getHeight()) {
		return OoB;
	}

	char field = map[x][y];

	switch (field) {
	case '.':
		return EMPTY;
	case '#':
		return WALL;
	case 'S':
		return START;
	case 'C':
		return FINISH;
	default:
		return OoB;
	};
}

void Map::getStart(int &x, int &y) const
{
	for (uint32 i = 0; i < getHeight(); ++i) {
		for (uint32 j = 0; j < getWidth(); ++j) {
			if (getFieldType(j, i) == START) {
				x = j;
				y = i;
				return;
			}
		}
	}
}

void Map::getFinish(int &x, int &y) const
{
	for (uint32 i = 0; i < getHeight(); ++i) {
		for (uint32 j = 0; j < getWidth(); ++j) {
			if (getFieldType(j, i) == FINISH) {
				x = j;
				y = i;
				return;
			}
		}
	}
}

uint32 Map::getHeight() const
{
	if (!map.empty()) {
		return map[0].size();
	}

	return 0;
}

uint32 Map::getWidth() const
{
	return map.size();	
}

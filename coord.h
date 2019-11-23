#ifndef COORD_H
#define COORD_H
#include <iostream>
#include <vector>
#include <cstddef>

class Coord {
	public:
		int x = 0;
		int y = 0;
		Coord(int x, int y): x{x}, y{y} {};
};

#endif


#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"

class Cell {

	string name;
	bool in_region;
	bool is_filled;
	Coord coordinates;

	public:
		void set_region(bool b);
		void set_filled(bool b);
}

#endif


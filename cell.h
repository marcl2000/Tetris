#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"

class Cell {

	string name;
	bool in_region = false;
	bool is_filled = false;
	Coord coordinates;

	public:
		Cell(string name, Coord coordinates): name{name}, coordinates{coordinates} {}
		void set_region(bool b);
		void set_filled(bool b);
}

#endif


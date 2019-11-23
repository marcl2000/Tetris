#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>

class Cell {

	std::string name;
	bool in_region = false;
	bool is_filled = false;
	Coord coordinates;

	public:
		Cell(std::string name, Coord coordinates): name{name}, coordinates{coordinates} {}
		void set_region(bool b);
		void set_filled(bool b);
		bool inRegion();
		bool isFilled();
};

#endif


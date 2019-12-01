#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>

class Cell {

	std::string name;
	Coord coordinates;
	bool is_filled;

	public:
		Cell(std::string name, Coord coordinates, bool is_filled): name{name}, coordinates{coordinates}, is_filled{is_filled} {}
		void set_filled(bool b);
		bool isFilled();
		Coord getCoord();
		void setCoord(Coord c);
		std::string getName();
};

#endif


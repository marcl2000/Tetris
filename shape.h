#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"

//forward declaration
class Cell;

class Shape {

	string type_name;
	Coord focal;                //for rotating
	bool heavy_flag;
	bool gd_on;                 //so that a shape knows whether to update the graphicsdisplay when changed

	std::vector<Cell*> members;

	public:
		void move_left();
		void move_right();
		void move_down();
		void drop();
		void clockwise();
		void counterclockwise();
		void make_heavy();
		void gd_on();

}

#endif


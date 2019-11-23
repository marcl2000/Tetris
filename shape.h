#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>

//forward declaration
class Cell;

class Shape {

	std::string type_name;
	Coord focal;                //for rotating
	bool heavy_flag = false;
	bool gd_on;                 //so that a shape knows whether to update the graphicsdisplay when changed

	std::vector<Cell*> members;

	public:
		Shape(std::string name, Coord focal): type_name{name}, focal{focal} {}
		void move_left();
		void move_right();
		void move_down();
		void drop();
		void clockwise();
		void counterclockwise();
		void make_heavy();
		void gdOn();
		vector<Coord> getMembers();
};

#endif


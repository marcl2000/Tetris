#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>
#include "cell.h"

class Shape {

	std::string type_name;
	
	std::vector<Cell> members;
	bool heavy_flag;
	bool gd_on;

	public:
		~Shape(){}
		Shape(std::string name, std::vector<Cell> members, bool heavy_flag, bool gd_on):
		       	type_name{name}, members{members}, heavy_flag{heavy_flag}, gd_on{gd_on} {}
		void move_left();
		void move_right();
		void move_down();
		void drop();
		void clockwise();
		void counterclockwise();
		std::vector<Coord> getMembers();
};

#endif


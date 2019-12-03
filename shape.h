#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>
#include "cell.h"
#include "grid.h"

class Grid;

class Shape {

	public:
		virtual ~Shape(){}

		virtual void move_left(int n){}
		virtual void move_right(int n){}
		virtual void move_down(){}
		virtual void clockwise(Grid &g){}
		virtual void counterclockwise(Grid &g){}
		virtual std::vector<Coord> getMembers();
		virtual std::string getName();
		virtual std::vector<Cell>& getCells();
		virtual int getLevel();
		virtual bool wasScored();
		virtual void setScored(){}
};

#endif


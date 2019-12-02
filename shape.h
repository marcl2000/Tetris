#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>
#include "cell.h"

class Shape {

	public:
		virtual ~Shape(){}

		virtual void move_left(int n){}
		virtual void move_right(int n){}
		virtual void move_down(){}
		virtual void clockwise(){}
		virtual void counterclockwise(){}
		virtual std::vector<Coord> getMembers();
		virtual std::string getName();
		virtual std::vector<Cell>& getCells();
		virtual int getLevel();
		virtual bool wasScored();
		virtual void setScored(){}
};

#endif


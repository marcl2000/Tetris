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
	std::string type_name;
	std::vector<Cell> members;
	bool heavy_flag;
	bool bonus_heavy;
	bool gd_on;
	int level_placed;
	bool scored = false;

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
	virtual void change_level(int level) {}
	virtual void change_heavy() {};
};

#endif


#ifndef ISHAPE_H
#define ISHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>
#include "cell.h"
#include "shape.h"

class IShape: public Shape {

	std::string type_name;
	std::vector<Cell> members;
	bool heavy_flag;
	bool gd_on;

	public:
	~IShape() {}
	IShape(std::string name, std::vector<Cell> members, bool heavy_flag, bool gd_on):
		type_name{name}, members{members}, heavy_flag{heavy_flag}, gd_on{gd_on} {}
	
	void move_left(int n) override;
	void move_right(int n) override;
	void move_down() override;
	void clockwise() override;
	void counterclockwise() override;
	std::vector<Coord> getMembers() override;
	std::string getName() override;
	std::vector<Cell>& getCells() override;
};

#endif


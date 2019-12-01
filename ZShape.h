#ifndef ZSHAPE_H
#define ZSHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>
#include "cell.h"
#include "shape.h"

class ZShape: public Shape {

	std::string type_name;
	std::vector<Cell> members;
	bool heavy_flag;
	bool gd_on;
	int level_placed;
	bool scored = false;

	public:
	~ZShape() {}
	ZShape(std::string name, std::vector<Cell> members, bool heavy_flag, bool gd_on, int level_placed):
		type_name{name}, members{members}, heavy_flag{heavy_flag}, gd_on{gd_on}, level_placed{level_placed} {}

	void move_left(int n) override;
	void move_right(int n) override;
	void move_down() override;
	void clockwise() override;
	void counterclockwise() override;
	std::vector<Coord> getMembers() override;
	std::string getName() override;
	std::vector<Cell>& getCells() override;
	int getLevel() override;
	bool wasScored() override;
	void setScored() override;

};

#endif


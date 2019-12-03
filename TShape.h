#ifndef TSHAPE_H
#define TSHAPE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"
#include <string>
#include "cell.h"
#include "shape.h"
#include "grid.h"

class TShape: public Shape {

	std::string type_name;
	std::vector<Cell> members;
	bool heavy_flag;
	bool bonus_heavy;
	bool gd_on;
	int level_placed;
	bool scored = false;

	public:
	~TShape() {}
	TShape(std::string name, std::vector<Cell> members, bool heavy_flag, bool bonus_heavy, bool gd_on, int level_placed):
		type_name{name}, members{members}, heavy_flag{heavy_flag}, bonus_heavy{bonus_heavy}, gd_on{gd_on}, level_placed {level_placed} {}

	void move_left(int n) override;
	void move_right(int n) override;
	void move_down() override;
	void clockwise(Grid &g) override;
	void counterclockwise(Grid &g) override;
	std::vector<Coord> getMembers() override;
	std::string getName() override;
	std::vector<Cell>& getCells() override;
	int getLevel() override;
	bool wasScored() override;
	void setScored() override;

};

#endif


#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "levelone.h"
#include "shape.h"
#include "IShape.h"
#include "JShape.h"
#include "LShape.h"
#include "SShape.h"
#include "TShape.h"
#include "OShape.h"
#include "ZShape.h"

using namespace std;

Shape* LevelOne::createShape(string name, bool heavy_flag, bool gd_on){

	Shape *newShape;
	Coord one(0, 5*20);
	Coord two(20, 5*20);
	Coord three(20, 6*20);
	Coord four(40, 5*20);
	Cell c1("T", one, true);
	Cell c2("T", two, true);
	Cell c3("T", three, true);
	Cell c4("T", four, true);

	vector<Cell> members;
	members.emplace_back(c1);
	members.emplace_back(c2);
	members.emplace_back(c3);
	members.emplace_back(c4);
	newShape = new TShape("T", members, heavy_flag, gd_on);
	return newShape;	
}

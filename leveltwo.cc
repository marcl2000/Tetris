#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "leveltwo.h"
#include "shape.h"
#include "IShape.h"
#include "JShape.h"
#include "LShape.h"
#include "SShape.h"
#include "TShape.h"
#include "OShape.h"
#include "ZShape.h"

using namespace std;

Shape* LevelTwo::createShape(string name, bool heavy_flag, bool gd_on){
	
	Shape *newShape = nullptr;
	Coord one(0, 7*20);
	Coord two(20, 7*20);
	Coord three(40, 7*20);
	Coord four(40, 6*20);
	Cell c1("L", one, true);
	Cell c2("L", two, true);
	Cell c3("L", three, true);
	Cell c4("L", four, true);

	vector<Cell> members;
	members.emplace_back(c1);
	members.emplace_back(c2);
	members.emplace_back(c3);
	members.emplace_back(c4);
	newShape = new LShape("L", members, heavy_flag, gd_on);
	return newShape;
}


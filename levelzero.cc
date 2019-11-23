#include "levelzero.h"
#include <iostream>
#include <string>
#include <vector>
#include "shape.h"
#include "cell.h"
#include "level.h"

using namespace std;

Shape* LevelZero::createShape(string name, bool heavy_flag, bool gd_on){
	if(name == "I"){
		//set a focal point
		Coord focal(0,7*20);
		//make the four cells that set up the shape
		Coord one(0, 7*20);
		Coord two(20, 7*20);
		Coord three(40, 7*20);
		Coord four(60, 7*20);
		Cell c1("I", one, true);
		Cell c2("I", two, true);
		Cell c3("I", three, true);
		Cell c4("I", four, true);

		//now turn this into a shape
		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		Shape *newShape = new Shape("I", focal, members, heavy_flag, gd_on);
		return newShape;
	}
}



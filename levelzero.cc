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
		Shape *newShape = new Shape("I", members, heavy_flag, gd_on);
		return newShape;
	}

	if(name == "J"){
		Coord one(0, 6*20);
		Coord two(0, 7*20);
		Coord three(20, 7*20);
		Coord four(40, 7*20);
		Cell c1("J", one, true);
		Cell c2("J", two, true);
		Cell c3("J", three, true);
		Cell c4("J", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		Shape *newShape = new Shape("J", members, heavy_flag, gd_on);
		return newShape;
	}



}



#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "levelthree.h"
#include "shape.h"
#include "IShape.h"
#include "JShape.h"
#include "LShape.h"
#include "SShape.h"
#include "TShape.h"
#include "OShape.h"
#include "ZShape.h"

using namespace std;

Shape* LevelThree::createShape(string name, bool heavy_flag, bool gd_on, int level_made){

	Shape *newShape;

	//generate a random number
	double random = (double) rand() / (RAND_MAX);

	random *= 9;

	if(random > 7){
		//make an S block
		Coord one(0, 6*20);
		Coord two(20, 6*20);
		Coord three(20, 5*20);
		Coord four(40, 5*20);
		Cell c1("S", one, true);
		Cell c2("S", two, true);
		Cell c3("S", three, true);
		Cell c4("S", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);

		//for level three, heavy flag is always on
		newShape = new SShape("S", members, true, gd_on, level_made);
	}

	else if(random > 5){
		//make a Z block
		Coord one(0, 5*20);
		Coord two(20, 5*20);
		Coord three(20, 6*20);
		Coord four(40, 6*20);
		Cell c1("Z", one, true);
		Cell c2("Z", two, true);
		Cell c3("Z", three, true);
		Cell c4("Z", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		newShape = new ZShape("Z", members, true, gd_on, level_made);
	}

	else if(random > 4){
		//create a T block
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
		newShape = new TShape("T", members, true, gd_on, level_made);
	}

	else if(random > 3){
		//create an O block
		Coord one(0, 6*20);
		Coord two(20, 6*20);
		Coord three(0, 5*20);
		Coord four(20, 5*20);
		Cell c1("O", one, true);
		Cell c2("O", two, true);
		Cell c3("O", three, true);
		Cell c4("O", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		newShape = new OShape("O", members, true, gd_on, level_made);
	}

	else if(random > 2){
		//create an I block
		Coord one(0, 6*20);
		Coord two(20, 6*20);
		Coord three(40, 6*20);
		Coord four(60, 6*20);
		Cell c1("I", one, true);
		Cell c2("I", two, true);
		Cell c3("I", three, true);
		Cell c4("I", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		newShape = new IShape("I", members, true, gd_on, level_made);
	}

	else if(random > 1){
		//create an L block
		Coord one(0, 6*20);
		Coord two(20, 6*20);
		Coord three(40, 6*20);
		Coord four(40, 5*20);
		Cell c1("L", one, true);
		Cell c2("L", two, true);
		Cell c3("L", three, true);
		Cell c4("L", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		newShape = new LShape("L", members, true, gd_on, level_made);
	}

	else{
		//create a J block
		Coord one(0, 5*20);
		Coord two(0, 6*20);
		Coord three(20, 6*20);
		Coord four(40, 6*20);
		Cell c1("J", one, true);
		Cell c2("J", two, true);
		Cell c3("J", three, true);
		Cell c4("J", four, true);

		vector<Cell> members;
		members.emplace_back(c1);
		members.emplace_back(c2);
		members.emplace_back(c3);
		members.emplace_back(c4);
		newShape = new JShape("J", members, true, gd_on, level_made);
	}

	return newShape;
}


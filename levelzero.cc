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

	   if(name == "S"){
		Coord one(0, 7*20);
		Coord two(20, 7*20);
		Coord three(20, 6*20);
		Coord four(40, 6*20);
                Cell c1("S", one, true);
                Cell c2("S", two, true);
                Cell c3("S", three, true);
                Cell c4("S", four, true);

                vector<Cell> members;
                members.emplace_back(c1);
                members.emplace_back(c2);
                members.emplace_back(c3);
                members.emplace_back(c4);
                Shape *newShape = new Shape("S", members, heavy_flag, gd_on);
                return newShape;
        }

	if(name == "L"){
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
                Shape *newShape = new Shape("L", members, heavy_flag, gd_on);
                return newShape;
	}

	if(name == "O"){
                Coord one(0, 7*20);
                Coord two(20, 7*20);
                Coord three(0, 6*20);
                Coord four(20, 6*20);
                Cell c1("O", one, true);
                Cell c2("O", two, true);
                Cell c3("O", three, true);
                Cell c4("O", four, true);

                vector<Cell> members;
                members.emplace_back(c1);
                members.emplace_back(c2);
                members.emplace_back(c3);
                members.emplace_back(c4);
                Shape *newShape = new Shape("O", members, heavy_flag, gd_on);
                return newShape;
        }
	
	if(name == "Z"){
                Coord one(0, 6*20);
                Coord two(20, 7*20);
                Coord three(20, 6*20);
                Coord four(40, 7*20);
                Cell c1("Z", one, true);
                Cell c2("Z", two, true);
                Cell c3("Z", three, true);
                Cell c4("Z", four, true);

                vector<Cell> members;
                members.emplace_back(c1);
                members.emplace_back(c2);
                members.emplace_back(c3);
                members.emplace_back(c4);
                Shape *newShape = new Shape("Z", members, heavy_flag, gd_on);
                return newShape;
        }

	if(name == "T"){
                Coord one(0, 6*20);
                Coord two(20, 6*20);
                Coord three(20, 7*20);
                Coord four(40, 6*20);
                Cell c1("T", one, true);
                Cell c2("T", two, true);
                Cell c3("T", three, true);
                Cell c4("T", four, true);

                vector<Cell> members;
                members.emplace_back(c1);
                members.emplace_back(c2);
                members.emplace_back(c3);
                members.emplace_back(c4);
                Shape *newShape = new Shape("T", members, heavy_flag, gd_on);
                return newShape;
	}
        
}



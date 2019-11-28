#include "SShape.h"
#include <iostream>
#include <string>
#include <vector>
#include "shape.h"
#include "cell.h"
#include "level.h"

using namespace std;

void SShape::move_left(int n){
	for (int i=0; i < 4; ++i) {
		int newx = this->members[i].getCoord().x - n * 20;
		Coord c(newx, this->members[i].getCoord().y);
		this->members[i].setCoord(c);
		cout << "New coords are " << c.x << " , " << c.y << endl;
	}

	for (int i=0; i < 4; ++i) {
		while (this->members[i].getCoord().x < 0) {
			this->move_right(1);
		}
	}
}

void SShape::move_right(int n){
	for (int i=0; i < 4; ++i) {
		int newx = this->members[i].getCoord().x + n * 20;
		Coord c(newx, this->members[i].getCoord().y);
		this->members[i].setCoord(c);
		cout << "New coords are " << c.x << " , " << c.y << endl;
	}

	for (int i=0; i < 4; ++i) {
		while (this->members[i].getCoord().x > 10 * 20) {
			this->move_left(1);
		}
	}
}

void SShape::move_down(){
	//main has concluded that it is possible to move down
	for(int i=0;i<4;i++){
		int n = this->members[i].getCoord().x;
		int m = this->members[i].getCoord().y + 20;
		Coord c(n,m);
		this->members[i].setCoord(c);
	}
}

void SShape::clockwise(){

	// Check if it is horizontal, then it can be rotated always
	if (this->members[0].getCoord().x - this->members[3].getCoord().x == - 2 * 20) {
		// Position 1

		if (this->members[0].getCoord().y > this->members[3].getCoord().y) {

			cout << "POSITION 1" << endl;
			Coord one(this->members[0].getCoord().x, this->members[0].getCoord().y - 2 * 20);
			this->members[0].setCoord(one);

			Coord two(this->members[1].getCoord().x - 1 * 20, this->members[1].getCoord().y - 1 * 20);
			this->members[1].setCoord(two);

			//Third coordinate stays the same

			Coord four(this->members[3].getCoord().x - 1 * 20, this->members[3].getCoord().y + 1 * 20);
			this->members[3].setCoord(four);
		} else {


			cout << "POSITION 2" << endl;
			Coord one(this->members[3].getCoord().x - 1 * 20, this->members[3].getCoord().y);
			this->members[3].setCoord(one);

			Coord two(this->members[2].getCoord().x, this->members[2].getCoord().y + 1 * 20);
			this->members[2].setCoord(two);

			Coord three(this->members[1].getCoord().x + 1 * 20, this->members[1].getCoord().y);
			this->members[1].setCoord(three);

			Coord four(this->members[0].getCoord().x + 2 * 20, this->members[0].getCoord().x + 1 * 20);
			this->members[0].setCoord(four);

		}
	}

	else {
		if (this->members[0].getCoord().y - this->members[3].getCoord().y == -2 * 20) {

			cout << "POSITION 3" << endl;
			Coord one(this->members[0].getCoord().x + 2 * 20, this->members[0].getCoord().y + 1 * 20);
			this->members[0].setCoord(one);

			Coord two(this->members[1].getCoord().x + 1 *20, this->members[1].getCoord().y);
			this->members[1].setCoord(two);

			Coord three(this->members[2].getCoord().x, this->members[2].getCoord().y + 1 *20);
			this->members[2].setCoord(three);

			Coord four(this->members[3].getCoord().x - 1 * 20, this->members[3].getCoord().y);
			this->members[3].setCoord(four);
		} else {

			cout << "POSITION 4" << endl;
			Coord one(this->members[0].getCoord().x - 1 * 20, this->members[0].getCoord().y);
			this->members[0].setCoord(one);

			Coord two(this->members[1].getCoord().x, this->members[1].getCoord().y + 1 * 20);
			this->members[1].setCoord(two);

			Coord three(this->members[2].getCoord().x + 1 * 20, this->members[2].getCoord().y);
			this->members[2].setCoord(three);

			Coord four(this->members[3].getCoord().x + 2 * 20, this->members[3].getCoord().y + 1 *20 );
			this->members[3].setCoord(four);

		}


	}

	//if heavy is on, then this rotate should drop the shape by 1
	if(this->heavy_flag){
		for(int i=0;i<4;i++){
			Coord c(this->members[i].getCoord().x, this->members[i].getCoord().y + 1);
			this->members[i].setCoord(c);
		}
	}
}

void SShape::counterclockwise(){}

vector<Coord> SShape::getMembers(){
	vector<Coord> coords;
	//for the length of the vector of cells
	for(int i=0;i<4;i++){
		if(this->members[i].isFilled()){
			coords.emplace_back(this->members[i].getCoord());
		}
	}
	return coords;
}

string SShape::getName(){
	return this->type_name;
}

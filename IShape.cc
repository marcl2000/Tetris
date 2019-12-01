#include "IShape.h"
#include <iostream>
#include <string>
#include <vector>
#include "shape.h"
#include "cell.h"
#include "level.h"

using namespace std;

void IShape::move_left(int n){
	for (int i=0; i < 4; ++i) {
		int newx = this->members[i].getCoord().x - n * 20;
		Coord c(newx, this->members[i].getCoord().y);
		this->members[i].setCoord(c);
	}

	for (int i=0; i < 4; ++i) {
		while (this->members[i].getCoord().x < 0) {
			this->move_right(1);
		}
	}
}

void IShape::move_right(int n){
	for (int i=0; i < 4; ++i) {
		int newx = this->members[i].getCoord().x + n * 20;
		Coord c(newx, this->members[i].getCoord().y);
		this->members[i].setCoord(c);
	}

	for (int i=0; i < 4; ++i) {
		while (this->members[i].getCoord().x > 10 * 20) {
			this->move_left(1);
		}
	}
}

void IShape::move_down(){
	//main has concluded that it is possible to move down
	for(int i=0;i<4;i++){
		int n = this->members[i].getCoord().x;
		int m = this->members[i].getCoord().y + 20;
		Coord c(n,m);
		this->members[i].setCoord(c);
	}
}

void IShape::clockwise(){
	if(this->members[0].getCoord().y == this->members[1].getCoord().y){
		//we are horizontal and it can always be rotated

		//check if in position 1 or 3
		if(this->members[0].getCoord().x < this->members[1].getCoord().x){

			Coord one(this->members[0].getCoord().x, this->members[0].getCoord().y - 3*20);
			this->members[0].setCoord(one);

			Coord two(this->members[1].getCoord().x - 1*20, this->members[1].getCoord().y - 2*20);
			this->members[1].setCoord(two);

			Coord three(this->members[2].getCoord().x - 2*20, this->members[2].getCoord().y - 1*20);
			this->members[2].setCoord(three);

			Coord four(this->members[3].getCoord().x -3*20, this->members[3].getCoord().y);
			this->members[3].setCoord(four);
		}
		else{
			Coord one(this->members[3].getCoord().x, this->members[3].getCoord().y - 3*20);
			this->members[3].setCoord(one);

			Coord two(this->members[2].getCoord().x - 1*20, this->members[2].getCoord().y - 2*20);
			this->members[2].setCoord(two);

			Coord three(this->members[1].getCoord().x - 2*20, this->members[1].getCoord().y - 1*20);
			this->members[1].setCoord(three);

			Coord four(this->members[0].getCoord().x -3*20, this->members[0].getCoord().y);
			this->members[0].setCoord(four);

		}
	}
	else{
		//we are vertical, check if it can be rotated
		if(this->members[0].getCoord().x <= 7){

			//check if in position 2 or 4
			if(this->members[0].getCoord().y > this->members[1].getCoord().y){

				Coord one(this->members[0].getCoord().x, this->members[0].getCoord().y);
				this->members[0].setCoord(one);

				Coord two(this->members[1].getCoord().x + 1*20, this->members[1].getCoord().y + 1*20);
				this->members[1].setCoord(two);

				Coord three(this->members[2].getCoord().x + 2*20, this->members[2].getCoord().y + 2*20);
				this->members[2].setCoord(three);

				Coord four(this->members[3].getCoord().x + 3*20, this->members[3].getCoord().y + 3*20);
				this->members[3].setCoord(four);
			}
			else{
				Coord one(this->members[3].getCoord().x, this->members[3].getCoord().y);
				this->members[3].setCoord(one);

				Coord two(this->members[2].getCoord().x + 1*20, this->members[2].getCoord().y + 1*20);
				this->members[2].setCoord(two);

				Coord three(this->members[1].getCoord().x + 2*20, this->members[1].getCoord().y + 2*20);
				this->members[1].setCoord(three);

				Coord four(this->members[0].getCoord().x + 3*20, this->members[0].getCoord().y + 3*20);
				this->members[0].setCoord(four);

			}
		}
	}


        //if heavy is on, then this rotate should drop the shape by 1
        if(this->heavy_flag){
                for(int i=0;i<4;i++){
                        Coord c(this->members[i].getCoord().x, this->members[i].getCoord().y + 20);
                        this->members[i].setCoord(c);
                }
        }

}

// For diagonally symmetrical shapes such as I, S, Z, and O, rotating clockwise 
// has the same effect as rotating counterclockwise

void IShape::counterclockwise(){
	this->clockwise();
}

vector<Coord> IShape::getMembers(){
	vector<Coord> coords;
	//for the length of the vector of cells
	for(int i=0;i<4;i++){
		if(this->members[i].isFilled()){
			coords.emplace_back(this->members[i].getCoord());
		}
	}
	return coords;
}

string IShape::getName(){
	return this->type_name;
}

std::vector<Cell>& IShape::getCells(){
	return this->members;
}

int IShape::getLevel(){
       return this->level_placed;
}

bool IShape::wasScored(){
	return this->scored;
}

void IShape::setScored(){
       this->scored = true;
}


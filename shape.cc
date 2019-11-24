#include "shape.h"
#include "coord.h"
#include <vector>

using namespace std;

void Shape::move_left(){
}

void Shape::move_right(){

}

void Shape::move_down(){
	//main has concluded that it is possible to move down
	for(int i=0;i<4;i++){
		int n = this->members[i].getCoord().x;
		int m = this->members[i].getCoord().y + 20;
		Coord c(n,m);
		this->members[i].setCoord(c);
	}
}

//should change make_blind to false after dropping and change the cells in the shape to is_filled()
void Shape::drop(){
	//the main will delete the old shape
	
	//check to see if it can be dropped


}

void Shape::clockwise(){

	if(this->type_name == "I"){
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
				Coord c(this->members[i].getCoord().x, this->members[i].getCoord().y + 1);
				this->members[i].setCoord(c);
			}
		}
	}

	//if(this->type_name == "J"){
}

void Shape::counterclockwise(){

}

vector<Coord> Shape::getMembers(){
	vector<Coord> coords;
	//for the length of the vector of cells
	for(int i=0;i<4;i++){
		if(this->members[i].isFilled()){
			coords.emplace_back(this->members[i].getCoord());
		}
	}
	return coords;
}

string Shape::getName() {
	return this->type_name;
}

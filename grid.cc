#include "grid.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//the textdisplay to be updated is passed as parameter
void Grid::init(TextDisplay *td){

	//create lines and push them into the vector of lines contained in grid
	for(int i=0;i<18;i++){

		Line l(i, td);               //update the textdisplay with these cells that are created in line
		lines.emplace_back(l);
	}
}	
	
void Grid::change_blind(bool b){
	this->blind_flag = b;
}

bool Grid::piece_fits(string name){***************

}

void Grid::print(){
	this->td->print(this->blind_flag);
}

int Grid::lines_cleared(Line l){
	//lines will actually be cleared in the line class
	int count = 0;

	//loop through the vector of lines and check how many are filled
	for(int i=0;i<18;i++){
		if(this->lines[i].is_filled()){
			count++;
		}
	}

	return count;
}

void Grid::set_gd(GraphicsDisplay *gd){
	this->gd = gd;
}



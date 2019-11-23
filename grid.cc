#include "grid.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//called by the main after initializing a textdisplay with a unique pointer
void Grid::init(TextDisplay *td, int position){

	//create lines and push them into the vector of lines contained in grid
	for(int i=0;i<18;i++){

		Line l(i, td);               //update the textdisplay with these cells that are created in line
		lines.emplace_back(l);
	}

	td->setDisplay(position, this);
}	

//called by the main when the user wants to play the blind option
void Grid::change_blind(bool b){
	this->blind_flag = b;
}

//called by the main to determine if the game is over
bool Grid::piece_fits(string name){***************
	return true;//temporay placeholder, delete once code is added
}

//called by the main (is passed on to textdisplay)
void Grid::print(){
	this->td->print(this->blind_flag);
}

//called by the main (on the grid)
int Grid::lines_cleared(){
	//lines will actually be cleared in the line class
	int count = 0;

	//loop through the vector of lines and check how many are filled
	for(int i=0;i<18;i++){
		if(this->lines[i].isFilled()){
			count++;
		}
	}

	return count;
}

//called by the main when it is determined that the user wants graphics
void Grid::set_gd(GraphicsDisplay *gd){
	this->gd = gd;
}



#include "grid.h"
#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"
#include "graphicsdisplay.h"

using namespace std;

Grid::~Grid(){
	if(this->name == "g1"){
		delete td;
		delete gd;
	}
}

//called by the main twice
void Grid::init(string name){
	this->name = name;

	//create lines and push them into the vector of lines contained in grid
	for(int i=0;i<18;i++){

		Line l;               //update the textdisplay with these cells that are created in line
		l.init(i);
		l.set_td(this->td);
		l.set_gd(this->gd);

		lines.emplace_back(l);
	}

	//td->setDisplay(position, this);
}	

//called by the main when the user wants to play the blind option
void Grid::change_blind(bool b){
	this->blind_flag = b;
}

//called by the main to determine if the game is over
bool Grid::piece_fits(string name){
	bool temp = true;
	return temp;//temporay placeholder, delete once code is added
}

vector<Line>& Grid::get_lines(){
	return this->lines;
}

void Grid::add_shape(Shape * sh){
	this->shapes.emplace_back(sh);
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

	//now, shift all the pieces downwards if there were any lines cleared (make sure to make each cell filled again)
	if(count>0){}

	return count;
}

//called by the main when it is determined that the user wants graphics
void Grid::set_gd(GraphicsDisplay *gd){
	this->gd = gd;
}

void Grid::set_td(TextDisplay *td){
	this->td = td;
}


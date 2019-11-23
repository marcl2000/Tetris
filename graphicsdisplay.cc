#include "graphicsdisplay.h"
#include "window.h"
#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "coord.h"

using namespace std;

//initialized in the main, and then set to each grid
GraphicsDisplay::GraphicsDisplay(){

	//a 26 by 11 grid of black squares, then 3 columns of white squares, then another grid
	
	/*
	for(int i=0;i<11;i++){
		for(int j=0;j<26;j++){
			xw.fillRectangle(i*20, j*20, 20, 20, 1);
		}
	}
	for(int i=14;i<25;i++){
		for(int j=0;j<26;j++){
			xw.fillRectangle(i*20, j*20, 20, 20, 1);

		}
	}

	*/

	//xw.fillRectangle(0, 140, 20, 20, 1);

	//print the level and player strings
	xw.drawString(1, 20, "Level: ", 1);
	xw.drawString(1, 40, "Score: ", 1);
	xw.drawString(1, 60, "-----------", 1);
	xw.drawString(1, 22*20, "___________ ", 1);
	xw.drawString(1, 23*20, "Next: ", 1);
	xw.drawString(14*20 + 1, 20, "Level: ", 1);
	xw.drawString(14*20 + 1, 40, "Score: ", 1);
	xw.drawString(14*20 + 1, 60, "-----------", 1);
	xw.drawString(14*20 + 1, 22*20, "___________ ", 1);
	xw.drawString(14*20 + 1, 23*20, "Next: ", 1);



}

//called by the main or shape class when something happens to next* (is created or is changed)
void GraphicsDisplay::update_shape(string name, vector<Coord> coords) {

	//this new shape must be displayed on the board with a colour for each colour
	if(name == "I"){
		int size = coords.size();
		for(int i=0;i<size;i++){
			this->xw.fillRectangle(coords[i].x, coords[i].y, 20, 20, 2);
		}
	}
}

void GraphicsDisplay::delete_shape(vector<Coord> coords){
	int size = coords.size();
	for(int i=0;i<size;i++){
		this->xw.fillRectangle(coords[i].x, coords[i].y, 20, 20, 0);
	}
}
//else if (name == "" ...






//called by Line class from within is_filled(), once it realizes it must delete itself
void GraphicsDisplay::update_line(vector<Cell> cells) {

	//loop through the cells on that row and set them back to black
	//for(int i=0;i<11;i++){



}




#include "graphicsdisplay.h"
#include "window.h"
#include <iostream>
#include <string>
#include <vector>
#include "cell.h"

using namespace std;

//initialized in the main, and then set to each grid
GraphicsDisplay::GraphicsDisplay(){

	//an 18 by 11 grid of black squares, then a column of white squares, then another grid
	for(int i=0;i<11;i++){
		for(int j=0;j<37;j++){
			if(j == 17){
				xw.fillRectangle(i*20, j*20, 20, 20, 0);
			}
			else{
				xw.fillRectangle(i*20, j*20, 20, 20, 1);
			}
		}
	}
}

//called by the main or shape class when something happens to next* (is created or is changed)
void GraphicsDisplay::update_shape(string name, vector<Cell*> cells) {

	//this new shape must be displayed on the board with a colour for each colour
	if(name == "I"){
		for(int i=0;i<4;i++){
			if(cells[i]->is_filled()){
				xw.fillRectangle(cells[i]->x * 20, cells[i]->y * 20, 20, 20, 2);
			}
		}
	}
	else if (name == "" ...


	

}

//called by Line class from within is_filled(), once it realizes it must delete itself
void GraphicsDisplay::update_line(vector<Cell> cells) {

	//loop through the cells on that row and set them back to black
	for(int i=0;i<11;i++){
		
		
	
}




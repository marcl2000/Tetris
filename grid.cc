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

		if (gd_on) {
			delete gd;
		}
	}
	int size = this->shapes.size();
	for (int i = 0; i < size; ++i) {
		delete this->shapes[i];
	}
}

void Grid::deleteShape() {
	int size = this->shapes.size();
	for (int i = 0; i < size; ++i) {
		delete this->shapes[i];
	}
}

//called by the main twice
void Grid::init(string name, bool gd_on){
	this->name = name;
	this->gd_on = gd_on;
	vector <Shape *> s;
	this->shapes = s;

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
bool Grid::piece_fits(vector<Coord> coords){
	//If overlapping any piece on the grid, we are done for sure

	bool can_move = true;
	for(int i=0;i<4;i++){
		int n = coords[i].y/20 - 3;
		int m = coords[i].x/20;

		if((n >= 18) || ((this->get_lines()[n].get_cells()[m]).isFilled())){
			can_move = false;
			break;
		}
	}

	return can_move;
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
	int grid = 0;

	if (name == "g1") {
		grid = 1;
	} else {
		grid = 2;
	}

	//loop through the vector of lines and check how many are filled
	for(int i=0;i<18;i++){
		if(this->lines[i].isFilled(grid)){
			count++;
		}
	}

	//now, shift all the pieces downwards if there were any lines cleared (make sure to make each cell filled again
	if(count>0){
		int dropCount = 1;
		while (dropCount > 0) {
			dropCount = 0;
			int s = this->shapes.size();
			for (int i = 0; i < s; ++ i) {

				bool can_move = true;
				int move_count = 0;
				while(can_move){
					for(int j=0;j<4;j++){

						int n = this->shapes[i]->getMembers()[j].y/20 - 2;
						int m = this->shapes[i]->getMembers()[j].x/20;

						if((n >= 18) || ((this->get_lines()[n].get_cells()[m]).isFilled())){
							can_move = false;
							break;
						}
					}

					if(can_move){
						move_count++;
						if(move_count==1){
							++dropCount;
							int g;
							if (this->name == "g1") {
								g = 1;
							} else {
								g = 2;
							}
							gd->clear(this->shapes[i]->getMembers(), g);
							td->clear(this->shapes[i]->getMembers(), g);

						}
						this->shapes[i]->move_down();
					}
				}

			}
		}
	}

	return count;
}

//called by the main when it is determined that the user wants graphics
void Grid::set_gd(GraphicsDisplay *gd){
	this->gd = gd;
}

void Grid::set_td(TextDisplay *td){
	this->td = td;
}


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

void Grid::clear_cells(){
	for(int i=0;i<18;i++){
		this->lines[i].clear_cells();
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
		l.init(i, gd_on);
		l.set_td(this->td);
		l.set_gd(this->gd);   //this will be nullptr if gd_on = false

		lines.emplace_back(l);
	}
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
vector<int> Grid::lines_cleared(){
	//lines will actually be cleared in the line class
	int count = 0;
	int grid = 0;
	vector<int> result;

	if (name == "g1") {
		grid = 1;
	} else {
		grid = 2;
	}

	//loop through the vector of lines and check how many are filled
	for(int i=0;i<18;i++){
		if(this->lines[i].isFilled(grid)){
			count++;

			//set the shape cells to false
			int size = shapes.size();
			for(int j=0;j<size;j++){
				for(int k=0;k<4;k++){
					if(shapes[j]->getCells()[k].getCoord().y/20 - 3 == i){
						shapes[j]->getCells()[k].set_filled(false);

						//this is where you would check to see if the entire piece has been set to false. if so, then add it to the score?
						//use get_level, a shape function
					}
				}

				bool pieces_left = false;
				for(int k=0;k<4;k++){
					if(shapes[j]->getCells()[k].isFilled()){
							pieces_left = true;
							break;
					}
				}
				if(!pieces_left && !shapes[j]->wasScored()){
					result.emplace_back(shapes[j]->getLevel());
					
					//set the piece to scored
					shapes[j]->setScored();
				}
			}
		}
	}

	//now, add the count
	result.emplace_back(count);

	//now, shift all the pieces downwards if there were any lines cleared (make sure to make each cell filled again
	if(count>0){
		int dropCount = 1;
		while (dropCount > 0) {
			dropCount = 0;

			int s = this->shapes.size();
			for (int i = 0; i < s; i++) {

				bool can_move = true;
				int move_count = 0;
				while(can_move){

					//do not move any pieces that are completely wiped out
					int filled_count = 0;
					for(int k=0;k<4;k++){
						if(this->shapes[i]->getCells()[k].isFilled()){
							++filled_count;
						}
					}
					if(filled_count == 0){
						can_move = false;
					}

					int shift=0;

					//for pieces that still have cells on the board...
					for(int p=0;p<4;p++){

						if(!(this->shapes[i]->getCells()[p].isFilled())){
							shift++;
						}

						if(this->shapes[i]->getCells()[p].isFilled()){
							int n = this->shapes[i]->getMembers()[p-shift].y/20 - 2;
							int m = this->shapes[i]->getMembers()[p-shift].x/20;

							bool to_check = true;
							for(int h=0;h<4;h++){

								if(((shapes[i]->getCells()[p].getCoord().y - shapes[i]->getCells()[h].getCoord().y) == -20) 
										&& (shapes[i]->getCells()[p].getCoord().x - shapes[i]->getCells()[h].getCoord().x == 0)
										&& (shapes[i]->getCells()[h].isFilled())){
									to_check = false;
									break;
								}
							}

							if((n >= 18) || (((this->get_lines()[n].get_cells()[m]).isFilled()) && to_check)){
								can_move = false;
								break;
							}

						}
					}

					if(can_move){

						++dropCount;
						int g;
						if (this->name == "g1") {
							g = 1;
						} else {
							g = 2;
						}

						if(gd_on){
							gd->clear(this->shapes[i]->getMembers(), g);
						}
						td->clear(this->shapes[i]->getMembers(), g);


						int shift2 = 0;
						for(int j=0;j<4;j++){

							if(!(this->shapes[i]->getCells()[j].isFilled())){
								++shift2;
							}

							if(this->shapes[i]->getCells()[j].isFilled()){
								int n = this->shapes[i]->getMembers()[j-shift2].y/20 - 2;
								int m = this->shapes[i]->getMembers()[j-shift2].x/20;

								this->get_lines()[n].get_cells()[m].set_filled(true);
								this->get_lines()[n-1].get_cells()[m].set_filled(false);
							}
						}

						this->shapes[i]->move_down();

						if(name == "g1"){
							if(gd_on){
								gd->update_shape(shapes[i]->getName(), shapes[i]->getMembers(), 1);
							}

							td->update_shape(shapes[i]->getName(), shapes[i]->getMembers(), 1);
						}
						else{
							if(gd_on){
								gd->update_shape(shapes[i]->getName(), shapes[i]->getMembers(), 2);
							}
							td->update_shape(shapes[i]->getName(), shapes[i]->getMembers(), 2);
						}

					}
				}

			}
		}
	}

	return result;
}

//called by the main when it is determined that the user wants graphics
void Grid::set_gd(GraphicsDisplay *gd){
	this->gd = gd;
}

void Grid::set_td(TextDisplay *td){
	this->td = td;
}


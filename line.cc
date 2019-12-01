#include "line.h"
#include "cell.h"
#include <string>
#include <vector>
#include "coord.h"

using namespace std;

void Line::init(int i, bool gd_on){
	this->row_number = i;
	this->gd_on = gd_on;

	//set the contents (all cells must be set to false)
	for(int j=0;j<11;j++){
		Coord co(i, j);
		Cell c("", co, false);
		this->contents.emplace_back(c);
	}
}

void Line::set_td(TextDisplay *td){
	this->td = td;
}

void Line::set_gd(GraphicsDisplay *gd){
	this->gd = gd;
}

bool Line::isFilled(int grid_num){

	bool temp = true;
	for(int i=0;i<11;i++){
		if(!this->contents[i].isFilled()){
			temp = false;
			break;
		}
	}

	//if it is filled, make sure to update both the textdisplay and graphicsdisplay, and set each cell in the line to not_filled
	if(temp){

		vector<Cell> &mem = this->get_cells();
		int n = mem.size();
			
		td->clear(this->getMembers(), grid_num);

		if(gd_on){
			gd->clear(this->getMembers(), grid_num);
		}

		for (int i = 0; i < 11; ++i) {
			mem[i].set_filled(false);
		}	
	}
	
	return temp;
}

vector<Cell>& Line::get_cells(){
	return this->contents;
}

vector<Coord> Line::getMembers(){
	vector<Coord> coords;
	for(int i=0;i<11;i++){
		if(this->contents[i].isFilled()){
			coords.emplace_back(this->contents[i].getCoord());
		}
	}
	return coords;
}

void Line::clear_cells(){
	for(int i=0;i<11;i++){
		this->contents[i].set_filled(false);
	}
}

#include "line.h"
#include "cell.h"
#include <string>
#include <vector>
#include "coord.h"

using namespace std;

void Line::init(int i){
	this->row_number = i;

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

bool Line::isFilled(){

	bool temp = true;
	for(int i=0;i<11;i++){
		if(!this->contents[i].isFilled()){
			temp = false;
			break;
		}
	}

	//if it is filled, make sure to update both the textdisplay and graphicsdisplay, and set each cell in the line to not_filled
	if(temp){
	}
	
	return temp;
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


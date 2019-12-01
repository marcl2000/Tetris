#include "cell.h"
#include <iostream>
#include <string>
#include <vector>
#include "coord.h"

using namespace std;

void Cell::set_filled(bool b){
	this->is_filled = b;
}

bool Cell::isFilled(){
	return this->is_filled;
}

Coord Cell::getCoord(){
	return this->coordinates;
}

void Cell::setCoord(Coord c){
	this->coordinates = c;
}

string Cell::getName(){
	return this->name;
}


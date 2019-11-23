#include "cell.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Cell::set_region(bool b){
	this->in_region = b;
}

void Cell::set_filled(bool b){
	this->is_filled = b;
}

bool Cell::inRegion(){
	return this->in_region;
}

bool Cell::isFilled(){
	return this->is_filled;
}


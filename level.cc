#include <iostream>
#include <vector>
#include <cstddef>
#include "shape.h"
#include "level.h"

using namespace std;

Shape * Level::createShape(string name, bool heavy_flag, bool gd_on, int level_made){
	Shape *new_shape = nullptr;
	return new_shape;
}

void Level::increaseTime() {
	++this->currTime;
}

int Level::getTime() {
	return currTime;
}

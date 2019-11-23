#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "shape.h"

class Level {

	public:
		//virtual ~Level() = 0;
		virtual Shape* createShape(std::string name, bool heavy_flag, bool gd_on);

};

#endif


#ifndef LEVELZERO_H
#define LEVELZERO_H
#include <iostream>
#include <vector>
#include <cstddef>
//#include "level.h"
#include "shape.h"

class LevelZero {
	public:
		//~LevelZero() override {}
		Shape* createShape(std::string name, bool heavy_flag, bool gd_on); // override;
};

#endif


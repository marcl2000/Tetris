#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <ctime>
#include "shape.h"

class Level {
	
	int currTime = time(NULL);

	public:
		virtual ~Level() {}
		virtual Shape* createShape(std::string name, bool heavy_flag, bool gd_on, int level_made);
		void increaseTime();
		int getTime();
};

#endif


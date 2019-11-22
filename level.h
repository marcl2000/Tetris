#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "shape.h"

class Level {

	int level = 0;

	public:
		Shape createShape();
		void levelup();
		void leveldown();
		int return_level();
}

#endif


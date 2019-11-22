#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "shape.h"

class Level {

	public:
		virtual Shape createShape();
}

#endif


#ifndef LEVELONE_H
#define LEVELONE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "shape.h"

class LevelOne {
	public:
		Shape createShape() override;
}

#endif


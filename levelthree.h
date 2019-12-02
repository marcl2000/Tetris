#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "shape.h"

class LevelThree : public Level {
	public:
		~LevelThree(){}
		Shape* createShape(std::string name, bool bonus_heavy, bool gd_on, int level_made) override;
};

#endif


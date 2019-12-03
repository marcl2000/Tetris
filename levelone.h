#ifndef LEVELONE_H
#define LEVELONE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "shape.h"

class LevelOne : public Level {
	int seed;
	public:
		~LevelOne(){}
		LevelOne(int seed): seed{seed} {};
		Shape* createShape(std::string name, bool bonus_heavy, bool gd_on, int level_made) override;
};

#endif

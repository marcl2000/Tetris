#ifndef LEVELZERO_H
#define LEVELZERO_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "shape.h"

class LevelZero : public Level {
	
	int seed;

	public:
		~LevelZero(){}
		LevelZero(int seed): seed{seed} {};
		Shape* createShape(std::string name, bool bonus_heavy, bool gd_on, int level_made) override;
};

#endif


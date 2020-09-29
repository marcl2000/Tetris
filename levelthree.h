#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "shape.h"

class LevelThree : public Level {
	
	int seed;

	public:
		~LevelThree(){}
		LevelThree(int seed): seed{seed} {};
		Shape* createShape(std::string name, bool bonus_heavy, bool gd_on, int level_made) override;
};

#endif


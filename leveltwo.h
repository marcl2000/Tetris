#ifndef LEVELTWO_H
#define LEVELTWO_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "level.h"
#include "shape.h"

class LevelTwo : public Level {
	public:
		~LevelTwo(){}
		Shape* createShape(std::string name, bool bonus_heavy, bool gd_on, int level_made) override;
};

#endif

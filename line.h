#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"

class Line {

	std::vector<Cell> contents;

	bool is_filled = false;
	int count = 0;

	public:
		bool isFilled();
};

#endif


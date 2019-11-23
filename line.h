#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"

//forward declarations
class TextDisplay;

class Line {

	std::vector<Cell> contents;

	bool is_filled = false;
	int count = 0;
	int i;
	TextDisplay *td;

	public:
		Line(int i): i{i} {}
		bool isFilled();
};

#endif


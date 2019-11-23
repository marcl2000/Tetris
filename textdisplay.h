#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "shape.h"

//forward declarations
class Cell;

class TextDisplay {
	std::vector<std::vector<std::string>>  firstDisplay;
	std::vector<std::vector<std::string>>  secondDisplay;
	public:
		void init();
		void print(bool b);      //accepts a bool to determine whether to print with the blind flag
		void setShape(int display, Shape &s);
		void clearLine(int display); // clears the last line of the textdisplay, from main (or grid) we keep checking if
				  // if the last line is full, and call clearLine() on the td as much as needed?
};

#endif


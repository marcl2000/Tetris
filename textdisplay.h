#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <cstddef>

//forward declarations
class Cell;

class TextDisplay {

	std::vector<Cell*> firstDisplay;
	std::vector<Cell*> secondDisplay;

	public:
		void init();
		void print(bool b);      //accepts a bool to determine whether to print with the blind flag
}

#endif


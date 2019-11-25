#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "shape.h"

//forward declarations
class Cell;

class TextDisplay {
	std::vector<std::vector<std::string>> theDisplay;
	public:
		void init();
		void update_next(std::string name, int grid_number); 
		void print(bool blind_flag);
		void update_shape(std::string name, std::vector<Coord> coords, int grid_number);
		void delete_shape(std::vector<Coord>, int grid_number);
		void clearLine(std::vector<Coord>, int grid_number);
		void update_level(int new_level);
		void update_score(int new_score);
};

#endif


#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include "window.h"
#include "cell.h"

//forward declarations
class Shape;
class Line;

class GraphicsDisplay {

	Xwindow xw;
	int row = 26;
	int col = 25;

	public:

		//assuming the user wishes to play with the graphics turned on
		GraphicsDisplay();
		void update_shape(std::string name, std::vector<Coord> coords);
		void update_line(std::vector<Cell> cells);
		void delete_shape(std::vector<Coord> coords);
};

#endif


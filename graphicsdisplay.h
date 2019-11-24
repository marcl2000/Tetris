#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include "window.h"
#include "cell.h"
#include "coord.h"



class GraphicsDisplay {

	Xwindow xw;
	int row = 26;
	int col = 25;

	public:

		//assuming the user wishes to play with the graphics turned on
		GraphicsDisplay();
		void update_shape(std::string name, std::vector<Coord> coords, int grid_number);
		void update_line(std::vector<Cell> cells, int grid_number);
		void delete_shape(std::vector<Coord> coords, int grid_number);
		void update_next(std::string name, std::vector<Coord> coords, int grid_number);
};

#endif


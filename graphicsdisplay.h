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
		GraphicsDisplay();
		void update_shape(std::string name, std::vector<Coord> coords, int grid_number);
		void clear(std::vector<Coord> coords, int grid_number);
		void update_next(std::string name, std::vector<Coord> coords, int grid_number);
		void clear_current(int grid_number);
		void clear_next(int grid_number);
		void update_level(int new_level, int grid_number);
		void update_score(int new_score, int grid_number);
		void restart();
};

#endif


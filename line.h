#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "coord.h"
#include "graphicsdisplay.h"
#include "textdisplay.h"

//forward declarations
class TextDisplay;

class Line {

	std::vector<Cell> contents;

	bool is_filled = false;
	int row_number;
	TextDisplay *td;
	GraphicsDisplay *gd;

	public:
		void init(int i);
		bool isFilled(int grid_num);
		std::vector<Cell>& get_cells();
		void set_td(TextDisplay *td);
		void set_gd(GraphicsDisplay *gd);
		std::vector<Coord> getMembers();
		void clear_cells();
};

#endif


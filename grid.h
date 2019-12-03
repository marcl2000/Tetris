#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "line.h"
#include <string>

//forward declarations
class TextDisplay;
class GraphicsDisplay;
class Shape;
class Line;

class Grid {

	std::string name;
	int gridRows = 18;
	int gridCols = 11;

	std::vector<Line> lines; 
	std::vector<Shape *> shapes;

	bool blind_flag = false;
	bool gd_on = true;            //the command line arg -text turns this off
	
	//unique pointers
	TextDisplay *td = nullptr;
	GraphicsDisplay *gd = nullptr;

	public:
		~Grid();
		void deleteShape();
		void clear_cells();
		void init(std::string name, bool gd_on);
		void change_blind(bool b);
		bool piece_fits(std::vector<Coord> coords);    //if this returns false, then the game is over
		void add_shape(Shape *sh);
		std::vector<Line>& get_lines();
		void print();
		std::vector<int> lines_cleared();
		void set_gd(GraphicsDisplay *gd);
		void set_td(TextDisplay *td);
		bool isFilled(Coord c);
};
#endif



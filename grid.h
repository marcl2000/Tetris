#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "line.h"
#include "shape.h"
#include <string>
//#include <memory>

//forward declarations
class TextDisplay;
class GraphicsDisplay;

class Grid {

	std::string name;
	int gridRows = 18;
	int gridCols = 11;

	std::vector<Line> lines; 
	std::vector<Shape *> shapes;

	bool is_finished = false;
	bool blind_flag = false;
	bool gd_on = true;            //the command line arg -text turns this off
	
	//unique pointers
	TextDisplay *td = nullptr;
	GraphicsDisplay *gd = nullptr;

	public:
		~Grid();
		void init(std::string name);
		void change_blind(bool b);
		bool piece_fits(std::string name);
		void print();
		int lines_cleared();
		void set_gd(GraphicsDisplay *gd);
		void set_td(TextDisplay *td);
};
#endif



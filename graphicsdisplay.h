#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "window.h"

//forward declarations
class Shape;
class Line;

class GraphicsDisplay {

	xWindow xw(740,220);
	int row = 18;
	int col = 11;

	public:

		//assuming the user wishes to play with the graphics turned on
		GraphicsDisplay();
		void update_shape(Shape *);
		void update_line(Line *);
}

#endif


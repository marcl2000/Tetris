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

	xWindow xw;

	public:

		//assuming the user wishes to play with the graphics turned on
		void init();
		void update_shape(Shape *);
		void update_line(Line *);
}

#endif


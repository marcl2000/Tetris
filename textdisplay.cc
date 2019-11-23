#include "textdisplay.h"
#include "cell.h"
#include "coord.h"
#include <vector>
#include <string>
using namespace std;

void textdisplay::init() 
	for (int i = 0; i <= 18; ++i) {
		for (int j = 0; j <= 11; ++j) {
			// Fill each row of each grid with 11 cells
			firstDisplay[i].emplace_back("_");
			secondDisplay[i].emplace_back("_");
		}
	}
}

void textdisplay::print(bool b) {
	for (int i = 0; i < 18; ++i) {
		// Print out user1's row
		for (int j = 0; j < 11; ++j) {
			cout << firstDisplay[i][j];
		}
		cout << "          ";
		// Print out user2's row
	       	for (int k = 0; k < 18; ++k) {
			cout << secondDisplay[i][k];
	       	}	       
	       	cout << endl;
	}
	cout << "-----------          -----------" << endl;
	
}

void TextDisplay::setShape(int display, Shape &s) {	
	vector<Coord> cells = s.getMembers();
	for (auto i: cells) {
			if (display == 1) {
				this->firstDisplay[cells[i].x][cells[i].y] = s.type_name;
			} else {
				this->secondDisplay[cells[i].x][cells[i].y] = s.type_name;
			}
	}
}

void clearLine(int display) {

	//Create a new vector to be inserted at the top of the grid
	vector<string> newv;
        for (int i = 0, i < 11; ++i) {
		newv[i].push_back("_");
	}

	// Pop off the last vector and insert the new vector at the beginning of the specified grid
	if (display == 1) {
		firstDisplay.pop_back;
		firstDisplay.insert(firstDisplay.begin(), newv);
	} else {
		secondDisplay.pop_back();
		secondDisplay.insert(secondDisplay.begin(), newv);
	}
}

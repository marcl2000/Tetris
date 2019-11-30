#include "graphicsdisplay.h"
#include "window.h"
#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "coord.h"

using namespace std;

//initialized in the main, and then set to each grid
GraphicsDisplay::GraphicsDisplay(){
	
	//print the level and player strings
	xw.drawString(1, 20, "Level: ", 1);
	xw.drawString(1, 40, "Score: ", 1);
	xw.drawString(1, 60, "-------------------------------------", 1);
	xw.drawString(1, 21*20, "_____________________________________", 1);
	xw.drawString(1, 22*20, "Next: ", 1);
	xw.drawString(14*20 + 1, 20, "Level: ", 1);
	xw.drawString(14*20 + 1, 40, "Score: ", 1);
	xw.drawString(14*20 + 1, 60, "-------------------------------------", 1);
	xw.drawString(14*20 + 1, 21*20, "_____________________________________", 1);
	xw.drawString(14*20 + 1, 22*20, "Next: ", 1);



}

void GraphicsDisplay::restart() {
	xw.fillRectangle(0,0,500, 520 ,0);
        /*
	for(int j=0;j<26;j++){
                        xw.fillRectangle(i*20, j*20, 20, 20, 0);
                }
        }
        for(int i=14;i<25;i++){
                for(int j=0;j<26;j++){
                        xw.fillRectangle(i*20, j*20, 20, 20, 0);

                }
        }
	*/

	//print the level and player strings
        xw.drawString(1, 20, "Level: ", 1);
        xw.drawString(1, 40, "Score: ", 1);
        xw.drawString(1, 60, "-------------------------------------", 1);
        xw.drawString(1, 21*20, "_____________________________________", 1);
        xw.drawString(1, 22*20, "Next: ", 1);
  	xw.drawString(14*20 + 1, 20, "Level: ", 1);
        xw.drawString(14*20 + 1, 40, "Score: ", 1);
        xw.drawString(14*20 + 1, 60, "-------------------------------------", 1);
        xw.drawString(14*20 + 1, 21*20, "_____________________________________", 1);
        xw.drawString(14*20 + 1, 22*20, "Next: ", 1);

}
//called by the main or shape class when something happens to next* (is created or is changed)
void GraphicsDisplay::update_shape(string name, vector<Coord> coords, int grid_number) {

	int n = 0;
	if(grid_number == 2){
		n = 14*20;
	}

	//this new shape must be displayed on the board with a colour for each shape
	if(name == "I"){
		int size = coords.size();
		for(int i=0;i<size;i++){
			this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 2);
		}
	} else if (name == "J") {
	 	int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 3);
                }
	} else if (name == "S") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 4);
                }
        } else if (name == "L") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 5);
                }
        } else if (name == "O") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 6);
                }
        } else if (name == "T") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 7);
                }
        } else if (name == "Z") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 8);
                }
        }
}


void GraphicsDisplay::clear(std::vector<Coord> coords, int grid_number){

	int n = 0;
	if(grid_number == 2){
		n = 14*20;
	}

	int size = coords.size();
	if(!(size == 11)){
		for(int i=0;i<size;i++){
			this->xw.fillRectangle(coords[i].x + n, coords[i].y, 20, 20, 0);
		}
	}
	else{
		for(int i=0;i<size;i++){
			this->xw.fillRectangle(coords[i].y*20, (coords[i].x+3)*20 + n, 20, 20, 0);
		}
	}
}

void GraphicsDisplay::update_next(string name, vector<Coord> coords, int grid_number){

	int n = 0;
        if(grid_number == 2){
                n = 14*20;
        }

        //this new shape must be displayed on the board with a colour for each shape
        if(name == "I"){
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 2);
                }
        } else if (name == "J") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 3);
                }
        } else if (name == "S") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 4);
                }
        } else if (name == "L") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 5);
                }
        } else if (name == "O") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 6);
                }
        } else if (name == "T") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 7);
                }
        } else if (name == "Z") {
                int size = coords.size();
                for(int i=0;i<size;i++){
                        this->xw.fillRectangle(coords[i].x + n, coords[i].y + 20 * 17, 20, 20, 8);
                }
        }

}

void GraphicsDisplay::clear_current(int grid_number) {
	int n = 14*20;
	if (grid_number == 1) {
		this->xw.fillRectangle(0, 5*20, 80, 60, 0);
	} else {
		this->xw.fillRectangle(n, 5*20, 80, 60, 0);
	}
}

void GraphicsDisplay::clear_next(int grid_number) {
	int n = 14*20;
	if (grid_number == 1) {
                this->xw.fillRectangle(0, 5*20+20*18, 80, 60, 0);
        } else {
                this->xw.fillRectangle(n, 5*20+20*18, 80, 60, 0);
        }
}

void GraphicsDisplay::update_level(int new_level, int grid_number){

        string s = "";

        if (new_level == 0) {
                s = "0";
        } else if (new_level == 1) {
                s = "1";
        } else if (new_level == 2) {
                s = "2";
        } else if (new_level == 3) {
                s = "3";
        } else if (new_level == 4) {
                s = "4";
        }
	
	if(grid_number == 1){
		xw.fillRectangle(0, 0, 20*11, 20, 0);
		xw.drawString(1, 20, "Level: "+s, 1);
	}
	else if(grid_number==2){
		xw.fillRectangle(14*20, 0, 20*11, 20, 0);
		xw.drawString(14*20 + 1, 20, "Level: "+s, 1);
	}
}

void GraphicsDisplay::update_score(int new_score, int grid_number){
	if(grid_number == 1){
		xw.drawString(1, 40, "Score: "+new_score, 1);
	}
	else if(grid_number == 2){
		xw.drawString(14*20 + 1, 40, "Score: "+new_score, 1);
	}
}



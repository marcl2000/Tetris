#include "textdisplay.h"
#include "cell.h"
#include "coord.h"
#include <vector>
#include <string>
using namespace std;

void TextDisplay::init(){
	for (int i = 0; i <= 25; ++i) {
		for (int j = 0; j < 26 ; ++j) {
			// Fill each row of each grid with 11 cells
			theDisplay[i].emplace_back(" ");
		}
	}
	//add the text
	theDisplay[0][0] = "L";
	theDisplay[0][1] = "e";
	theDisplay[0][2] = "v";
	theDisplay[0][3] = "e";
	theDisplay[0][4] = "l";
	theDisplay[0][5] = ":";
	theDisplay[0][9] = "0";
	theDisplay[0][14] = "L";
	theDisplay[0][15] = "e";
	theDisplay[0][16] = "v";
	theDisplay[0][17] = "e";
	theDisplay[0][18] = "l";
	theDisplay[0][19] = ":";
	theDisplay[0][24] = "0";

	theDisplay[1][0] = "S";
	theDisplay[1][1] = "c";
	theDisplay[1][2] = "o";
	theDisplay[1][3] = "r";
	theDisplay[1][4] = "e";
	theDisplay[0][5] = ":";
	theDisplay[0][9] = "0";
	theDisplay[1][14] = "S";
	theDisplay[1][15] = "c";
	theDisplay[1][16] = "o";
	theDisplay[1][17] = "r";
	theDisplay[1][18] = "e";
	theDisplay[1][19] = ":";
	theDisplay[1][24] = "0";

	for(int i=0;i<11;i++){
		theDisplay[3][i] = "-";
		theDisplay[3][i+14] = "-";
	}
	for(int i=0;i<11;i++){
		theDisplay[22][i] = "_";
		theDisplay[22][i+14] = "_";
	}

	theDisplay[23][0] = "N";
	theDisplay[23][1] = "e";
	theDisplay[23][2] = "x";
	theDisplay[23][3] = "t";
	theDisplay[23][4] = ":";
	theDisplay[23][14] = "N";
	theDisplay[23][15] = "e";
	theDisplay[23][16] = "x";
	theDisplay[23][17] = "t";
	theDisplay[23][18] = ":";
}

void TextDisplay::update_next(string name, int grid_number){
	int n = 0;
	if(grid_number == 2){
		n = 14;
	}
	//delete the previous next
	for(int i=0;i<4;i++){
		theDisplay[24][i+n] = " ";
		theDisplay[25][i+n] = " ";
	}

	if(name == "I"){
		theDisplay[24][0+n] = "I";
		theDisplay[24][1+n] = "I";
		theDisplay[24][2+n] = "I";
		theDisplay[24][3+n] = "I";
	}
	else if(name == "J"){
		theDisplay[24][0+n] = "J";
		theDisplay[25][0+n] = "J";
		theDisplay[25][1+n] = "J";
		theDisplay[25][2+n] = "J";
	}
	else if(name == "L"){
		theDisplay[24][2+n] = "L";
		theDisplay[25][0+n] = "L";
		theDisplay[25][1+n] = "L";
		theDisplay[25][2+n] = "L";
	}
	else if(name == "O"){
		theDisplay[24][0+n] = "O";
		theDisplay[24][1+n] = "O";
		theDisplay[25][0+n] = "O";
		theDisplay[25][1+n] = "O";
	}
	else if(name == "S"){
		theDisplay[24][1+n] = "S";
		theDisplay[24][2+n] = "S";
		theDisplay[25][0+n] = "S";
		theDisplay[25][1+n] = "S";
	}
	else if(name == "Z"){
		theDisplay[24][0+n] = "Z";
		theDisplay[24][1+n] = "Z";
		theDisplay[25][1+n] = "Z";
		theDisplay[25][2+n] = "Z";
	}
	else if(name == "T"){
		theDisplay[24][0+n] = "T";
		theDisplay[24][1+n] = "T";
		theDisplay[24][2+n] = "T";
		theDisplay[25][1+n] = "T";
	}
}

void TextDisplay::print(bool blind_flag) {
	for (int i = 0; i < 25; ++i) {
		for(int j=0;j<26;j++){
			cout<<theDisplay[i][j];
		}
		cout<<endl;
	}
}

void TextDisplay::update_shape(string name, vector<Coord> coords){}

void TextDisplay::delete_shape(vector<Coord> coords){}

void TextDisplay::clearLine(vector<Coord> coords) {}

#include "textdisplay.h"
#include "cell.h"
#include "coord.h"
#include <vector>
#include <string>
using namespace std;

void TextDisplay::init(){
	theDisplay.resize(25);
	for (int i = 0; i < 25; ++i) {
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
	theDisplay[0][10] = "0";
	theDisplay[0][14] = "L";
	theDisplay[0][15] = "e";
	theDisplay[0][16] = "v";
	theDisplay[0][17] = "e";
	theDisplay[0][18] = "l";
	theDisplay[0][19] = ":";

	theDisplay[1][0] = "S";
	theDisplay[1][1] = "c";
	theDisplay[1][2] = "o";
	theDisplay[1][3] = "r";
	theDisplay[1][4] = "e";
	theDisplay[1][5] = ":";
	theDisplay[1][10] = "0";
	theDisplay[1][14] = "S";
	theDisplay[1][15] = "c";
	theDisplay[1][16] = "o";
	theDisplay[1][17] = "r";
	theDisplay[1][18] = "e";
	theDisplay[1][19] = ":";

	for(int i=0;i<11;i++){
		theDisplay[2][i] = "-";
		theDisplay[2][i+14] = "-";
	}
	for(int i=0;i<11;i++){
		theDisplay[21][i] = "-";
		theDisplay[21][i+14] = "-";
	}

	theDisplay[22][0] = "N";
	theDisplay[22][1] = "e";
	theDisplay[22][2] = "x";
	theDisplay[22][3] = "t";
	theDisplay[22][4] = ":";
	theDisplay[22][14] = "N";
	theDisplay[22][15] = "e";
	theDisplay[22][16] = "x";
	theDisplay[22][17] = "t";
	theDisplay[22][18] = ":";
}

void TextDisplay::update_next(string name, int grid_number){
	int n = 0;
	if(grid_number == 2){
		n = 14;
	}

	//delete the previous next
	for(int i=0;i<4;i++){
		theDisplay[23][i+n] = " ";
		theDisplay[24][i+n] = " ";
	}

	if(name == "I"){
		theDisplay[23][0+n] = "I";
		theDisplay[23][1+n] = "I";
		theDisplay[23][2+n] = "I";
		theDisplay[23][3+n] = "I";
	}
	else if(name == "J"){
		theDisplay[23][0+n] = "J";
		theDisplay[24][0+n] = "J";
		theDisplay[24][1+n] = "J";
		theDisplay[24][2+n] = "J";
	}
	else if(name == "L"){
		theDisplay[23][2+n] = "L";
		theDisplay[24][0+n] = "L";
		theDisplay[24][1+n] = "L";
		theDisplay[24][2+n] = "L";
	}
	else if(name == "O"){
		theDisplay[23][0+n] = "O";
		theDisplay[23][1+n] = "O";
		theDisplay[24][0+n] = "O";
		theDisplay[24][1+n] = "O";
	}
	else if(name == "S"){
		theDisplay[23][1+n] = "S";
		theDisplay[23][2+n] = "S";
		theDisplay[24][0+n] = "S";
		theDisplay[24][1+n] = "S";
	}
	else if(name == "Z"){
		theDisplay[23][0+n] = "Z";
		theDisplay[23][1+n] = "Z";
		theDisplay[24][1+n] = "Z";
		theDisplay[24][2+n] = "Z";
	}
	else if(name == "T"){
		theDisplay[23][0+n] = "T";
		theDisplay[23][1+n] = "T";
		theDisplay[23][2+n] = "T";
		theDisplay[24][1+n] = "T";
	}
}

void TextDisplay::print(bool blind_flag, int g) {
	if (!blind_flag) {
		cout<<endl;
		for (int i = 0; i < 25; ++i) {
			for(int j=0;j<26;j++){
				cout<<theDisplay[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
	} else if (g == 1) {
		cout<<endl;
		for (int i = 0; i < 25; ++i) {
			for(int j=0;j<26;j++){
				if ((8 <= i) && (i <= 17) && (2 <= j) && (j <= 8)) {
					cout<<"?";	   
				} else {
					cout<<theDisplay[i][j];
				}
			}
			cout<<endl;
		}
		cout<<endl;

	} else {
		cout<<endl;
		for (int i = 0; i < 25; ++i) {
			for(int j=0;j<26;j++){
				if ((8 <= i) && (i <= 17) && (16 <= j) && (j <= 22)) {
					cout<<"?";
				} else {
					cout<<theDisplay[i][j];
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
}

void TextDisplay::update_shape(string name, vector<Coord> coords, int grid_number){
	int n = 0;
	if(grid_number == 2){
		n = 14;
	}

	int size = coords.size();
	for(int i=0;i<size;i++){
		if(name == "I"){
			theDisplay[coords[i].y/20][coords[i].x/20 +n] = "I";
		}
		else if(name == "J"){
			theDisplay[coords[i].y/20][coords[i].x/20 +n] = "J";

		}
		else if(name == "L"){
			theDisplay[coords[i].y/20][coords[i].x/20 +n] = "L";

		}
		else if(name == "O"){
			theDisplay[coords[i].y/20][coords[i].x/20 +n] = "O";

		}
		else if(name == "S"){
			theDisplay[coords[i].y/20][coords[i].x/20+n] = "S";

		}
		else if(name == "Z"){
			theDisplay[coords[i].y/20][coords[i].x/20 +n] = "Z";

		}
		else if(name == "T"){
			theDisplay[coords[i].y/20][coords[i].x/20 +n] = "T";

		}
	}
}

void TextDisplay::clear(vector<Coord> coords, int grid_number) {
	int n = 0;
	if (grid_number == 2) {
		n = 14;
	}	

	int size = coords.size();

	if(!(size == 11)){
		for(int i =0; i<size;i++){
			theDisplay[coords[i].y/20][coords[i].x/20 + n] = " ";
		}
	}
	else{
		for(int i=0;i<size; i++){
			theDisplay[coords[i].x + 3][coords[i].y + n] = " ";
		}
	}
}

void TextDisplay::update_level(int new_level, int grid_number){
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
		theDisplay[0][10] = s;
	}

	else if (grid_number==2){
		theDisplay[0][24] = s;
	}
}

void TextDisplay::update_score(int new_score, int grid_number){
	string s = to_string(new_score);

	if(grid_number == 1){
		theDisplay[1][10] = s;
	}
	else if(grid_number == 2){
		theDisplay[1][24] = s;
	}
}


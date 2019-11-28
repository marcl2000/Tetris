#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "graphicsdisplay.h"
#include "grid.h"
#include "textdisplay.h"
#include "level.h"
#include "levelzero.h"
#include "IShape.h"
#include "JShape.h"
#include "LShape.h"
#include "SShape.h"
#include "TShape.h"
#include "ZShape.h"
#include "OShape.h"

using namespace std;

int main(int argc, char *argv[]){	
	// Variables for program setup
	string numSteps = "";
	int steps = 1;
	string user1file = "biquadris_sequence1.txt";
	string user2file = "biquadris_sequence2.txt";
	int turn = 0;

	bool wants_graphics = true;
	bool heavy_flag = false;            //turning this on requires the user to clear a certain number of lines
	int current_level = 0;

	// If any command lines were given, interpret and apply them
	for (int i = 0; i < argc; ++i) {
		string cmd = argv[i];
		if (cmd.substr(0,2) == "-t") {
			wants_graphics = false;

		} else if (cmd.substr(0, 3) == "-se") {
			++i;
			int seed = stoi(argv[i]); 
		} else if (cmd.substr(0, 3) == "-st") {
			++i;
			int level = stoi(argv[i]);
			current_level = level;
		} else if (cmd == "-scriptfile1") {
			++i;
			string newFile = argv[i];
			user1file = newFile;
		} else if (cmd == "-scriptfile2") {
			++i;
			string newFile = argv[i];
			user2file = newFile;
		}
	}

	//make the textdisplay
	TextDisplay *td = new TextDisplay();
	td->init();

	//set up the two grids regardless
	Grid g1;
	g1.init("g1", wants_graphics);
	Grid g2;
	g2.init("g2", wants_graphics);

	//set the td
	g1.set_td(td);
	g2.set_td(td);

	GraphicsDisplay *gd = nullptr;

	//if the user wants graphics, then turn the display on
	if (wants_graphics) {
		gd = new GraphicsDisplay();
		g1.set_gd(gd);
		g2.set_gd(gd);
	}

	// Create filestreams for the blocks of each user
	ifstream u1stream {user1file};
	ifstream u2stream {user2file};
	string u1block;
	string u2block;

	u1stream >> u1block;

	//create a shape (this really needs to be Level *)
	Level *zero = new LevelZero();
	Shape *current = zero->createShape(u1block, heavy_flag, wants_graphics);

	if (wants_graphics) {
		gd->update_shape(u1block, current->getMembers(), 1);
	}
	td->update_shape(u1block, current->getMembers(), 1);

	//get the next block in line
	u1stream >> u1block;
	Shape *next1 = zero->createShape(u1block, heavy_flag, wants_graphics);
	if (wants_graphics) {
		gd->update_next(u1block, next1->getMembers(), 1);
	}
	td->update_next(u1block, 1);  //

	// Create a shape for user2
	u2stream >> u2block;
	Shape *current2 = zero->createShape(u2block, heavy_flag, wants_graphics);
	if (wants_graphics) {
		gd->update_shape(u2block, current2->getMembers(), 2);
	}
	td->update_shape(u2block, current2->getMembers(), 2);

	//get the next block for user2
	u2stream >> u2block;
	Shape * next2 = zero->createShape(u2block, heavy_flag, wants_graphics);
	if (wants_graphics) {
		gd->update_next(u2block, next2->getMembers(), 2);
	}
	td->update_next(u2block, 2);

	//now print the textdisplay
	g1.print();

	while (true) {

		//Read the first string inputted
		string s;
		cin >> s;

		// If the end of file is reached, then exit		
		if (cin.eof()) {
			break;
		}

		int len = s.length();

		// Determine if there are any digits at the beginning of the string
		for (int i = 0; i < len; ++i) {
			// If a digit is present, concantenate it to the numSteps string
			if (isdigit(s[i])) {
				numSteps = numSteps + s;
			} else {
				// If digits were present at the beginning of the string, 
				// set the steps to the amount specified in the string
				if (numSteps != "") {
					steps = stoi(numSteps);
					numSteps = "";
					s = s.substr(i, len - i);
					len = s.length();
				}		
			}
		}

		// Interpret the commands using the minimum number of characters required
		// to distinguish a command from other possible commands
		if (s.substr(0, 5) == "level") {
			if (s[5] == 'u') {
				cout << "Going up " << steps << " levels" << endl;
			} else if (s[5] == 'd') {
				cout << "Going down " << steps << " levels"  << endl;
			}
		} else if (s.substr(0, 3) == "lef") {
			if (turn%2 == 0) {
				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
				}
				td->clear(current->getMembers(), 1);
				current->move_left(steps);
				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();
			} else {
				if (wants_graphics) {
					gd->clear(current2->getMembers(), 2);
				}
				td->clear(current2->getMembers(), 2);
				current2->move_left(steps);
				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g2.print();
			}
		} else if (s.substr(0, 2) == "ri") {
			if (turn%2 == 0) {
				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
				}
				td->clear(current->getMembers(), 1);
				current->move_right(steps);
				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();
			} else {
				if (wants_graphics) {
					gd->clear(current2->getMembers(), 2);
				}
				td->clear(current2->getMembers(), 2);
				current2->move_right(steps);
				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g2.print();
			}
		} else if (s.substr(0, 2) == "do") {
			for(int i=0;i<steps;i++){
				//check to see if the block can be moved down safely
				if(turn%2 == 0){
					bool can_drop = true;
					for(int i=0;i<4;i++){
						int n = current->getMembers()[i].y/20 - 2;
						int m = current->getMembers()[i].x/20;

						if((n >= 18) || ((g1.get_lines()[n].get_cells()[m]).isFilled())){
							can_drop = false;
							break;
						}
					}
					if(can_drop){
						if (wants_graphics) {
							gd->clear(current->getMembers(), 1);
						}
						td->clear(current->getMembers(), 1);

						current->move_down();
						if (wants_graphics) {
							gd->update_shape(current->getName(), current->getMembers(), 1);
						}
						td->update_shape(current->getName(), current->getMembers(), 1);
					}
				}
				else{
					bool can_drop = true;
					for(int i =0;i<4;i++){
						int n = current2->getMembers()[i].y/20 - 2;
						int m = current2->getMembers()[i].x/20;

						if((n >= 18) || ((g2.get_lines()[n].get_cells()[m]).isFilled())){
							can_drop = false;
							break;
						}
					}
					if(can_drop){
						if (wants_graphics) {
							gd->clear(current2->getMembers(), 2);
						}
						td->clear(current2->getMembers(), 2);
						current2->move_down();
						if (wants_graphics) {
							gd->update_shape(current2->getName(), current2->getMembers(), 2);
						}
						td->update_shape(current2->getName(), current2->getMembers(), 2);
					}
				}
			}
			g1.print();

		} else if (s.substr(0, 2) == "dr") {

			//To differentiate between users, user1 will play when the turn count is
			//even and user2 will play when the turn count is odd
			if (turn % 2 == 0) {
				bool can_move = true;
				int move_count = 0;
				while(can_move){
					for(int i=0;i<4;i++){
						int n = current->getMembers()[i].y/20 - 2;
						int m = current->getMembers()[i].x/20;
						
						if((n >= 18) || ((g1.get_lines()[n].get_cells()[m]).isFilled())){
							can_move = false;
							break;
						}
					}
					if(can_move){
						move_count++;
						if(move_count==1){
							if (wants_graphics) {
								gd->clear(current->getMembers(), 1);
							}
							td->clear(current->getMembers(), 1);
						}
						current->move_down();
					}
				}
				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);

				//after dropping, add this shape to the list of shapes and set the corresponding grid cells to filled
				g1.add_shape(current);

				for(int i=0;i<4;i++){
					int n = current->getMembers()[i].y/20 - 3;
					int m = current->getMembers()[i].x/20;
					(g1.get_lines()[n].get_cells()[m]).set_filled(true);
				}
				if (wants_graphics) {
					gd->clear_current(1);
				}
				int clearCount = g1.lines_cleared();
				// calculatet the score later

				// First set the next block to the current shape
				current = next1;
				if (wants_graphics) {
					gd->update_shape(u1block, current->getMembers(),1);
				}
				td->update_shape(u1block, current->getMembers(), 1);
				u1stream >> u1block;
				if (u1stream.eof()) {
					// Clear the filestream and start reading from the beginning of the file
					u1stream.clear( );
					u1stream.seekg( 0, std::ios::beg);
					u1stream >> u1block;
				}
				if (wants_graphics) {
					gd->clear_next(1);
				}
				// Now display the next block
				next1 = zero->createShape(u1block, heavy_flag, wants_graphics);

				// Call fits function to see if the piece fits, if it doesn't the game is over
				if (!g1.piece_fits(next1->getMembers())) {
					cout << "The winner is Player 2!" << endl;
					u1stream.close();
					u2stream.close();
					delete current;
                                        delete current2;
                                        delete next1;
                                        delete next2;
					delete zero;
					return 0;	
				}
				if (wants_graphics) {
					gd->update_next(u1block, next1->getMembers(),1);
				}
				td->update_next(u1block, 1);
				g1.print();

			} else {
				bool can_move = true;
				int move_count = 0;
				while(can_move){
					for(int i=0;i<4;i++){
						int n = current2->getMembers()[i].y/20 - 2;
						int m = current2->getMembers()[i].x/20;

						if((n >= 18) || ((g2.get_lines()[n].get_cells()[m]).isFilled())){
							can_move = false;
							break;
						}
					}
					if(can_move){
						move_count++;
						if(move_count==1){

							if (wants_graphics) {
								gd->clear(current2->getMembers(), 2);
							}
							td->clear(current2->getMembers(), 2);
						}
						current2->move_down();
					}
				}
				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);

				//after dropping, add this shape to the list of shapes and set the corresponding grid cells to filled
				g2.add_shape(current2);

				for(int i=0;i<4;i++){
					int n = current2->getMembers()[i].y/20 - 3;
					int m = current2->getMembers()[i].x/20;
					(g2.get_lines()[n].get_cells()[m]).set_filled(true);
				}


				//call lines_cleared to determine if lines are cleared and shifting needs to occur
				int clearCount = g2.lines_cleared();

				// Now calaculate the score
				
				if (wants_graphics) {
					gd->clear_current(2);
				}
				
				// Repeat the above process but for user2
				current2 = next2;
				if (wants_graphics) {
					gd->update_shape(u2block, next2->getMembers(),2);
				}
				td->update_shape(u2block, current2->getMembers(), 2);
				u2stream >> u2block;
				if (u2stream.eof()) {
					u2stream.clear( );
					u2stream.seekg( 0, std::ios::beg);
					u2stream >> u2block;
				}
				if (wants_graphics) {
					gd->clear_next(2);
				}
				next2 = zero->createShape(u2block, heavy_flag, wants_graphics);

				//call the function to check if the game is over (does the next piece fit on the grid)
				if (!g2.piece_fits(next2->getMembers())) {
					u1stream.close();
					u2stream.close();
					delete current;
					delete current2;
					delete next1;
					delete next2;
					delete zero;
					return 0;
				}
				if (wants_graphics) {
					gd->update_next(u2block, next2->getMembers(),2);
				}
				td->update_next(u2block, 2);
				g2.print();
			}
			++turn;
		} else if (s.substr(0, 2) == "co") {
		} else if (s.substr(0, 2) == "cl") {                     
			for(int i=0;i<steps;i++){
				if(turn % 2 == 0){   //first player's block
					if (wants_graphics) {
						gd->clear(current->getMembers(), 1);
					}
					td->clear(current->getMembers(), 1);
					current->clockwise();
					if (wants_graphics) {
						gd->update_shape(current->getName(), current->getMembers(), 1);
					}
					td->update_shape(current->getName(), current->getMembers(), 1);
					g1.print();
				}

				else{  //second player's block
					if (wants_graphics) {
						gd->clear(current2->getMembers(), 2);
					}
					td->clear(current2->getMembers(), 2);
					current2->clockwise();
					if (wants_graphics) {
						gd->update_shape(current2->getName(), current2->getMembers(), 2);
					}
					td->update_shape(current2->getName(), current2->getMembers(), 2);
					g1.print();
				}
			}

		} else if (s.substr(0, 2) == "ra") {
		} else if (s[0] == 'n') {
			string file = "";
			cin >> file;
		} else if (s.substr(0, 2) == "re") {
			turn = 0;
			delete td;
			td = new TextDisplay;
			td->init();

			if (wants_graphics) {
				gd->restart();
			}
			
			g1.deleteShape();
			g2.deleteShape();
			
			delete current;
			delete current2;
			delete next1;
			delete next2;
			
			//set up the two grids regardless
			g1.init("g1", wants_graphics);
			g2.init("g2", wants_graphics);

			//set the td
			g1.set_td(td);
			g2.set_td(td);

			// Clear the filestream and start reading from the beginning of the file
			u1stream.clear( );
			u1stream.seekg( 0, std::ios::beg);
			u1stream >> u1block;

			u2stream.clear( );
			u2stream.seekg( 0, std::ios::beg);
			u2stream >> u2block;


			//create a shape (this really needs to be Level *)
			current = zero->createShape(u1block, heavy_flag, wants_graphics);
			if (wants_graphics) {
				gd->update_shape(u1block, current->getMembers(), 1);
			}
			td->update_shape(u1block, current->getMembers(), 1);

			//get the next block in line
			u1stream >> u1block;
			next1 = zero->createShape(u1block, heavy_flag, wants_graphics);
			if (wants_graphics) {
				gd->update_next(u1block, next1->getMembers(), 1);
			}
			td->update_next(u1block, 1);  

			// Create a shape for user2
			current2 = zero->createShape(u2block, heavy_flag, wants_graphics);
			if (wants_graphics) {
				gd->update_shape(u2block, current2->getMembers(), 2);
			}
			td->update_shape(u2block, current2->getMembers(), 2);

			//get the next block for user2
			u2stream >> u2block;
			next2 = zero->createShape(u2block, heavy_flag, wants_graphics);
			if (wants_graphics) {
				gd->update_next(u2block, next2->getMembers(), 2);
			}
			td->update_next(u2block, 2);

			//now print the textdisplay
			g1.print();
			
		} else if (s[0] == 's') {
			string file = "";
			cin >> file;
		} else if (s == "I" || s == "J" || s == "L" || s == "O" || s == "S" || s == "Z" || s == "T") { //Commands for testing with different block types
			Shape * newShape = zero->createShape(s, heavy_flag, wants_graphics);
			if (turn %2 == 0) {
				td->clear(current->getMembers(), 1);
				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
				}
				current = newShape;
				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();
			} else {
				td->clear(current2->getMembers(), 2);
				if (wants_graphics) {
					gd->clear(current2->getMembers(), 2);
				}
				current2 = newShape;
				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g1.print();
			}
		}
		steps = 1;
		numSteps = "";
	}
}

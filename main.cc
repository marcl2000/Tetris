#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "graphicsdisplay.h"
#include "grid.h"
#include "textdisplay.h"
#include "level.h"
#include "levelzero.h"
#include "leveltwo.h"
#include "levelone.h"
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
	int current1_level = 0;
	int current2_level = 0;

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
			current1_level = level;
			current2_level = level;
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

	//	td->update_level(current1_level, 1);
	//	td->update_level(current2_level, 2);

	GraphicsDisplay *gd = nullptr;

	//if the user wants graphics, then turn the display on
	if (wants_graphics) {
		gd = new GraphicsDisplay();
		g1.set_gd(gd);
		g2.set_gd(gd);
		gd->update_level(current1_level, 1);
		gd->update_level(current2_level, 2);
	}

	// Create filestreams for the blocks of each user
	ifstream u1stream {user1file};
	ifstream u2stream {user2file};
	string u1block;
	string u2block;

	Level *u1level = nullptr;
	Level *u2level = nullptr;
	Shape *current = nullptr;
	Shape *current2 = nullptr;
	Shape *next1 = nullptr;
	Shape *next2 = nullptr;

	if (current1_level == 1) {
		u1level = new LevelOne();
	} else if (current1_level == 2) {
		u1level = new LevelTwo();
	} else {
		current1_level = 0;
		u1stream >> u1block;

		//create a shape (this really needs to be Level *)
		u1level = new LevelZero();
		current = u1level->createShape(u1block, heavy_flag, wants_graphics);

		if (wants_graphics) {
			gd->update_shape(u1block, current->getMembers(), 1);
		}
		td->update_shape(u1block, current->getMembers(), 1);

		//get the next block in line
		u1stream >> u1block;
		next1 = u1level->createShape(u1block, heavy_flag, wants_graphics);
		if (wants_graphics) {
			gd->update_next(u1block, next1->getMembers(), 1);
		}
		td->update_next(u1block, 1);  

		//now print the textdisplay
		g1.print();


	}

	cout << "USER 2 LEVEL IS " << current2_level << endl;
	if (current2_level == 1) {
		u2level = new LevelOne();
	} else if (current2_level == 2) {
		u2level = new LevelTwo();
	} else {
		cout << "before seg fault"; 
		current2_level = 0;
		u2stream >> u2block;
		
		u2level = new LevelZero();
		current2 = u2level->createShape(u2block, heavy_flag, wants_graphics);
		if (wants_graphics) {
			gd->update_shape(u2block, current2->getMembers(), 2);
		}
		td->update_shape(u2block, current2->getMembers(), 2);

		//get the next block for user2
		u2stream >> u2block;
		next2 = u2level->createShape(u2block, heavy_flag, wants_graphics);
		if (wants_graphics) {
			gd->update_next(u2block, next2->getMembers(), 2);
		}
		td->update_next(u2block, 2);
		//now print the textdisplay
		g2.print();
	}



	if (!current1_level == 0) {
		current = u1level->createShape("", heavy_flag, wants_graphics);
		td->update_shape(current->getName(), current->getMembers(), 1);

		next1 = u1level->createShape("", heavy_flag, wants_graphics);
		td->update_next(next1->getName(), 1);

		if (wants_graphics) {
			gd->update_shape(current->getName(), current->getMembers(), 1);
			gd->update_next(next1->getName(), next1->getMembers(), 1);
		}

		g1.print();
	}

	if (!current2_level == 0) {
		current2 = u2level->createShape("", heavy_flag, wants_graphics);
		td->update_shape(current2->getName(), current2->getMembers(), 2);

		next2 = u2level->createShape("", heavy_flag, wants_graphics);
		td->update_next(next2->getName(), 2);

		if (wants_graphics) {
			gd->update_shape(current2->getName(), current2->getMembers(), 2);
			gd->update_next(next2->getName(), next2->getMembers(), 2);
		}

		g1.print();
	}

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
					gd->update_shape(current->getName(), current->getMembers(),1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);

				if (current1_level == 0) {
					u1stream >> u1block;
					if (u1stream.eof()) {
						// Clear the filestream and start reading from the beginning of the file
						u1stream.clear( );
						u1stream.seekg( 0, std::ios::beg);
						u1stream >> u1block;
					}
						// Now display the next block
						next1 = u1level->createShape(u1block, heavy_flag, wants_graphics);
				} else {
					next1 = u1level->createShape("", heavy_flag, wants_graphics);


				}
				if (wants_graphics) {
					gd->clear_next(1);
				}

				// Call fits function to see if the piece fits, if it doesn't the game is over
				if (!g1.piece_fits(next1->getMembers())) {
					cout << "The winner is Player 2!" << endl;
					u1stream.close();
					u2stream.close();
					delete current;
					delete current2;
					delete next1;
					delete next2;
					delete u1level;
					delete u2level;
					return 0;	
				}
				if (wants_graphics) {
					gd->update_next(next1->getName(), next1->getMembers(),1);
				}
				td->update_next(next1->getName(), 1);
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

				// Now calculate the score
				current2 = next2;

				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(),2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);


				if (current2_level == 0) {
					// Repeat the above process but for user2
					current2 = next2;
					if (wants_graphics) {
						gd->update_shape(current2->getName(), next2->getMembers(),2);
					}
					td->update_shape(current2->getName(), current2->getMembers(), 2);
					u2stream >> u2block;
					if (u2stream.eof()) {
						u2stream.clear( );
						u2stream.seekg( 0, std::ios::beg);
						u2stream >> u2block;
					}
					next2 = u2level->createShape(u2block, heavy_flag, wants_graphics);

				} else {
					next2 = u2level->createShape("", heavy_flag, wants_graphics);
				}
				if (wants_graphics) {
					gd->clear_next(2);
				}

				//call the function to check if the game is over (does the next piece fit on the grid)
				if (!g2.piece_fits(next2->getMembers())) {
					cout << "The winner is Player 1!" << endl;
					u1stream.close();
					u2stream.close();
					delete current;
					delete current2;
					delete next1;
					delete next2;
					delete u1level;
					delete u2level;
					return 0;
				}
				if (wants_graphics) {
					gd->update_next(next2->getName(), next2->getMembers(),2);
				}
				td->update_next(next2->getName(), 2);
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

			if (current1_level == 0) {
				// Clear the filestream and start reading from the beginning of the file
				u1stream.clear( );
				u1stream.seekg( 0, std::ios::beg);
				u1stream >> u1block;

				//create a level shape for user 1 
				current = u1level->createShape(u1block, heavy_flag, wants_graphics);

				//get the next block in line
				u1stream >> u1block;
				next1 = u1level->createShape(u1block, heavy_flag, wants_graphics);

			} else {
				current = u1level->createShape("", heavy_flag, wants_graphics);
				next1 = u1level->createShape("", heavy_flag, wants_graphics);
			}

			if (current2_level == 0) {

				u2stream.clear( );
				u2stream.seekg( 0, std::ios::beg);
				u2stream >> u2block;

				// Create a shape for user2
				current2 = u2level->createShape(u2block, heavy_flag, wants_graphics);

				//get the next block for user2
				u2stream >> u2block;
				next2 = u2level->createShape(u2block, heavy_flag, wants_graphics);
			} else {
				current2 = u2level->createShape("", heavy_flag, wants_graphics);
				next2 = u2level->createShape("", heavy_flag, wants_graphics);
			} 

			if (wants_graphics) {
				gd->update_shape(current->getName(), current->getMembers(), 1);
				gd->update_next(next1->getName(), next1->getMembers(), 1);
				gd->update_shape(current2->getName(), current2->getMembers(), 2);
				gd->update_next(next2->getName(), next2->getMembers(), 2);
			}

			//Update the text display
			td->update_shape(current->getName(), current->getMembers(), 1);
			td->update_next(next1->getName(), 1);  
			td->update_shape(current2->getName(), current2->getMembers(), 2);
			td->update_next(next2->getName(), 2);

			//now print the textdisplay
			g1.print();

		} else if (s[0] == 's') {
			string file = "";
			cin >> file;
		} else if (s == "I" || s == "J" || s == "L" || s == "O" || s == "S" || s == "Z" || s == "T") { //Commands for testing with different block types
			if (turn %2 == 0) {
				Shape * newShape = u1level->createShape(s, heavy_flag, wants_graphics);
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
				Shape * newShape = u2level->createShape(s, heavy_flag, wants_graphics);
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

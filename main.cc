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
			cout << "Running only in text mode" << endl;
			wants_graphics = false;

		} else if (cmd.substr(0, 3) == "-se") {
			++i;
			int seed = stoi(argv[i]); 
			cout << "Setting the random number's generator seed to " << seed << endl;
		} else if (cmd.substr(0, 3) == "-st") {
			++i;
			int level = stoi(argv[i]);
			cout << "Starting at level  " << level << endl;
			current_level = level;
		} else if (cmd == "-scriptfile1") {
			++i;
			string newFile = argv[i];
			user1file = newFile;
			cout << "Replacing scriptfile1 with " << argv[i] << endl;
		} else if (cmd == "-scriptfile2") {
			++i;
			string newFile = argv[i];
			user2file = newFile;
			cout << "Replacing scriptfile2 with " << argv[i] << endl;
		}
	}

	//make the textdisplay
	TextDisplay *td = new TextDisplay();
	td->init();

	//set up the two grids regardless
	Grid g1;
	g1.init("g1");
	Grid g2;
	g2.init("g2");

	//set the td
	g1.set_td(td);
	g2.set_td(td);

	//if the user wants graphics, then turn the display on
	GraphicsDisplay *gd = new GraphicsDisplay();
	g1.set_gd(gd);
	g2.set_gd(gd);

	// Create filestreams for the blocks of each user
	ifstream u1stream {user1file};
	ifstream u2stream {user2file};
	string u1block;
	string u2block;

	u1stream >> u1block;
	cout << "user1's block is " << u1block << endl;

	//create a shape (this really needs to be Level *)
	LevelZero *zero = new LevelZero();
	Shape *current = zero->createShape(u1block, heavy_flag, wants_graphics);

	gd->update_shape(u1block, current->getMembers(), 1);
	td->update_shape(u1block, current->getMembers(), 1);

	//get the next block in line
	u1stream >> u1block;
	cout << "U1 next IS " << u1block << endl;
	Shape *next1 = zero->createShape(u1block, heavy_flag, wants_graphics);
	gd->update_next(u1block, next1->getMembers(), 1);
	td->update_next(u1block, 1);  //

	// Create a shape for user2
	u2stream >> u2block;
	cout << "U2 Blocks is " << u2block << endl;
	Shape *current2 = zero->createShape(u2block, heavy_flag, wants_graphics);
	gd->update_shape(u2block, current2->getMembers(), 2);
	td->update_shape(u2block, current2->getMembers(), 2);

	//get the next block for user2
	u2stream >> u2block;
	cout << "U2 next IS " << u2block << endl;
	Shape * next2 = zero->createShape(u2block, heavy_flag, wants_graphics);
	gd->update_next(u2block, next2->getMembers(), 2);
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
				//gd->clear_current(1);
				gd->clear(current->getMembers(), 1);
				td->clear(current->getMembers(), 1);
				current->move_left(steps);
				gd->update_shape(current->getName(), current->getMembers(), 1);
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();
			} else {
				cout << "type is " << current2->getName() << endl;
				//gd->clear_current(2);
				gd->clear(current2->getMembers(), 2);
				td->clear(current2->getMembers(), 2);
				current2->move_left(steps);
				gd->update_shape(current2->getName(), current2->getMembers(), 2);
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g2.print();
			}
		} else if (s.substr(0, 2) == "ri") {
			if (turn%2 == 0) {
				//gd->clear_current(1);
				gd->clear(current->getMembers(), 1);
				td->clear(current->getMembers(), 1);
				current->move_right(steps);
				gd->update_shape(current->getName(), current->getMembers(), 1);
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();
			} else {
				cout << "type is " << current2->getName() << endl;
				//gd->clear_current(2);
				gd->clear(current2->getMembers(), 2);
				td->clear(current2->getMembers(), 2);
				current2->move_right(steps);
				gd->update_shape(current2->getName(), current2->getMembers(), 2);
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g2.print();
			}
		} else if (s.substr(0, 2) == "do") {
			cout << "Moving down by " << steps << " steps" << endl;
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
						gd->clear(current->getMembers(), 1);
						td->clear(current->getMembers(), 1);

						current->move_down();
						gd->update_shape(current->getName(), current->getMembers(), 1);
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
						gd->clear(current2->getMembers(), 2);
						td->clear(current2->getMembers(), 2);
						current2->move_down();
						gd->update_shape(current2->getName(), current2->getMembers(), 2);
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
							gd->clear(current->getMembers(), 1);
							td->clear(current->getMembers(), 1);
						}
						current->move_down();
					}
				}
				gd->update_shape(current->getName(), current->getMembers(), 1);
				td->update_shape(current->getName(), current->getMembers(), 1);

				//after dropping, add this shape to the list of shapes and set the corresponding grid cells to filled
				g1.add_shape(current);

				for(int i=0;i<4;i++){
					int n = current->getMembers()[i].y/20 - 3;
					int m = current->getMembers()[i].x/20;
					(g1.get_lines()[n].get_cells()[m]).set_filled(true);
				}

				gd->clear_current(1);

				//call lines_cleared to determine if lines are cleared and shifting needs to occur************************
				//call the function to check if the game is over (does the next piece fit on the grid)???????????????
				int clearCount = g1.lines_cleared();
				 cout << "Clear count is " << clearCount << endl;
				// calculatet the score later


				// First set the next block to the current shape
				current = next1;
				gd->update_shape(u1block, current->getMembers(),1);
				td->update_shape(u1block, current->getMembers(), 1);
				u1stream >> u1block;
				if (u1stream.eof()) {
					// Clear the filestream and start reading from the beginning of the file
					u1stream.clear( );
					u1stream.seekg( 0, std::ios::beg);
					u1stream >> u1block;
				}
				gd->clear_next(1);
				cout << "user1's block is " << u1block << endl;
				// Now display the next block
				next1 = zero->createShape(u1block, heavy_flag, wants_graphics);
				gd->update_next(u1block, next1->getMembers(),1);
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
							gd->clear(current2->getMembers(), 2);
							td->clear(current2->getMembers(), 2);
						}
						current2->move_down();
					}
				}
				gd->update_shape(current2->getName(), current2->getMembers(), 2);
				td->update_shape(current2->getName(), current2->getMembers(), 2);

				//after dropping, add this shape to the list of shapes and set the corresponding grid cells to filled
				g2.add_shape(current2);

				for(int i=0;i<4;i++){
					int n = current2->getMembers()[i].y/20 - 3;
					int m = current2->getMembers()[i].x/20;
					(g2.get_lines()[n].get_cells()[m]).set_filled(true);
				}


				//call lines_cleared to determine if lines are cleared and shifting needs to occur*******************
				//call the function to check if the game is over (does the next piece fit on the grid)???????????????
				int clearCount = g2.lines_cleared();
				cout << "Clear count is " << clearCount << endl;
		
				// Now calaculate teh score

				gd->clear_current(2);
				// Repeat the above process but for user2
				cout << "User 2's old block is " << u2block << endl;
				current2 = next2;
				gd->update_shape(u2block, next2->getMembers(),2);
				td->update_shape(u2block, current2->getMembers(), 2);
				u2stream >> u2block;
				if (u2stream.eof()) {
					u2stream.clear( );
					u2stream.seekg( 0, std::ios::beg);
					u2stream >> u2block;
				}
				gd->clear_next(2);
				cout << "user2's block is " << u2block << endl;
				next2 = zero->createShape(u2block, heavy_flag, wants_graphics);
				gd->update_next(u2block, next2->getMembers(),2);
				td->update_next(u2block, 2);
				g2.print();
			}
			++turn;
		} else if (s.substr(0, 2) == "co") {
			cout << "Rotating counter clockwise by " << steps << " steps" << endl;
		} else if (s.substr(0, 2) == "cl") {                     
			cout << "Rotating clockwise by " << steps << " steps" << endl;
			for(int i=0;i<steps;i++){
				if(turn % 2 == 0){   //first player's block
					gd->clear(current->getMembers(), 1);
					td->clear(current->getMembers(), 1);
					current->clockwise();
					gd->update_shape(current->getName(), current->getMembers(), 1);
					td->update_shape(current->getName(), current->getMembers(), 1);
					g1.print();
				}

				else{  //second player's block
					gd->clear(current2->getMembers(), 2);
					td->clear(current2->getMembers(), 2);
					current2->clockwise();
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
					td->update_shape(current2->getName(), current2->getMembers(), 2);
					g1.print();
				}
			}

		} else if (s.substr(0, 2) == "ra") {
			cout << "Calling random" << endl;
		} else if (s[0] == 'n') {
			string file = "";
			cin >> file;
			cout << "Calling nonrandom with " << file << endl;
		} else if (s.substr(0, 2) == "re") {
			cout << "Restarting" << endl;
			//delete the current grids!!!!! and reinitialize them

		} else if (s[0] == 's') {
			string file = "";
			cin >> file;
			cout << "Sequence of blocks is in " << file << endl;
		} else if (s == "I") { //Commands for testing with different block types
			cout << "Making " << s << " block" << endl;
		} else if (s == "J") {
			cout << "Making " << s << " block" << endl;
		} else if (s == "L") {
			cout << "Making " << s << " block" << endl;
		} else if (s == "O") {
			cout << "Making " << s << " block" << endl;
		} else if (s == "S") {
			cout << "Making " << s << " block" << endl;
		} else if (s == "Z") {
			cout << "Making " << s << " block" << endl;
		} else if (s == "T") {
			cout << "Making " << s << " block" << endl;
		}

		steps = 1;
		numSteps = "";
	}
}

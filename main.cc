#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "graphicsdisplay.h"
#include "grid.h"
#include "textdisplay.h"
#include "level.h"
#include "levelzero.h"    //this should really not be included but its not working without ?????

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

	//print the textdisplay
	gd->update_shape(u1block, current->getMembers(), 1);

	//get the next block in line
	u1stream >> u1block;
	cout << "U1 next IS " << u1block << endl;
	Shape *next1 = zero->createShape(u1block, heavy_flag, wants_graphics);
   	gd->update_next(u1block, next1->getMembers(), 1);

	// Create a shape for user2
	u2stream >> u2block;
	cout << "U2 Blocks is " << u2block << endl;
	Shape *current2 = zero->createShape(u2block, heavy_flag, wants_graphics);
	gd->update_shape(u2block, current2->getMembers(), 2);                         
	
	//get the next block for user2
	u2stream >> u2block;
        cout << "U2 next IS " << u2block << endl;
        Shape * next2 = zero->createShape(u2block, heavy_flag, wants_graphics);
        gd->update_next(u2block, next2->getMembers(), 2);


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
			cout << "Moving left by " << steps << " steps" << endl;
		} else if (s.substr(0, 2) == "ri") {
			cout << "Moving right by " << steps << " steps" << endl;
		} else if (s.substr(0, 2) == "do") {
			cout << "Moving down by " << steps << " steps" << endl;
		} else if (s.substr(0, 2) == "dr") {
			cout << "Dropping  " << steps << " steps" << endl;
			//To differentiate between users, user1 will play when the turn count is
			//even and user2 will play when the turn count is odd
			if (turn % 2 == 0) {
				gd->clear_current(1);
				// First set the next block to the current shape
				current = next1;
				gd->update_shape(u1block, current->getMembers(),1);
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
			} else {
				gd->clear_current(2);
				// Repeat the above process but for user2
				cout << "User 2's old block is " << u2block << endl;
				current2 = next2;
				gd->update_shape(u2block, next2->getMembers(),2);
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
			}
			++turn;
		} else if (s.substr(0, 2) == "co") {
			cout << "Rotating counter clockwise by " << steps << " steps" << endl;
		} else if (s.substr(0, 2) == "cl") {                                                       //HOW WILL WE EVER ROTATE PLAYER TWO'S SHAPE???
			cout << "Rotating clockwise by " << steps << " steps" << endl;
			for(int i=0;i<steps;i++){
			//	gd->delete_shape(current->getMembers(), 1);
			//	current->clockwise();
			//	gd->update_next(u1block, current->getMembers(), 1);
			//** Claudia, above is your old code. After fixing the seg fault, your old code doesn't work anymore
			//so I had to call differently as shown below. I had to create a getName() method because other wise
			// block1's type is set to next's type, and we need current's type, so i can pass in block1, i have
			// to pass in current's type. Sorry i
				gd->delete_shape(current->getMembers(), 1);
				current->clockwise();
				gd->update_shape(current->getName(), current->getMembers(), 1);
			}

		} else if (s.substr(0, 2) == "ra") {
			cout << "Calling random" << endl;
		} else if (s[0] == 'n') {
			string file = "";
			cin >> file;
			cout << "Calling nonrandom with " << file << endl;
		} else if (s.substr(0, 2) == "re") {
			cout << "Restarting" << endl;
			//delete the current grids and reinitialize them

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

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
#include "levelthree.h"
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

	bool bonus_heavy1 = false;            //turning this on requires the user to clear a certain number of lines
	bool bonus_heavy2 = false;
	
	int current1_level = 0;
	int current2_level = 0;

	int score1 = 0;
	int score2 = 0;

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
	g1.set_td(td);

	Grid g2;
	g2.set_td(td);

	//update the scores and levels
	td->update_level(current1_level, 1);
	td->update_level(current2_level, 2);
	td->update_score(0, 1);
	td->update_score(0, 2);

	GraphicsDisplay *gd = nullptr;

	//if the user wants graphics, then turn the display on
	if (wants_graphics) {
		gd = new GraphicsDisplay();
		g1.set_gd(gd);
		g2.set_gd(gd);
		gd->update_level(current1_level, 1);
		gd->update_level(current2_level, 2);
		gd->update_score(0, 1);
		gd->update_score(0, 2);
	}
	g1.init("g1", wants_graphics);
	g2.init("g2", wants_graphics);


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
	} else if (current1_level == 3){
		u1level = new LevelThree();
	} else {
		current1_level = 0;
		u1stream >> u1block;

		//create a shape (this really needs to be Level *)
		u1level = new LevelZero();
		current = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);

		if (wants_graphics) {
			gd->update_shape(u1block, current->getMembers(), 1);
		}
		td->update_shape(u1block, current->getMembers(), 1);

		//get the next block in line
		u1stream >> u1block;
		next1 = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);
		if (wants_graphics) {
			gd->update_next(u1block, next1->getMembers(), 1);
		}
		td->update_next(u1block, 1);  


	}

	if (current2_level == 1) {
		u2level = new LevelOne();
	} else if (current2_level == 2) {
		u2level = new LevelTwo();
	} else if (current2_level == 3){
		u2level = new LevelThree();
	} else {
		current2_level = 0;
		u2stream >> u2block;

		u2level = new LevelZero();
		current2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);

		if (wants_graphics) {
			gd->update_shape(u2block, current2->getMembers(), 2);
		}
		td->update_shape(u2block, current2->getMembers(), 2);

		//get the next block for user2
		u2stream >> u2block;
		next2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);
		if (wants_graphics) {
			gd->update_next(u2block, next2->getMembers(), 2);
		}
		td->update_next(u2block, 2);
		//now print the textdisplay
		g2.print();
	}



	if (!current1_level == 0) {
		current = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);

		td->update_shape(current->getName(), current->getMembers(), 1);

		next1 = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);
		td->update_next(next1->getName(), 1);

		if (wants_graphics) {
			gd->update_shape(current->getName(), current->getMembers(), 1);
			gd->update_next(next1->getName(), next1->getMembers(), 1);
		}

		g1.print();
	}

	if (!current2_level == 0) {
		current2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);

		td->update_shape(current2->getName(), current2->getMembers(), 2);

		next2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);
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
			if (s[5] == 'd') {
				steps = steps * (-1);
			}

			if (turn%2==0) {
				current1_level += steps;

				// If user levels up on our highest level, then set the level to
				// the highest level we have implemented
				if (current1_level > 3) {
					current1_level = 3;
				}
				if (current1_level <  0) {
					current1_level = 0;
				}


				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
					gd->clear(next1->getMembers(), 1);
					gd->clear_next(1);

				}
				td->clear(current->getMembers(), 1);
				td->clear(next1->getMembers(),1);
				td->update_level(current1_level, 1);

				delete u1level;
				delete current;
				delete next1;

				if (current1_level == 1) {
					u1level = new LevelOne();
				} else if (current1_level == 2) {
					u1level = new LevelTwo();
				} else if (current1_level == 3){
					u1level = new LevelThree();
				} else {
					current1_level = 0;
					u1stream >> u1block;

					//create a shape (this really needs to be Level *)
					u1level = new LevelZero();
					current = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);

					if (wants_graphics) {
						gd->update_shape(u1block, current->getMembers(), 1);
					}
					td->update_shape(u1block, current->getMembers(), 1);

					//get the next block in line
					u1stream >> u1block;
					next1 = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);
					if (wants_graphics) {
						gd->update_next(u1block, next1->getMembers(), 1);
					}

					//now print the textdisplay
					g1.print();

				}

				if (!current1_level == 0) {
					current = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);

					td->update_shape(current->getName(), current->getMembers(), 1);

					next1 = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);
					td->update_next(next1->getName(), 1);

					if (wants_graphics) {
						gd->update_shape(current->getName(), current->getMembers(), 1);
						gd->update_next(next1->getName(), next1->getMembers(), 1);
					}

					g1.print();
				}

				td->update_level(current1_level, 1);
				if (wants_graphics) {
					gd->update_level(current1_level, 1);
				}



			} else {
				current2_level += steps;

				// If user levels up on our highest level, then set the level to
				// the highest level we have implemented
				if (current2_level > 3) {
					current2_level = 3;
				}

				if (current2_level < 0) {
					current2_level = 0;
				}

				if (wants_graphics) {
					gd->clear(current2->getMembers(),2);
					gd->clear(next2->getMembers(), 2);
					gd->clear_next(2);
				}
				td->clear(current2->getMembers(), 2);
				td->clear(next2->getMembers(),2);
				td->update_level(current2_level, 2);

				delete u2level;
				delete current2;
				delete next2;

				if (current2_level == 1) {
					u2level = new LevelOne();
				} else if (current2_level == 2) {
					u2level = new LevelTwo();
				} else if (current2_level == 3){
					u2level = new LevelThree();
				} else {
					current2_level = 0;
					u2stream >> u2block;

					u2level = new LevelZero();
					current2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);

					if (wants_graphics) {
						gd->update_shape(u2block, current2->getMembers(), 2);
					}
					td->update_shape(u2block, current2->getMembers(), 2);

					//get the next block for user2
					u2stream >> u2block;
					next2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);
					if (wants_graphics) {
						gd->update_next(u2block, next2->getMembers(), 2);
					}
					td->update_next(u2block, 2);
					//now print the textdisplay
					g2.print();
				}

				if (!current2_level == 0) {
					current2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);

					td->update_shape(current2->getName(), current2->getMembers(), 2);

					next2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);
					td->update_next(next2->getName(), 2);

					if (wants_graphics) {
						gd->update_shape(current2->getName(), current2->getMembers(), 2);
						gd->update_next(next2->getName(), next2->getMembers(), 2);
					}

					g2.print();
				}
				if (wants_graphics) {
					gd->update_level(current2_level, 2);
				}

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

				//IF BONUS HEAVY OR ON LEVEL THREE, CHECK IF THIS MOVE WOULD END THE GAME

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

				//SAME HERE
			}


		} else if (s.substr(0, 2) == "ri") {
			if (turn%2 == 0) {
				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
				}
				td->clear(current->getMembers(), 1);

				//if there is anything in the way, decrease steps
				int true_steps = 0;
				bool temp = true;

				while(steps*20+current->getMembers()[0].x > 10*20 || steps*20+current->getMembers()[1].x > 10*20 || 
						steps*20+current->getMembers()[2].x > 10*20 || steps*20+current->getMembers()[3].x > 10*20){
					--steps;
				}

				for(int i=0;i<steps;i++){
					for(int j=0;j<4;j++){
						int n = current->getMembers()[j].x/20 + i+1;
						int m = current->getMembers()[j].y/20 - 3;

						if((g1.get_lines()[m].get_cells()[n]).isFilled()){
							temp = false;
						}
					}
					if(temp){
						++true_steps;
					}
				}

				current->move_right(true_steps);
				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();

				//SAME HERE

			} else {
				if (wants_graphics) {
					gd->clear(current2->getMembers(), 2);
				}
				td->clear(current2->getMembers(), 2);

				int true_steps = 0;
				bool temp = true;

				while(steps*20+current2->getMembers()[0].x > 10*20 || steps*20+current2->getMembers()[1].x > 10*20 ||
						steps*20+current2->getMembers()[2].x > 10*20 || steps*20+current2->getMembers()[3].x > 10*20){
					--steps;
				}

				for(int i=0;i<steps;i++){
					for(int j=0;j<4;j++){
						int n = current2->getMembers()[j].x/20 + i+1;
						int m = current2->getMembers()[j].y/20 - 3;

						if((g2.get_lines()[m].get_cells()[n]).isFilled()){
							temp = false;
						}
					}
					if(temp){
						++true_steps;
					}
				}

				current2->move_right(true_steps);
				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g2.print();

				//SAME HERE
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
				vector<int> result = g1.lines_cleared();
				
				//with this information, calculate the score for player 1

				if(result.back() > 0){
					score1 += (current1_level + result.back())*(current1_level + result.back());
					result.pop_back();

					//now, do the pieces cleared this turn
					int size = result.size();
					for(int p=0;p<size;p++){
						int level = result.back()+1;
						level *= level;
						score1 += level;
						result.pop_back();
					}

					//update the displays
					if(wants_graphics){
						gd->update_score(score1, 1);
					}
					td->update_score(score1, 1);
				}

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
					next1 = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);
				} else {
					next1 = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);


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


				//**IF THE LINES CLEARED WAS TWO OR MORE, GIVE A BONUS OPTION

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

				 vector<int> result = g2.lines_cleared();

				 //with this information, calculate the score for player 2
				 if(result.back() > 0){
				 	score2 += (current2_level + result.back())*(current2_level + result.back());
				 	result.pop_back();
				 
				 	//now, do the pieces cleared this turn
				 	int size = result.size();
				 	for(int p=0;p<size;p++){
						int level = result.back()+1;
					 	level *= level;
					 	score2 += level;
					 	result.pop_back();
					}
				
					//update the displays
					if(wants_graphics){
						gd->update_score(score2, 2);
					}
					td->update_score(score2, 2);
				 }
				
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
					next2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);

				} else {
					next2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);
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

				//**IF THE LINES CLEARED WAS TWO OR MORE, GIVE A BONUS OPTION

			}
			++turn;
		} else if (s.substr(0, 2) == "co") {
			if(turn % 2 == 0){   //first player's block
				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
				}
				td->clear(current->getMembers(), 1);

				current->counterclockwise();
				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();

				//SAME HERE
				//ALSO CHECK IF ROTATING WOULD BE ON TOP OF ANOTHER PIECE, OTHERWISE MOVE IT BACK TO THE ORIGINAL POSITION
			}

			else{  //second player's block
				if (wants_graphics) {
					gd->clear(current2->getMembers(), 2);
				}
				td->clear(current2->getMembers(), 2);
				current2->counterclockwise();
				if (wants_graphics) {
					gd->update_shape(current2->getName(), current2->getMembers(), 2);
				}
				td->update_shape(current2->getName(), current2->getMembers(), 2);
				g1.print();

				//SAME HERE
				//ALSO CHECK IF ROTATING WOULD BE ON TOP OF ANOTHER PIECE, OTHERWISE MOVE IT BACK TO THE ORIGINAL POSITION
			}

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

					//SAME HERE
					//ALSO CHECK...
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

					//SAME HERE
					//ALSO CHECK...
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
				gd->update_level(current1_level, 1);
				gd->update_level(current2_level, 2);
			}

			g1.deleteShape();
			g2.deleteShape();

			//set all cells on the grid to false
			g1.clear_cells();
			g2.clear_cells();

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
				current = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);

				//get the next block in line
				u1stream >> u1block;
				next1 = u1level->createShape(u1block, bonus_heavy1, wants_graphics, current1_level);

			} else {
				current = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);

				next1 = u1level->createShape("", bonus_heavy1, wants_graphics, current1_level);
			}

			if (current2_level == 0) {

				u2stream.clear( );
				u2stream.seekg( 0, std::ios::beg);
				u2stream >> u2block;

				// Create a shape for user2
				current2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);

				//get the next block for user2
				u2stream >> u2block;
				next2 = u2level->createShape(u2block, bonus_heavy2, wants_graphics, current2_level);
			} else {
				current2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);

				next2 = u2level->createShape("", bonus_heavy2, wants_graphics, current2_level);
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
				Shape * newShape = u1level->createShape(s, bonus_heavy1, wants_graphics, current1_level);

				td->clear(current->getMembers(), 1);
				if (wants_graphics) {
					gd->clear(current->getMembers(), 1);
				}
				delete current;
				current = newShape;

				if (wants_graphics) {
					gd->update_shape(current->getName(), current->getMembers(), 1);
				}
				td->update_shape(current->getName(), current->getMembers(), 1);
				g1.print();
			} else {
				Shape * newShape = u2level->createShape(s, bonus_heavy2, wants_graphics, current2_level);
				td->clear(current2->getMembers(), 2);
				if (wants_graphics) {
					gd->clear(current2->getMembers(), 2);
				}
				delete current2;
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

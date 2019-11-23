#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){	
	// Variables for program setup
	string numSteps = "";
	int steps = 1;
	string user1file = "biquadris_sequence1.txt";
	string user2file = "biquadris_sequence2.txt";
  	int turn = 0;	

	// If any command lines were given, interpret and apply them
	for (int i = 0; i < argc; ++i) {
		string cmd = argv[i];
		if (cmd.substr(0,2) == "-t") {
			 cout << "Running only in text mode" << endl;
		} else if (cmd.substr(0, 3) == "-se") {
                        ++i;
			int seed = stoi(argv[i]); 
                        cout << "Setting the random number's generator seed to " << seed << endl;
                }else if (cmd.substr(0, 3) == "-st") {
                        ++i;
			int level = stoi(argv[i]);
                        cout << "Starting at level  " << level << endl;
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

	// Create filestreams for the blocks of each user
	ifstream u1stream {user1file};
        ifstream u2stream {user2file};
        string u1block;
        string u2block;
	
	u1stream >> u1block;
        cout << "user1's block is " << u1block << endl;
	
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
			++turn;
			if (turn % 2 == 0) {
                        	u1stream >> u1block;
				if (u1stream.eof()) {
					// Clear the filestream and start reading from the beginning of the file
					u1stream.clear( );
					u1stream.seekg( 0, std::ios::beg);
					u1stream >> u1block;
				}
                        	cout << "user1's block is " << u1block << endl;
               		 } else {
                        	u2stream >> u2block;
				if (u2stream.eof()) {
					u2stream.clear( );
                               		u2stream.seekg( 0, std::ios::beg);
                                        u2stream >> u1block;
                                }
                       		cout << "user2's block is " << u2block << endl;
                	 }
                } else if (s.substr(0, 2) == "co") {
                        cout << "Rotating counter clockwise by " << steps << " steps" << endl;
                } else if (s.substr(0, 2) == "cl") {
                        cout << "Rotating clockwise by " << steps << " steps" << endl;
                } else if (s.substr(0, 2) == "ra") {
                        cout << "Calling random" << endl;
                } else if (s[0] == 'n') {
                        string file = "";
                        cin >> file;
			cout << "Calling nonrandom with " << file << endl;
                } else if (s.substr(0, 2) == "re") {
                        cout << "Restarting" << endl;
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

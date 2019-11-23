#include <iostream>
#include <string>
using namespace std;

int main(){	
	string numSteps = "";
	int steps = 1;

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
                } else if (s.substr(0, 2) == "-t") { //Command-line interface commands
			cout << "Running only in text mode" << endl;
		} else if (s.substr(0, 3) == "-se") {
			int seed;
			cin >> seed;
			cout << "Setting the random number's generator seed to " << seed << endl;
		} else if (s.substr(0, 3) == "-st") {
                        int level;
                        cin >> level;
                        cout << "Starting at level  " << level << endl;
		} else if (s == "-scriptfile1") {
			string f;
			cin >> f;
			cout << "Replacing scriptfile1 with " << f << endl;
		} else if (s == "-scriptfile2") {
                        string f;
                        cin >> f;
                        cout << "Replacing scriptfile2 with " << f << endl;
                }
		steps = 1;
		numSteps = "";
	}
}

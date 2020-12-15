// LOL keymap logger created by maximos nolan
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <ctime>

using namespace std;
	struct positions {
		LPCSTR one = "";
		LPCSTR two = "";
		LPCSTR three = "";
		LPCSTR four = "";
	};
	positions driver;
	double log_count = 0;
	bool valid_choice = false;
	bool end_program = false; 
	unordered_map<char, int> log_map; 
	void intro() {
		cout << "This program will help create a heatmap of keys pressed in league!"
			<< " this program \n"
			<< "in particular will detect function key usage and keep track of other "
			<< "important stats\n";
		cout << "Created by: Maximos Nolan (Cliftonbeefy)\n";
		cout << "-------------------------------------------------------------------\n";
		cout << "Enter the role that you play: (top, jungle, mid, adc, support)  \n";
	}
	void update_key_log(int key) {
		switch (key) {
		case 'Q':
			log_map['Q']++;
			break;
		case 'W':
			log_map['W']++;
			break;
		case 'E':
			log_map['E']++;
			break;
		case 'R':
			log_map['R']++;
			break;
		case 'D':
			log_map['D']++;
			break;
		case 'F':
			log_map['F']++;
			break;
		}
	}
	void set_position() {
		
		string role = "";
		cin >> role;
		switch (role[0]) {
		case 't':
			driver.one = " jungle ";
			driver.two = " mid ";
			driver.three = " adc ";
			driver.four = " support ";
			valid_choice = true;
			break;
		case 'j':
			driver.one = " top ";
			driver.two = " mid ";
			driver.three = " adc ";
			driver.four = " support ";
			valid_choice = true;
			break;
		case 'm':
			driver.one = " top ";
			driver.two = " jungle ";
			driver.three = " adc ";
			driver.four = " support ";
			valid_choice = true;
			break;
		case 'a':
			driver.one = " top ";
			driver.two = " jungle ";
			driver.three = " mid ";
			driver.four = " support ";
			valid_choice = true;
			break;
		case 's':
			driver.one = " top ";
			driver.two = " jungle ";
			driver.three = " mid ";
			driver.four = " adc ";
			valid_choice = true;
			break;
		default: cout << "enter valid choice! (top, jungle, mid, adc, support) \n";
		}
	}


	void writeToLog(LPCSTR text) {
		ofstream logfile;
		logfile.open("keylogs.txt", fstream::app);
		logfile << text;
		logfile.close();
	}

	bool KeyListed(int key) {
		switch (key) {
		case VK_SPACE:
			cout << " ";
			writeToLog(" ");
			log_count++;
			break;
		case VK_RETURN:
			cout << "\n";
			writeToLog("\n");
			break;
		case VK_SHIFT:
			cout << " *Shift* ";
			writeToLog(" *Shift* ");
			break;
		case VK_BACK:
			cout << "\b";
			writeToLog("\b");
		case VK_RBUTTON:
			cout << " *rclick* ";
			writeToLog(" *rclick* ");
			log_count++;
			break;
		case VK_LBUTTON:
			cout << " *lclick* ";
			writeToLog(" *lclick* ");
			log_count++;
			break;
		case VK_ESCAPE:
			cout << " *escape* ";
			writeToLog(" *escape* ");
			break;
		case VK_F1:
			cout << driver.one;
			writeToLog(driver.one);
			log_map['1']++;
			log_count++;
			break;
		case VK_F2:
			cout << driver.two;
			writeToLog(driver.two);
			log_map['2']++;
			log_count++;
			break;
		case VK_F3:
			cout << driver.three;
			writeToLog(driver.three);
			log_map['3']++;
			log_count++;
			break;
		case VK_F4:
			cout << driver.four;
			writeToLog(driver.four);
			log_map['4']++;
			log_count++;
			break;
		case VK_F10:
			end_program = true;
			cout << end_program;
			break;
		default: return false;
		}
		
	}
	time_t start = time(0);
	void calculate_log() {
		double min_since_start = difftime(time(0), start);
		min_since_start /= 60.0;
		cout << "statistics: \n";
		cout << "times you panned to your" << driver.one << ": " << log_map['1'] << "\n";
		cout << "times you panned to your" << driver.two << ": " << log_map['2'] << "\n";
		cout << "times you panned to your" << driver.three << ": " << log_map['3'] << "\n";
		cout << "times you panned to your" << driver.four << ": " << log_map['4'] << "\n";

		cout << "\n";
		cout << "times key pressed (calcualted compared to other keys): \n";
		cout << "times you pressed q " << log_map['Q'] << " " << 100 * log_map['Q'] / log_count << "%\n";
		cout << "times you pressed w " << log_map['W'] << " " << 100 * log_map['W'] / log_count << "%\n";
		cout << "times you pressed e " << log_map['E'] << " " << 100 * log_map['E'] / log_count << "%\n";
		cout << "times you pressed r " << log_map['R'] << " " << 100 * log_map['R'] / log_count << "%\n";
		cout << "times you pressed d " << log_map['D'] << " " << 100 * log_map['D'] / log_count << "%\n";
		cout << "times you pressed f " << log_map['F'] << " " << 100 * log_map['F'] / log_count << "%\n";
		cout << "\n";

		cout << "function key analysis: \n";
		double sum_of_fn = log_map['1'] + log_map['2'] + log_map['3'] + log_map['4'];
		cout << "You used function keys at a rate of " << sum_of_fn / min_since_start << " per minute\n";
		(sum_of_fn / min_since_start <= 6) ? cout << "poor function key usage\n": cout << "good function key usage\n";
		cout << "APM " << log_count / min_since_start << "\n";
		cout << "Thank you for using the program!";
		cout << "\n";
}
	bool mask_input = false;
	void mask_output() {
		string input;
		bool stop = false;
		cout << "Do you want to mask your logged keys from the console (yes or no) ? \n";
		while (!stop) {
			cin >> input;
			tolower(input[0]);
			switch (input[0]) {
			case  'y':
				mask_input = true;
				cout << "masking key loggs \n";
				stop = true;
				break;
			case 'n':
				cout << "not masking key loggs \n";
				stop = true;
				break;
			default: cout << "enter yes or no\n";
			}
		}
}
int main() {
	intro();
	while (!valid_choice) set_position();
	mask_output();
	char key;
	do {
		Sleep(10);
		for (key = 8; key <= 190 && !end_program; key++) {
			if (GetAsyncKeyState(key) == -32767) {
				if (KeyListed(key) == FALSE) {
					log_count++;
					update_key_log(key);
					if(!mask_input) cout << key << " "; 
					ofstream logfile; 
					logfile.open("keylogs.txt", fstream::app);
					logfile << key << " "; 
					logfile.close();
				}
			}
		}
	}while (!end_program);
	calculate_log();
	system("pause");
}

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

#define ADD_LINE 1
#define DELETE_LINE 2
#define SEARCH_LINE 3
#define REVERSE_LINES 4
#define REMOVE_DUPLICATES 5
#define COUNT_LINES 6
#define MERGE_FILES 7
#define QUIT 8

void display_menu();
int get_menu_choice();
string get_input(string);
int get_input();

void add_line(string, string, int);
int delete_line(string, string, int);
int search_line(string, string, int);
int reverse_lines(string);
int remove_duplicates(string, string);
int merge_files(string, string, string);
int count_lines(string);

void display_output(int, string, string, int, int);  // used for add/delete/search
void display_output(int, string, int);               // used for reverse/remove/count
void display_output(string, string, string, int);  // used for merge


int main()
{
	do {
		//Variables
		string text1;
		string text2;
		string text3;
		int menu_choice;
		int num_of_lines;
		int times;
		int result;

		display_menu();
		menu_choice = get_menu_choice();
		if (menu_choice == 1) {
			int result = 0;
			text1 = get_input("file name");
			text2 = get_input("the word you want to add to the file");
			times = get_input();
			add_line(text1, text2, times);
			display_output(ADD_LINE, text1, text2, times, result);
		}
		else if (menu_choice == 2) {
			text1 = get_input("file name");
			text3 = get_input("line you wish to delete from the file");
			times = get_input();
			result = delete_line(text1, text3, times);
			display_output(DELETE_LINE, text1, text3, times, result);
		}
		else if (menu_choice == 3) {
			text1 = get_input("file name");
			text2 = get_input("the word you want to search for in the file");
			times = get_input();
			result = search_line(text1, text2, times);
			display_output(SEARCH_LINE, text1, text2, times, result);
		}
		else if (menu_choice == 4) {
			text1 = get_input("file name");
			result = reverse_lines(text1);
			display_output(REVERSE_LINES, text1, result);
		}
		else if (menu_choice == 5) {
			text1 = get_input("file name");
			text2 = get_input("word to remove duplicates (test)");
			result = remove_duplicates(text1, text2);
			display_output(REMOVE_DUPLICATES, text1, result);
		}
		else if (menu_choice == 6) {
			text1 = get_input("file name");
			num_of_lines = count_lines(text1);
			display_output(COUNT_LINES, text1, num_of_lines);
		}
		else {
			system("PAUSE");
			return 0;
		}
	} 
	while (true);
}

void display_menu()
{
	string menu = "0";
	cout << "---------- MENU ----------\n\n";
	cout << "1. Add line\n";
	cout << "2. Delete line\n";
	cout << "3. Search line\n";
	cout << "4. Reverse lines\n";
	cout << "5. Remove duplicates\n";
	cout << "6. Count lines\n";
	cout << "7. Merge files\n";
	cout << "8. Quit\n\n";
	cout << "--------------------------\n\n";
}

int get_menu_choice()
{
	int menu_choice;

	do
	{
		cout << "Enter your choice (1-8): ";
		cin >> menu_choice;
	}

	while (menu_choice < 1 || menu_choice > 8);

	return menu_choice;

}

string get_input(string text)
{
	string input;
	cout << "Enter the " << text << ": ";
	cin >> input;
	return input;
}

int get_input()
{
	int input;
	cout << "Enter the number of occurences: ";
	cin >> input;
	return input;
}

int count_lines(string filename)
{
	ifstream inputfile;
	string line;
	int num_of_lines = 0;
	inputfile.open(filename.c_str());

	if (!inputfile)
		return -1;

	while (inputfile >> line)
		num_of_lines++;

	inputfile.close();

	return num_of_lines;
}

void display_output(int op, string filename, string file_line, int num_of_occurs, int result)  // used for add/delete/search
{

	if (result == -1)
		cout << "\nERROR: the file " << filename << " could not be found\n\n";


	else
		switch (op)
		{

		case ADD_LINE:
			cout << "\nThe line " << file_line << " has been added to the file "
				<< filename << " " << num_of_occurs << " time(s)\n\n";
			break;

		case DELETE_LINE:


			if (result == 0)
				cout << "\nThe line " << file_line << " does not occur in the file "
				<< filename << endl << endl;

			else if (result < num_of_occurs)
				cout << "\nThe line " << file_line << " could only be removed from the file "
				<< filename << " " << result << " time(s)\n\n";

			else // result == num_of_occurs
				cout << "\nThe line " << file_line << " has been removed from the file "
				<< filename << " " << result << " time(s)\n\n";
			break;


		default: // case = SEARCH_LINE


			if (result == 0)
				cout << "\nThe line " << file_line << " does not occur in the file "
				<< filename << endl << endl;

			else if (result < num_of_occurs)
				cout << "\nThe line " << file_line << " could only be found in the file "
				<< filename << " " << result << " time(s)\n\n";

			else
				cout << "\nThe line " << file_line << " has been found in the file "
				<< filename << " " << result << " time(s)\n\n";

		}

}

void display_output(int op, string filename, int result) // used for reverse/remove/count
{

	if (result == -1)
		cout << "\nERROR: the file " << filename << " could not be found\n\n";

	else
		switch (op)
		{
		case REVERSE_LINES:
			cout << "\nAll of the lines in the file " << filename << " have been reversed\n\n";
			break;

		case REMOVE_DUPLICATES:
			cout << endl << result << " duplicates have been removed from the file " << filename << endl << endl;
			break;

		default:
			cout << "\nThere are " << result << " lines in the file " << filename << endl << endl;

		}

}

void display_output(string filename1, string filename2, string filename3, int result) //used for merge
{
	switch (result)
	{
	case -3:
		cout << "\nERROR: both files " << filename1 << " and " << filename2 << " could not be found\n\n";
		break;

	case -2:
		cout << "\nERROR: the file " << filename2 << " could not be found\n\n";
		break;

	case -1:
		cout << "\nERROR: the file " << filename1 << " could not be found\n\n";
		break;

	default:
		cout << "\nThe files " << filename1 << " and " << filename2 << " were merged into the file " << filename3
			<< ", which contains a total of " << result << " lines\n\n";

	}
}

void add_line(string filename, string file_line, int num_of_occurs) {
	ifstream inputFile;
	inputFile.open(filename);
	ofstream outputFile;
	outputFile.open("tmp.txt");

	string word;

	for (int i = 1; i <= num_of_occurs; i++) {
		outputFile << file_line << endl;
	}

	while (inputFile >> word)
	{
		outputFile << word << endl;
	}

	outputFile.close();
	inputFile.close();

	remove(filename.c_str());

	rename("tmp.txt", filename.c_str());
}

int delete_line(string filename, string file_line, int num_of_occurs) {
	int result = 0;
	int count = 0;
	ifstream inputFile;
	inputFile.open(filename);
	ofstream outputFile;
	outputFile.open("tmp.txt");

	string word;

	while (inputFile >> word) {
		if (file_line != word || count >= num_of_occurs) {
			outputFile << word << endl;
		}
		else if (file_line == word) {
			result++;
			count++;
		}
	}

	outputFile.close();
	inputFile.close();

	remove(filename.c_str());

	rename("tmp.txt", filename.c_str());

	return result;
}

int search_line(string filename, string file_line, int num_of_occurs) {
	int result = 0;
	ifstream inputFile;
	inputFile.open(filename);

	string word;

	while (inputFile >> word) {
		if (word == file_line && result < num_of_occurs) {
			result++;
		}
	}
	return result;
}

int reverse_lines(string filename) {
	int result = 0;
	int count = count_lines(filename);
	ifstream inputFile;
	inputFile.open(filename);
	ofstream outputFile;
	outputFile.open("tmp.txt");

	string word;


	outputFile.close();
	inputFile.close();

	remove(filename.c_str());
	rename("tmp.txt", filename.c_str());

	return result;
}

int remove_duplicates(string filename, string file_line) {
	ifstream inputFile;
	inputFile.open(filename.c_str());
	ofstream outputFile;
	outputFile.open("tmp.txt");

	int count = 0;
	string word;

	while (inputFile >> word) {
		file_line = word;
		if (file_line == word) {
			count++;
		}
	}

	inputFile.close();
	outputFile.close();

	int num_of_occurs = (count - 1);
	delete_line(filename, file_line, num_of_occurs);
	return 0;
}

//test123
//woo gitHub thingy works
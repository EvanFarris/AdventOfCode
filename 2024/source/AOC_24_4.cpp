//Solution to Advent of Code's 2024 day 4 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<string>&, string);
void checkAllDirections(vector<string>&, int, int, int&);
bool foundCompleteWord(vector<string>&, int, int, int, int);
void part_1_calculation(vector<string>&);
void part_2_calculation(vector<string>&);

int main() {
	vector<string> rows, testRows;
	cout << "Example Data" << endl;
	rff(testRows, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_4.txt");
	part_1_calculation(testRows);
	part_2_calculation(testRows);
	cout << "Challenge Data" << endl;
	rff(rows, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_4.txt");
	part_1_calculation(rows);
	part_2_calculation(rows);
	return 0;
}

void rff(vector<string>& rows, string path) {
	rows.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		rows.push_back(l);
	}

	f.close();
}

void part_1_calculation(vector<string>& rows) {
	int occurences = 0;
	for (int i = 0; i < rows.size(); i++) {
		for (int j = 0; j < rows[i].size(); j++) {
			if(rows[i][j] == 'X') {
				checkAllDirections(rows, i, j, occurences);
			}
		}
	}
	cout << "The answer to part 1 of the challenge is: " << occurences << endl;
}

void part_2_calculation(vector<string>& rows) {
	int occurences = 0;
	for (int i = 0; i < rows.size(); i++) {
		for (int j = 0; j < rows[i].size(); j++) {
			if (rows[i][j] == 'A') {
				if ((foundCompleteWord(rows, i - 2, j - 2, 1, 1) || foundCompleteWord(rows, i + 2, j + 2, -1, -1)) && (foundCompleteWord(rows, i + 2, j - 2, -1, 1) || foundCompleteWord(rows, i - 2, j + 2, 1, -1))) {
					occurences++;
				}
			}
		}
	}
	cout << "The answer to part 2 of the challenge is: " << occurences << endl;
}

void checkAllDirections(vector<string>& rows, int i, int j, int& occurences) {
	for (int dI = -1; dI < 2; dI++) {
		for (int dJ = -1; dJ < 2; dJ++) {
			if (foundCompleteWord(rows, i, j, dI, dJ)) {
				occurences++;
			}
		}
	}
}

bool foundCompleteWord(vector<string>& rows, int i, int j, int changeI, int changeJ) {
	string rest = "MAS";
	for (int ind = 0; ind < rest.size(); ind++) {
		int newI = i + changeI * (ind + 1);
		int newJ = j + changeJ * (ind + 1);

 		if (!(newI >= 0 && newI < rows.size()) || !(newJ >= 0 && newJ < rows[newI].size())) { return false; }
		if (rows[newI][newJ] != rest[ind]) { return false; }
	}
	return true;
}
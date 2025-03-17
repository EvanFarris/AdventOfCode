//Solution to Advent of Code's 2024 day 3 challenge
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<vector<int>>&, string, bool);
void part_1_calculation(vector<vector<int>>&);
void part_2_calculation(vector<vector<int>>&);

int main() {
	vector<vector<int>> reports, testReports;
	cout << "Example Data" << endl;
	rff(testReports, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_3.txt", false);
	part_1_calculation(testReports);
	rff(testReports, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_3.txt", true);
	part_2_calculation(testReports);
	cout << "Challenge Data" << endl;
	rff(reports, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_3.txt", false);
	part_1_calculation(reports);
	rff(reports, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_3.txt", true);
	part_2_calculation(reports);
	return 0;
}

//Reads lines in from file given, adds eligible number pairs into reports. If checkDo == true, then we look for do/don't commands, for part 2 of the challenge.
//Naive implementation, probably would be better to use regex capture groups for a more elegant approach.
void rff(vector<vector<int>>& reports, string path, bool checkDo) {
	reports.clear();
	ifstream f(path);
	string l;

	bool isEnabled = true;

	while (getline(f, l)) {
		vector<int> v = {};
		int n1Start = 0, n1Len = 0, n2Start = 0, n2Len = 0, insInd = 0;
		string ins = "mul(X,X)";

		for (int i = 0; i < l.size(); i++) {
			//If the current character matches the current instruction letter and the letter matched is not the number sentinel (X)
			if (l[i] == 'd') {
				if (i + 3 < l.size() && l.substr(i,4).compare("do()") == 0) {
					isEnabled = true;
				}
				else if (i + 6 < l.size() && l.substr(i, 7).compare("don't()") == 0) {
					isEnabled = false;
				}
			}
			else if (l[i] == ins[insInd] && ins[insInd] != 'X') {
				//If it's the last digit and it detected two numbers 
				if (insInd == ins.size() - 1) { //If it's the last index of the instruction, there should be two numbers found
					if (!checkDo || (checkDo && isEnabled)) {
						int temp1 = stoi(l.substr(n1Start, n1Len));
						int temp2 = stoi(l.substr(n2Start, n2Len));
						reports.push_back({ temp1,temp2 });
					}
					n1Len = 0;
					n2Len = 0;
					insInd = 0;
				}
				else {
					insInd++;
				}
			} 
			else if (l[i] >= '0' && l[i] <='9' && ins[insInd] == 'X') { //If the character is a number and the current insInd is on the sentinel value
				if (n1Len == 0) {
					n1Start = i;
					while (i < l.size() && l[i] >= '0' && l[i] <= '9') {
						n1Len++;
						i++;
					}
					if (i == l.size() || l[i] != ',') {
						n1Len = 0;
						insInd = 0;
					}
					else {
						insInd++;
					}
					i--;
				}
				else {
					n2Start = i;
					while (i < l.size() && l[i] >= '0' && l[i] <= '9') {
						n2Len++;
						i++;
					}
					if (i == l.size() || l[i] != ')') {
						n1Len = 0;
						n2Len = 0;
						insInd = 0;
					}
					else {
						insInd++;
					}
					i--;
				}
			}
			else {
				insInd = 0;
				n1Len = 0;
				n2Len = 0;
			}
		}

	}
	f.close();
}

void part_1_calculation(vector<vector<int>>& reports) {
	int result = 0;
	for (int i = 0; i < reports.size(); i++) {
		result += reports[i][0] * reports[i][1];
	}
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<vector<int>>& reports) {
	int result = 0;
	for (int i = 0; i < reports.size(); i++) {
		result += reports[i][0] * reports[i][1];
	}
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}
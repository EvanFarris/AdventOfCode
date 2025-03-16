//Solution to Advent of Code's 2024 day 2 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<vector<int>>&, string);

void part_1_calculation(vector<vector<int>>&);
void part_2_calculation(vector<vector<int>>&);
bool isReportSafe(vector<int>, int);
int main() {
	vector<vector<int>> reports, testReports;
	cout << "Example Data" << endl;
	rff(testReports, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_2.txt");
	part_1_calculation(testReports);
	part_2_calculation(testReports);
	cout << "Challenge Data" << endl;
	rff(reports, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_2.txt");
	part_1_calculation(reports);
	part_2_calculation(reports);

}

void rff(vector<vector<int>>& reports, string path) {
	reports.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		vector<int> v = {};
		int nStart = 0, ind = 0, length = 0;
		while (ind != l.size()) {
			if (l[ind] == ' ') {
				if (length > 0) {
					v.push_back(stoi(l.substr(nStart, length)));
				}
				nStart = ind + 1;
				length = 0;
			}
			else {
				length++;
			}
			ind++;
		}
		
		if (length > 0) {
			v.push_back(stoi(l.substr(nStart, length)));
		}
		reports.push_back(v);
	}
	f.close();
}

void part_1_calculation(vector<vector<int>>& reports) {
	int result = 0;
	for (int i = 0; i < reports.size(); i++) {
		if (isReportSafe(reports[i], -1)) { result++; }
	}

	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<vector<int>>& reports) {
	int result = 0;
	bool wasBroken, isIncreasing;
	for (int i = 0; i < reports.size(); i++) {
		if (isReportSafe(reports[i], -1)) { result++; }
		else {
			for (int j = 0; j < reports[i].size(); j++) {
				if (isReportSafe(reports[i], j)) {
					result++;
					break;
				}
			}
		}
	}
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

bool isReportSafe(vector<int> report, int indToRemove) {
	if (indToRemove >= 0 && indToRemove < report.size()) {
		report.erase(report.begin() + indToRemove);
	}
	bool wasBroken = false, isIncreasing;

	wasBroken = false;
	if (report[0] < report[1]) { isIncreasing = true; }
	else { isIncreasing = false; }

	for (int j = 0; j < report.size() - 1; j++) {
		int diff = abs(report[j] - report[j + 1]);
		if (diff < 1 || diff > 3 || (isIncreasing && report[j] > report[j + 1]) || (!isIncreasing && report[j] < report[j + 1])) {
			return false;
		}
	}
	return true;
}
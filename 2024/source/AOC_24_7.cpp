//Solution to Advent of Code's 2024 day 7 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<long long>&, vector<vector<long long>>&, vector<long long>&, vector<vector<long long>>&, string);

void part_1_calculation(vector<long long>, vector<vector<long long>>, vector<long long>&, vector<vector<long long>>&, long long&);
void part_2_calculation(vector<long long>, vector<vector<long long>>, long long);

bool recOperator(long long goal, vector<long long> vals, long long curVal, bool);
long long cat(long long fVal, long long sVal);

int main() {
	vector<vector<long long>> vals, testVals, lVals, testLVals;
	vector<long long> goals, testGoals, lGoals, testLGoals;
	long long result = 0, testResult = 0;

	cout << "Example Data" << endl;
	rff(testGoals, testVals, testLGoals, testLVals,  "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_7.txt");
	part_1_calculation(testGoals, testVals, testLGoals, testLVals, testResult);
	part_2_calculation(testLGoals, testLVals, testResult);
	cout << "Challenge Data" << endl;
	rff(goals, vals, lGoals, lVals, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_7.txt");
	part_1_calculation(goals, vals, lGoals, lVals, result);
	part_2_calculation(lGoals, lVals, result);

}

void rff(vector<long long>& goals, vector < vector <long long>> &vals, vector<long long>& lGoals, vector < vector <long long>>& lVals, string path) {
	goals.clear();
	vals.clear();
	lGoals.clear();
	lVals.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		vector<long long> v = {};
		int nStart = 0, ind = 0, length = 0;
		while (ind != l.size()) {
			if (l[ind] == ' ') {
				if (length > 0) {
					v.push_back(stoll(l.substr(nStart, length)));
				}
				nStart = ind + 1;
				length = 0;
			}
			else if (l[ind] == ':') {
				if (length > 0) {

					goals.push_back(stoll(l.substr(nStart, length)));
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
		vals.push_back(v);
	}
	f.close();
}

void part_1_calculation(vector<long long> goals, vector<vector<long long>> vals, vector<long long>& lGoals, vector<vector<long long>>& lVals, long long& res) {
	long long result = 0;
	long long beg;
	for (int i = 0; i < goals.size(); i++) {
		beg = vals[i][0];
		vals[i].erase(vals[i].begin());
		if (recOperator(goals[i], vals[i], beg, true)) {
			result += goals[i];
		}
		else {
			lGoals.push_back(goals[i]);
			vals[i].emplace(vals[i].begin(), beg);
			lVals.push_back(vals[i]);
		}
	}
	res = result;
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<long long> goals, vector<vector<long long>> vals, long long res) {
	long long result = res;
	long long beg;
	for (int i = 0; i < goals.size(); i++) {
		beg = vals[i][0];
		vals[i].erase(vals[i].begin());
		if (recOperator(goals[i], vals[i], beg, false)) {
			result += goals[i];
		}
	}
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

bool recOperator(long long goal, vector<long long> vals, long long curVal, bool isPartOne) {
	bool result;
	if (vals.size() == 1) {
		result = (goal == curVal * vals[0]) || (goal == curVal + vals[0]);
		if (!isPartOne) { result = result || goal == cat(curVal, vals[0]); }
		return result;
	}
	long long temp = vals[0];
	vals.erase(vals.begin());
	result = recOperator(goal, vals, curVal + temp, isPartOne) || recOperator(goal, vals, curVal * temp, isPartOne);
	if (!isPartOne) {
		result = result || recOperator(goal, vals, cat(curVal, temp), isPartOne);
	} 
	return result;
}

long long cat(long long fVal, long long sVal) {
	return stoll(to_string(fVal) + to_string(sVal));
}
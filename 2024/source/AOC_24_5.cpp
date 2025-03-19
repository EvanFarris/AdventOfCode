//Solution to Advent of Code's 2024 day 2 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;

void rff(vector<vector<int>>&, map<int, vector<int>>&, string);

void part_1_calculation(vector<vector<int>>&, map<int, vector<int>>&);
void part_2_calculation(vector<vector<int>>&, map<int, vector<int>>&);

bool isValidReport(vector<int>&, map<int, vector<int>>&);
void fixReport(vector<int>&, map<int, vector<int>>&);

int main() {
	vector<vector<int>> reports, testReports;
	map<int, vector<int>> rules, testRules;

	cout << "Example Data" << endl;
	rff(testReports, testRules, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_5.txt");
	part_1_calculation(testReports, testRules);
	part_2_calculation(testReports, testRules);
	cout << "Challenge Data" << endl;
	rff(reports, rules, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_5.txt");
	part_1_calculation(reports, rules);
	part_2_calculation(reports, rules);

}

void rff(vector<vector<int>>& reports, map<int, vector<int>> &rules, string path) {
	reports.clear();
	rules.clear();
	ifstream f(path);
	string l;
	bool partOne = true;
	int sepR, page1, page2;
	vector<int> v;
	while (getline(f, l)) {
		//Separator is 0 characters long
		if (l.size() == 0) {
			partOne = false;
			continue;
		}
		v.clear();
		if (partOne) {
			sepR = 0;
			while (l[sepR] != '|') { sepR++; }
			page1 = stoi(l.substr(0, sepR));
			page2 = stoi(l.substr(sepR + 1, l.size() - sepR - 1));
			v = rules[page1];
			v.push_back(page2);
			rules[page1] = v;
		}
		else {
			int nStart = 0, len = 0;
			for (int i = 0; i < l.size(); i++) {
				if (l[i] == ',') {
					v.push_back(stoi(l.substr(nStart, len)));
					nStart = i + 1;
					len = 0;
				}
				else {
					len++;
				}
			}
			v.push_back(stoi(l.substr(nStart, len)));
			reports.push_back(v);
		}

	}
	f.close();
}

void part_1_calculation(vector<vector<int>>& reports, map<int, vector<int>>& rules) {
	int result = 0;
	set<int> addedPages;
	vector<int> rls;
	//
	for (int i = 0; i < reports.size(); i++) {
		if (isValidReport(reports[i], rules)) {
			result += reports[i][reports[i].size() / 2];
		}
		
	}
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<vector<int>>& reports, map<int, vector<int>>& rules) {
	int result = 0;
	for (int i = 0; i < reports.size(); i++) {
		if (!isValidReport(reports[i], rules)) {
			fixReport(reports[i], rules);
			result += reports[i][reports[i].size() / 2];
		}
	}
	//Fix invalid reports && add middle element to result
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}


bool isValidReport(vector<int>& report, map<int, vector<int>>& rules) {
	vector<int> rls;
	set<int> addedPages;
	for (int j = 0; j < report.size(); j++) {
		//Check rules to see if a previous page in the rules have been added
		int curPage = report[j];
		rls = rules[curPage];
		for (int k = 0; k < rls.size(); k++) {
			int temp = rls[k];
			if (addedPages.find(temp) != addedPages.end()) {
				return false;
			}
		}
			addedPages.insert(curPage);
	}
	return true;
}

void fixReport(vector<int>& report, map<int, vector<int>>& rules) {
	vector<int> rls;
	set<int> addedPages = {};
	int earliestRuleBreak;
	for (int i = 0; i < report.size(); i++) {
		earliestRuleBreak = report.size();
		//Check rules for the rulebreak
		rls = rules[report[i]];
		for (int j = 0; j < rls.size(); j++) {
			if (addedPages.find(rls[j]) != addedPages.end()) {
				for (int k = 0; k < i; k++) {
					if (report[k] == rls[j] && k < earliestRuleBreak) {
						earliestRuleBreak = k;
					}
				}
			}
		}
		//Add page
		addedPages.insert(report[i]);

		if (earliestRuleBreak != report.size()) {
			//Move element behind earliest rule breaking page
			int tmp = report[i];
			for (int j = i; j > earliestRuleBreak; j--) {
				report[j] = report[j - 1];
			}
			report[earliestRuleBreak] = tmp;
		}	
	}	
}
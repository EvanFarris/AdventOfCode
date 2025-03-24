//Solution to Advent of Code's 2024 day 10 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void rff(vector<string>&, vector<vector<bool>>&, string);

void part_1_calculation(vector<string>&, vector<vector<bool>>);
void part_2_calculation(vector<string>&, vector<vector<bool>>);
int dfs(vector<string>& top, int x, int y, char step, vector<vector<bool>>& found, bool p2);

int main() {
	vector<string> top;
	vector<vector<bool>> found;
	cout << "Example Data" << endl;
	rff(top, found, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_10.txt");
	part_1_calculation(top, found);
	part_2_calculation(top, found);
	cout << "Challenge Data" << endl;
	rff(top, found, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_10.txt");
	part_1_calculation(top, found);
	part_2_calculation(top, found);

}

void rff(vector<string>& top, vector<vector<bool>>& found, string path) {
	top.clear();
	found.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		top.push_back(l);
		found.push_back(vector<bool>(l.size(), false));
	}
	f.close();
}

void part_1_calculation(vector < string> &top, vector<vector<bool>> found) {
	int result = 0;
	vector<vector<bool>> temp = found;
	for (size_t i = 0; i < top.size(); i++) {
		for (size_t j = 0; j < top[i].size(); j++) {
			temp = found;
			if (top[i][j] == '0') {
				result += dfs(top, i, j, '0', temp, false);
			}
		}
	}
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<string> &top, vector<vector<bool>> found) {
	int result = 0;
	vector<vector<bool>> temp = found;
	for (size_t i = 0; i < top.size(); i++) {
		for (size_t j = 0; j < top[i].size(); j++) {
			temp = found;
			if (top[i][j] == '0') {
				result += dfs(top, i, j, '0', temp, true);
			}
		}
	}
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}


int dfs(vector<string>& top, int x, int y, char step, vector<vector<bool>>& found, bool p2) {
	if (step == '9' && (!found[x][y] || p2)) {
		found[x][y] = true;
		return 1;
	}
	int tot = 0;

	if (x - 1 >= 0 && top[x - 1][y] == step + 1) { tot += dfs(top, x - 1, y, step + 1, found, p2); }
	if (x + 1 < top.size() && top[x + 1][y] == step + 1)	{ tot += dfs(top, x + 1, y, step + 1, found, p2); }
	if (y - 1 >= 0 && top[x][y - 1] == step + 1)			{ tot += dfs(top, x, y - 1, step + 1, found, p2); }
	if (y + 1 < top[x].size() && top[x][y + 1] == step + 1) { tot += dfs(top, x, y + 1, step + 1, found, p2); }
	return tot;
}



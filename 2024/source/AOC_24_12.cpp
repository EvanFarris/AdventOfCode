//Solution to Advent of Code's 2024 day 12 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<string>&, vector<vector<int>>&, string);

void part_1_calculation(vector<string>&);
void part_2_calculation(vector<string>&, vector<vector<int>>&);
long getPrice(vector<string> field, bool, vector<vector<int>>&);
long dfs(vector<string>& field, size_t i, size_t j, bool, vector<vector<int>>&);
void dfsHelper(vector<string>& field, size_t i, size_t j, int& area, int& perimeter, char c, const vector<string>);
void dfsHelper2(vector<string>& field, size_t i, size_t j, int& area, int& perimeter, char c, const vector<string> cField, vector<vector<int>>& v);
void getEdges(const vector<string>& field, size_t i, size_t j, char c, bool& l, bool& b, bool& r, bool& t);
int main() {
	vector<string> field;
	vector<vector<int>> sField;
	cout << "Example Data" << endl;
	rff(field, sField, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_12.txt");
	part_1_calculation(field);
	part_2_calculation(field, sField);
	cout << "Challenge Data" << endl;
	rff(field , sField, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_12.txt");
	part_1_calculation(field);
	part_2_calculation(field, sField);

}

void rff(vector<string>& field, vector<vector<int>>& sField, string path) {
	field.clear();
	sField.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		field.push_back(l);
		sField.push_back(vector<int>(l.size(), 0));
	}
	f.close();
}

void part_1_calculation(vector<string>& field) {
	long result = 0;
	vector<vector<int>> nul;
	result = getPrice(field, false, nul);
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<string>& field, vector<vector<int>>& sField) {
	long result = 0;
	result = getPrice(field, true, sField);
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

long getPrice(vector<string> field, bool part2, vector<vector<int>>& v) {
	long price = 0;
	for (size_t i = 0; i < field.size(); i++) {
		for (size_t j = 0; j < field[i].size(); j++) {
			if (field[i][j] != '.') {
				price += dfs(field, i, j, part2, v);
			}
		}
	}

	return price;
}

long dfs(vector<string>& field, size_t i, size_t j, bool part2, vector<vector<int>>& v) {
	char c = field[i][j];
	int area = 0, perimeter = 0;
	if (!part2) {
		dfsHelper(field, i, j, area, perimeter, c, field);
	}
	else {
		dfsHelper2(field, i, j, area, perimeter, c, field, v);
	}
	
	//cout << c << " a: " << area << " p: " << perimeter << endl;
	return area * perimeter;
}

void dfsHelper(vector<string>& field, size_t i, size_t j, int& area, int& perimeter, char c, const vector<string> cField) {
	area++;
	field[i][j] = '.';
	if (i >= 1 && field[i - 1][j] == c) {
		dfsHelper(field, i - 1, j, area, perimeter, c, cField);
	}
	else if (i == 0 || (i >= 1 && cField[i - 1][j] != c)) {
		perimeter++;
	}

	if (j >= 1 && field[i][j - 1] == c) {
		dfsHelper(field, i, j - 1, area, perimeter, c, cField);
	}
	else if (j == 0 || (j >= 1 && cField[i][j-1] != c)) {
		perimeter++;
	}

	if (i + 1 < field.size() && field[i + 1][j] == c) {
		dfsHelper(field, i + 1, j, area, perimeter, c, cField);
	}
	else if(i + 1 == field.size() || (i + 1 < field.size() && cField[i+1][j] != c)) {
		perimeter++;
	}


	if (j + 1 < field[i].size() && field[i][j + 1] == c) {
		dfsHelper(field, i, j + 1, area, perimeter, c, cField);
	}
	else if(j + 1 == field[i].size() || (j+1 < field[i].size() && cField[i][j+1] != c)) {
		perimeter++;
	}
}

void dfsHelper2(vector<string>& field, size_t i, size_t j, int& area, int& sides, char c, const vector<string> cField, vector<vector<int>>& v) {
	//Take the spot off the board to not cause infinite recursion
	area++;
	field[i][j] = '.';

	bool lEdge = false, bEdge = false, rEdge = false, tEdge = false;
	int tmp1, tmp2;
	//Get all the edges in the square
	getEdges(cField, i, j, c, lEdge, bEdge, rEdge, tEdge);
	//If there is an edge, check it's neighbors to see if an existing edge in v to build off of
	if (lEdge) {
		//v is a 2d vector of ints, and we store the type of side bitwise in the element.
		v[i][j] = v[i][j] | 1;
		//Check neighbors orthogonal to current edge for the same side.
		if (i != 0 && cField[i - 1][j] == c) { tmp1 = v[i - 1][j] & 1; }
		else { tmp1 = 0; }
		if (i + 1 < cField.size() && cField[i + 1][j] == c) { tmp2 = v[i + 1][j] & 1; }
		else { tmp2 = 0; }
		//If there are two unconnected sides, we connect them and decrement the counter, as the two sides join to one.
		if (tmp1 && tmp2) { sides--; }
		else if (!tmp1 && !tmp2) { sides++; } // If there are no sides at all, we "create" a new side.
	}
	else if(!lEdge && field[i][j - 1] == c) { dfsHelper2(field, i, j - 1, area, sides, c, cField, v); }
	
	if (rEdge) {
		v[i][j] = v[i][j] | 2;
		if (i != 0 && cField[i - 1][j] == c) { tmp1 = v[i - 1][j] & 2; }
		else { tmp1 = 0; }
		if (i + 1 < cField.size() && cField[i + 1][j] == c) { tmp2 = v[i + 1][j] & 2; }
		else { tmp2 = 0; }
		if (tmp1 && tmp2) { sides--; }
		else if (!tmp1 && !tmp2) { sides++; }
	}
	else if (!rEdge && field[i][j + 1] == c) {dfsHelper2(field, i, j + 1, area, sides, c, cField, v);}
	
	if (tEdge) {
		v[i][j] = v[i][j] | 4;
		if (j != 0 && cField[i][j - 1] == c) { tmp1 = v[i][j - 1] & 4; }
		else { tmp1 = 0; }
		if (j + 1 < cField[i].size() && cField[i][j + 1] == c) { tmp2 = v[i][j + 1] & 4; }
		else { tmp2 = 0; }
		if (tmp1 && tmp2) { sides--; }
		else if (!tmp1 && !tmp2) { sides++; }
	}
	else if (!tEdge && field[i - 1][j] == c) {dfsHelper2(field, i - 1, j, area, sides, c, cField, v);}
	
	if (bEdge) {
		v[i][j] = v[i][j] | 8;
		if (j != 0 && cField[i][j - 1] == c) { tmp1 = v[i][j - 1] & 8; }
		else { tmp1 = 0; }
		if (j + 1< cField[i].size() && cField[i][j + 1] == c) { tmp2 = v[i][j + 1] & 8; }
		else { tmp2 = 0; }
		if (tmp1 && tmp2) { sides--; }
		else if (!tmp1 && !tmp2) { sides++; }
	}
	else if (!bEdge && field[i + 1][j] == c) {dfsHelper2(field, i + 1, j, area, sides, c, cField, v);}

}

void getEdges(const vector<string>& cField, size_t i, size_t j, char c, bool& l, bool& b, bool& r, bool& t) {
	//Check top
	if (i == 0 || cField[i - 1][j] != c) { t = true; }
	//Check bot
	if (i == cField.size() - 1 || cField[i + 1][j] != c) { b = true; }
	//Check left
	if (j == 0 || cField[i][j - 1] != c) { l = true; }
	//Check right
	if (j == cField[i].size() - 1 || cField[i][j + 1] != c) { r = true; }
}
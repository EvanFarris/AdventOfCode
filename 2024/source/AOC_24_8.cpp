//Solution to Advent of Code's 2024 day 8 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void rff(vector<string>&, vector<vector<bool>> &, string);

void part_1_calculation(vector<string>&, vector<vector<bool>> &);
void part_2_calculation(vector<string>&, vector<vector<bool>> &);

map<char, vector<vector<size_t>>> ptsMap;
bool isValid(size_t bx, size_t by, size_t x, size_t y);
size_t countTrue(vector<vector<bool>> antiNodes);

int main() {
	vector<string> area;
	vector<vector<bool>> antiNodes;
	cout << "Example Data" << endl;
	rff(area, antiNodes, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_8.txt");
	part_1_calculation(area, antiNodes);
	part_2_calculation(area, antiNodes);
	cout << "Challenge Data" << endl;
	rff(area, antiNodes, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_8.txt");
	part_1_calculation(area, antiNodes);
	part_2_calculation(area, antiNodes);

}

void rff(vector<string>& area, vector<vector<bool>>& antiNodes, string path) {
	area.clear();
	antiNodes.clear();
	ptsMap.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		area.push_back(l);
		antiNodes.push_back(vector<bool>(l.size(), false));
	}
	f.close();
}

//Assumes area and antiNodes size > 0
void part_1_calculation(vector<string>& area, vector<vector<bool>>& antiNodes) {
	size_t result = 0;
	size_t bX = area.size(), bY = area[0].size(), dx, dy;
	vector<vector<size_t>> pts;
	for (size_t i = 0; i < bX; i++) {
		for (size_t j = 0; j < bY; j++) {
			if (area[i][j] != '.') {
				//Get vector of points with the same frequency
				pts = ptsMap[area[i][j]];
				//Find and put antinodes on the antiNodes 2d vector
				if (pts.size()) {
					for (size_t p = 0; p < pts.size(); p++) {
						//Current point is either more to the right or down in the matrix
						dx = i - pts[p][0];
						dy = j - pts[p][1];
						if (isValid(bX, bY, i + dx, j + dy)) {
							antiNodes[i + dx][j + dy] = true;
						}
						if (isValid(bX, bY, pts[p][0] - dx, pts[p][1] - dy)) {
							antiNodes[pts[p][0] - dx][pts[p][1] - dy] = true;
						}

					}
				}
				//Add point to the map
				pts.push_back({ i,j });
				ptsMap[area[i][j]] = pts;
			}
		}
	}

	result = countTrue(antiNodes);
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<string>& area, vector<vector<bool>>& antiNodes) {
	//Map is already built for this part of the challenge so we dont have to add points.
	size_t result = 0;
	size_t bX = area.size(), bY = area[0].size(), dx, dy, tempI, tempJ;
	vector<vector<size_t>> pts;
	for (size_t i = 0; i < bX; i++) {
		for (size_t j = 0; j < bY; j++) {
			if (area[i][j] != '.') {
				//Get vector of points with the same frequency
				pts = ptsMap[area[i][j]];
				//Find and put antinodes on the antiNodes 2d vector
				if (pts.size()) {
					for (size_t p = 0; p < pts.size(); p++) {
						if (i == pts[p][0] && j == pts[p][1]) { 
							//AntiNodes occur on the antennas locations, then continue to avoid dx == dy == 0 loop
							antiNodes[i][j] = true;
							continue; 
						}
						//Current point is either more to the right or down in the matrix
						dx = i - pts[p][0];
						dy = j - pts[p][1];
						tempI = i;
						tempJ = j;
						while (isValid(bX, bY, tempI + dx, tempJ + dy)) {
							antiNodes[tempI + dx][tempJ + dy] = true;
							tempI += dx;
							tempJ += dy;
						}
						tempI = pts[p][0];
						tempJ = pts[p][1];
						while (isValid(bX, bY, tempI - dx, tempJ - dy)) {
							antiNodes[tempI - dx][tempJ - dy] = true;
							tempI -= dx;
							tempJ -= dy;
						}

					}
				}
			}
		}
	}

	result = countTrue(antiNodes);

	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

bool isValid(size_t bx, size_t by, size_t x, size_t y) {
	return x >= 0 && x < bx && y >= 0 && y < by;
}

size_t countTrue(vector<vector<bool>> antiNodes) {
	size_t result = 0;
	for (size_t i = 0; i < antiNodes.size(); i++) {
		for (size_t j = 0; j < antiNodes[i].size(); j++) {
			result += antiNodes[i][j];
		}
	}
	return result;
}
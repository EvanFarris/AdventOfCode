//Solution to Advent of Code's 2024 day 6 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<string>&, vector<vector<bool>>&, string);

void part_1_calculation(vector<string>&, vector<vector<bool>>);
void part_2_calculation(vector<string>&, vector<vector<bool>>);

void findStart(vector<string>& area, int& x, int& y);
void solveMaze(vector<string>& area, vector<vector<bool>>& checked, int startX, int startY);
bool isValid(vector<string>& area, int posX, int posY);
int getScore(vector<vector<bool>>& checked);
void moveOnce(vector<string>& area, int& startX, int& startY);
bool findLoop(vector<string> area, int initX, int initY);

int main() {
	vector<string> area, testArea;
	vector<vector<bool>> checked;

	cout << "Example Data" << endl;
	rff(testArea, checked, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_6.txt");
	part_1_calculation(testArea, checked);
	part_2_calculation(testArea, checked);
	cout << "Challenge Data" << endl;
	rff(area, checked, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_6.txt");
	part_1_calculation(area, checked);
	part_2_calculation(area, checked);

}

void rff(vector<string>& area, vector<vector<bool>>& checked, string path) {
	area.clear();
	checked.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		vector<bool> v(l.size(), false);
		area.push_back(l);
		checked.push_back(v);
	}

	f.close();
}

void part_1_calculation(vector<string>& area, vector<vector<bool>> checked) {
	int result = 0;
	int posX, posY;
	findStart(area, posX, posY);
	char startDir = area[posX][posY];
	solveMaze(area, checked, posX, posY);
	result = getScore(checked);
	area[posX][posY] = startDir;
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<string>& area, vector<vector<bool>> checked) {
	int result = 0;
	int posX, posY;
	findStart(area, posX, posY);
	int initX = posX;
	int initY = posY;
	static char initDir = area[initX][initY];
	//All possible contenders are going to be in checked
	solveMaze(area, checked, initX, initY);
	//Initial position is not allowed to be a contender
	checked[initX][initY] = false;
	area[initX][initY] = initDir;

	for (int x = 0; x < checked.size(); x++) {
		for (int y = 0; y < checked[x].size(); y++) {
			if (checked[x][y]) {
				area[x][y] = '#';
				if (findLoop(area, initX, initY)) {
					result++;
				}
				area[x][y] = '.';
			}
		}
	}

	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

void findStart(vector<string>& area, int& x, int& y) {
	for (int i = 0; i < area.size(); i++) {
		for (int j = 0; j < area[i].size(); j++) {
			switch (area[i][j]) {
				case '^':
				case '>':
				case '<':
				case 'V':
					x = i;
					y = j;
					return;
					break;
				default:
					break;
			}
		}
	}
}

bool isValid(vector<string>& area, int posX, int posY) {
	return (posX >= 0 && posY >= 0 && posX < area.size() && posY < area[0].size());
}

int getScore(vector<vector<bool>>& checked) {
	int total = 0;
	for (int i = 0; i < checked.size(); i++) {
		for (int j = 0; j < checked[i].size(); j++) {
			total += checked[i][j];
		}
	}
	return total;
}

void solveMaze(vector<string>& area, vector<vector<bool>>& checked, int startX, int startY) {
	int posX = startX, posY = startY, newX, newY;
	if (!isValid(area, posX, posY)) {
		return;
	}

	char curDir;
	while (isValid(area ,posX, posY)) {
		checked[posX][posY] = true;
		curDir = area[posX][posY];
		area[posX][posY] = '.';
		newX = posX;
		newY = posY;
		switch (curDir) {
			case '^':
				newX--;
				break;
			case '>':
				newY++;
				break;
			case '<':
				newY--;
				break;
			case 'V':
				newX++;
				break;
			default:
				break;
		}
		//
		if (isValid(area, newX, newY)) {
			if (area[newX][newY] == '#') {
				switch (curDir) {
				case '^':
					curDir = '>';
					break;
				case '>':
					curDir = 'V';
					break;
				case 'V':
					curDir = '<';
					break;
				case '<':
					curDir = '^';
					break;
				}
			}
			else {
				posX = newX;
				posY = newY;
			}
			area[posX][posY] = curDir;
		}
		else { return; }

	}
}

bool findLoop(vector<string> area, int initX, int initY) {
	int sloX = initX, sloY = initY, fasX = initX, fasY = initY;
	char initDir = area[initX][initY];
	vector<string> sloArea(area);
	//Set initial positions
	moveOnce(area, fasX, fasY);
	moveOnce(area, fasX, fasY);
	moveOnce(sloArea, sloX, sloY);
	while (isValid(area, fasX, fasY) && isValid(sloArea, sloX, sloY)) {
		moveOnce(area, fasX, fasY);
		if (fasX == sloX && fasY == sloY && area[fasX][fasY] == sloArea[sloX][sloY]) { return true; }
		else if (!isValid(area, fasX, fasY)) { return false; }

		moveOnce(area, fasX, fasY);
		if (fasX == sloX && fasY == sloY && area[fasX][fasY] == sloArea[sloX][sloY]) { return true; }
		else if (!isValid(area, fasX, fasY)) { return false; }

		moveOnce(sloArea, sloX, sloY);
	}
	return false;
}

void moveOnce(vector<string>& area, int& posX, int& posY) {
	char curDir;
	int newX, newY;

	curDir = area[posX][posY];
	area[posX][posY] = '.';
	newX = posX;
	newY = posY;
	switch (curDir) {
	case '^':
		newX--;
		break;
	case '>':
		newY++;
		break;
	case '<':
		newY--;
		break;
	case 'V':
		newX++;
		break;
	default:
		break;
	}
	//
	if (isValid(area, newX, newY)) {
		if (area[newX][newY] == '#') {
			switch (curDir) {
			case '^':
				curDir = '>';
				break;
			case '>':
				curDir = 'V';
				break;
			case 'V':
				curDir = '<';
				break;
			case '<':
				curDir = '^';
				break;
			}
		}
		else {
			posX = newX;
			posY = newY;
		}
		area[posX][posY] = curDir;
	}
	else {
		posX = newX;
		posY = newY;
	}
}
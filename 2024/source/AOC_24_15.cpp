//Solution to Advent of Code's 2024 day 15 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<string>&, vector<string>&, const string);

void part_1_calculation(vector<string>, vector<string>&);
void part_2_calculation(vector<string>&, vector<string>&);

void getRobotPosition(size_t &, size_t &, vector<string> &);
void doDirections(vector<string>&, vector<string>&, size_t, size_t);
void doDirections2(vector<string>&, vector<string>&, size_t, size_t);
void convertToLargerWarehouse(vector<string>&, vector<string>&);
bool canPush(vector<string>&, size_t, size_t, int, int);
void recPush(vector<string>& warehouse, size_t robX, size_t robY, int dirX, int dirY);
void getDir(char, int&, int&);

void printWarehouse(vector<string>&);
size_t calcScore(vector<string>&);

int main() {
	vector<string> warehouse, moves;
	cout << "Example Data" << endl;
	rff(warehouse, moves, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_small_example_15.txt");
	part_1_calculation(warehouse, moves);
	part_2_calculation(warehouse, moves);
	rff(warehouse, moves, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_15.txt");
	part_1_calculation(warehouse, moves);
	part_2_calculation(warehouse, moves);
	cout << "Challenge Data" << endl;
	rff(warehouse, moves, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_15.txt");
	part_1_calculation(warehouse, moves);
	part_2_calculation(warehouse, moves);

}

void rff(vector<string>& warehouse, vector<string>& moves, const string path) {
	warehouse.clear();
	moves.clear();
	ifstream f(path);
	string l;
	vector<string>* vecPtr = &warehouse;

	while (getline(f, l)) {
		if (l.empty()) {
			vecPtr = &moves;
			continue;
		}
		(*vecPtr).push_back(l);
	}
	f.close();
}

void part_1_calculation(vector<string> warehouse, vector<string>& moves) {
	size_t x = 0, y = 0;
	
	getRobotPosition(x, y, warehouse);
	doDirections(warehouse, moves, x, y);
	
	printWarehouse(warehouse);
	cout << "The answer to part 1 of the challenge is: " << calcScore(warehouse) << endl;
}

void part_2_calculation(vector<string>& warehouse, vector<string>& moves) {
	size_t x = 0, y = 0;
	vector<string> newW;
	convertToLargerWarehouse(warehouse, newW);
	getRobotPosition(x, y, newW);
	doDirections2(newW, moves, x, y);

	printWarehouse(newW);
	cout << "The answer to part 2 of the challenge is: " << calcScore(newW) << endl;
}

void getRobotPosition(size_t& x, size_t& y, vector<string>& warehouse) {
	for (size_t row = 0; row < warehouse.size(); row++) {
		for (size_t col = 0; col < warehouse[row].size(); col++) {
			if (warehouse[row][col] == '@') {
				x = row;
				y = col;
				return;
			}
		}
	}
}


void printWarehouse(vector<string>& warehouse) {
	for (size_t row = 0; row < warehouse.size(); row++) {
		cout << warehouse[row] << endl;
	}
}
 
size_t calcScore(vector<string>& warehouse) {
	size_t res = 0;
	for (size_t row = 0; row < warehouse.size(); row++) {
		for (size_t col = 0; col < warehouse[row].size(); col++) {
			if (warehouse[row][col] == 'O' || warehouse[row][col] == '[') {
				res += 100 * row + col;
			}
		}
	}
	return res;
}

void doDirections(vector<string>& warehouse, vector<string>& moves, size_t robX, size_t robY) {
	int dirX, dirY;
	size_t tX, tY, ctr = 0;

	for (size_t row = 0; row < moves.size(); row++) {
		for (size_t col = 0; col < moves[row].size(); col++) {
			//Get the change in coordinates
			switch (moves[row][col]) {
			case '^':
				dirX = -1;
				dirY = 0;
				break;
			case 'v':
				dirX = 1;
				dirY = 0;
				break;
			case '<':
				dirX = 0;
				dirY = -1;
				break;
			case '>':
				dirX = 0;
				dirY = 1;
				break;
			}

			//Find the first empty space
			tX = robX + dirX;
			tY = robY + dirY;
			while (warehouse[tX][tY] != '.' && warehouse[tX][tY] != '#') {
				tX += dirX;
				tY += dirY;
			}
			//If it finds a free space, then move everything over, otherwise nothing happens.
			if (warehouse[tX][tY] == '.') {
				while (tX != robX || tY != robY) {
					warehouse[tX][tY] = warehouse[tX - dirX][tY - dirY];
					tX -= dirX;
					tY -= dirY;
				}
				warehouse[robX][robY] = '.';
				robX += dirX;
				robY += dirY;
				
			}

		}
	}
}

void doDirections2(vector<string>& warehouse, vector<string>& moves, size_t robX, size_t robY) {
	int dirX, dirY;
	for (size_t row = 0; row < moves.size(); row++) {
		for (size_t col = 0; col < moves[row].size(); col++) {
			getDir(moves[row][col], dirX, dirY);
			if(canPush(warehouse, robX, robY, dirX, dirY)) {
				recPush(warehouse, robX, robY, dirX, dirY);
				robX += dirX;
				robY += dirY;
			}

		}
	}
}

void getDir(char c, int& dirX, int& dirY) {
	switch (c) {
	case '^':
		dirX = -1;
		dirY = 0;
		break;
	case 'v':
		dirX = 1;
		dirY = 0;
		break;
	case '<':
		dirX = 0;
		dirY = -1;
		break;
	case '>':
		dirX = 0;
		dirY = 1;
		break;
	}
}

//Robot initially calls this, then recursive
bool canPush(vector<string>& warehouse, size_t robX, size_t robY, int dirX, int dirY) {
	//Moving up/down
	if (dirX) {
		switch (warehouse[robX + dirX][robY]) {
		case '.':
			return true;
			break;
		case '#':
			return false;
			break;
		case '[':
			return canPush(warehouse, robX + dirX, robY, dirX, dirY) && canPush(warehouse, robX + dirX, robY + 1, dirX, dirY);
			break;
		case ']':
			return canPush(warehouse, robX + dirX, robY, dirX, dirY) && canPush(warehouse, robX + dirX, robY - 1, dirX, dirY);
			break;

		}
	}
	else { //Moving left/right
		while (warehouse[robX][robY] != '#' && warehouse[robX][robY] != '.') {
			robY += dirY;
		}
		return warehouse[robX][robY] == '.';
	}
}

//Guaranteed no '#' 
void recPush(vector<string>& warehouse, size_t robX, size_t robY, int dirX, int dirY) {
	//Moving up/down
	if (dirX) {
		switch (warehouse[robX + dirX][robY]) {
		case '[':
			recPush(warehouse, robX + dirX, robY, dirX, dirY);
			recPush(warehouse, robX + dirX, robY + 1, dirX, dirY);
			break;
		case ']':
			recPush(warehouse, robX + dirX, robY, dirX, dirY); 
			recPush(warehouse, robX + dirX, robY - 1, dirX, dirY);
			break;
		default:
			break;
		}
		warehouse[robX + dirX][robY + dirY] = warehouse[robX][robY];
		warehouse[robX][robY] = '.';
	}
	else { //Moving left/right
		size_t tempY = robY;
		while (warehouse[robX][tempY] != '#' && warehouse[robX][tempY] != '.') {
			tempY += dirY;
		}
		while (tempY != robY) {
			warehouse[robX][tempY] = warehouse[robX][tempY - dirY];
			tempY -= dirY;
		}
		warehouse[robX][robY] = '.';
	}
}

void convertToLargerWarehouse(vector<string>& inW, vector<string>& outW) {
	outW.clear();
	string s;
	for (size_t row = 0; row < inW.size(); row++) {
		s = "";
		for (size_t col = 0; col < inW[row].size(); col++) {
			switch (inW[row][col]) {
			case '#':
				s.append("##");
				break;
			case '@':
				s.append("@.");
				break;
			case 'O' :
				s.append("[]");
				break;
			case '.':
				s.append("..");
				break;
			}
		}
		outW.push_back(s);
	}
}
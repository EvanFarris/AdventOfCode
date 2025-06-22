//Solution to Advent of Code's 2024 day 2 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void rff(vector<vector<int>>&, vector<vector<int>>&, string);

void part_1_calculation(vector<vector<int>>&, vector<vector<int>>&, int, int);
void part_2_calculation(vector<vector<int>>&, vector<vector<int>>&);

struct notablePoint {
	int frameNum;
	long heuristicValue;
};

void getHeuristics(vector<vector<int>> positions, vector<vector<int>> velocities, vector<notablePoint>& np);
void printTopTrees(vector<vector<int>> positions, vector<vector<int>> velocities, vector<notablePoint>& np);
void printFrame(vector<vector<int>>& positions, vector<vector<int>>& velocities, notablePoint);

int main() {
	vector<vector<int>> positions, velocities;
	cout << "Example Data" << endl;
	rff(positions, velocities, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_14.txt");
	part_1_calculation(positions, velocities, 11, 7);
	//part_2_calculation(testReports);
	cout << "Challenge Data" << endl;
	rff(positions, velocities, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_14.txt");
	part_1_calculation(positions, velocities, 101, 103);
	part_2_calculation(positions, velocities);

}

void rff(vector<vector<int>>& positions, vector<vector<int>>& velocities, string path) {
	positions.clear();
	velocities.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		vector<int> v = {};
		int nStart = 2, ind = 2, length = 0;
		//Put all four numbers into temp vector v
		while (ind < l.size()) {
			if (l[ind] == ' ' || l[ind] == ',') {
				if (length > 0) {
					v.push_back(stoi(l.substr(nStart, length)));
				}
				nStart = ind + 1;
				length = 0;
			}
			else if(l[ind] <= '9' && l[ind] >= '0' || l[ind] == '-') {
				length++;
			}
			else {
				nStart = ind + 1;
			}
			ind++;
		}

		if (length > 0) {
			v.push_back(stoi(l.substr(nStart, length)));
		}
		//Separate position and velocity vectors, position is the first 2 numbers in v, velocity in the last two.
		vector<int> pPos(v.begin(), v.begin() + 2);
		vector<int> vPos(v.begin() + 2, v.begin() + 4);
		positions.push_back(pPos);
		velocities.push_back(vPos);
	}
	f.close();
}

void part_1_calculation(vector<vector<int>>& positions, vector<vector<int>>& velocities, int maxX, int maxY) {
	int result = 0;
	int numSteps = 100, tX, tY, q1 = 0, q2 = 0, q3 = 0, q4 = 0;
	for (size_t i = 0; i < positions.size(); i++) {
		//Get new position
		tX = (positions[i][0] + velocities[i][0] * numSteps) % maxX;
		tY = (positions[i][1] + velocities[i][1] * numSteps) % maxY;
		if (tX < 0) { tX += maxX; }
		if (tY < 0) { tY += maxY; }
		//cout << tX << " " << tY << endl;
		if (tX == maxX / 2 || tY == maxY / 2) { continue; }

		if (tX < maxX / 2) {
			if (tY < maxY / 2) {
				q1++;
			}
			else {
				q3++;
			}
		}
		else {
			if (tY < maxY / 2) {
				q2++;
			}
			else {
				q4++;
			}
		}
	}
	//cout << q1 << " " << q2 << " " << q3 << " " << q4 << endl;
	cout << "The answer to part 1 of the challenge is: " << q1 * q2 * q3 * q4 << endl;
}

bool np_sorter(notablePoint const& lhs, notablePoint const& rhs) {
	return lhs.heuristicValue < rhs.heuristicValue;
}
void part_2_calculation(vector<vector<int>>& positions, vector<vector<int>>& velocities) {
	int result = 0;
	vector<notablePoint> np;
	getHeuristics(positions, velocities, np);
	//Answer is shown while printing the trees to the console, sideways near the end.
	printTopTrees(positions, velocities, np);
}

void getHeuristics(vector<vector<int>> positions, vector<vector<int>> velocities, vector<notablePoint>& np) {
	int maxFrames = 101 * 103;
	int maxX = 101, maxY = 103;
	//Magic number sets that increase as the positions get further down and closer to the center.
	//Definitely not optimized, but it shows in the top 100 frames (82).
	vector<int> heurY = { 0, 5, 40, 80, 100, 300, 1000, 2000, 3000, 5000, 0 };
	vector<int> heurX = { 1,20,50,300,200,200,300,50,20,1};
	long heur;
	notablePoint n{};
	for (int j = 0; j < maxFrames; j++) {
		heur = 0;
		n.frameNum = j + 1;
		for (size_t i = 0; i < positions.size(); i++) {
			//Get new position
			positions[i][0] = (positions[i][0] + velocities[i][0]) % maxX;
			positions[i][1] = (positions[i][1] + velocities[i][1]) % maxY;
			if (positions[i][0] < 0) { positions[i][0] += maxX; }
			if (positions[i][1] < 0) { positions[i][1] += maxY; }
			//cout << tX << " " << tY << endl;
			heur += (heurY[(positions[i][1] / 11)] * heurX[(positions[i][0] / 11)]);
		}
		n.heuristicValue = heur;
		np.push_back(n);
	}
	sort(np.begin(), np.end(), np_sorter);
}

void printTopTrees(vector<vector<int>> positions, vector<vector<int>> velocities, vector<notablePoint>& nps) {
	//Magic number 100
	for (int i = 0; i < 100; i++) {
		cout << "Number printed: " << i << endl;
		printFrame(positions, velocities, nps[i]);
	}
}
void printFrame(vector<vector<int>>& positions, vector<vector<int>>& velocities, notablePoint np) {
	cout << "Seconds after 0: " << np.frameNum << endl;
	int maxX = 101, maxY = 103;
	string s = "";
	char arr[101][103];
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 103; j++) {
			arr[i][j] = ' ';
		}
	}
	int tX, tY;
	for (size_t i = 0; i < positions.size(); i++) {
		tX = (positions[i][0] + velocities[i][0] * np.frameNum) % maxX;
		tY = (positions[i][1] + velocities[i][1] * np.frameNum) % maxY;
		if (tX < 0) { tX += maxX; }
		if (tY < 0) { tY += maxY; }
		arr[tX][tY] = '*';
	}
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 103; j++) {
			s += arr[i][j];
		}
		s += '\n';
	}
	cout << s << endl;
	cin.get();
}
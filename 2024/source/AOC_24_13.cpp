//Solution to Advent of Code's 2024 day 13 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(vector<vector<double>>& xd, vector<vector<double>>& yd, vector<vector<double>>& pz, string path);

void part_1_calculation(vector<vector<double>>&, vector<vector<double>>&, vector<vector<double>>&);
void part_2_calculation(vector<vector<double>>&, vector<vector<double>>&, vector<vector<double>>&);
int solve(vector<double>& x, vector<double>& y, vector<double>& p);
long long solve2(vector<double>& x, vector<double>& y, vector<double> p);
int main() {
	vector<vector<double>> xDelta, yDelta, prizes;
	cout << "Example Data" << endl;
	rff(xDelta, yDelta, prizes, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_13.txt");
	part_1_calculation(xDelta, yDelta, prizes);
	part_2_calculation(xDelta, yDelta, prizes);
	cout << "Challenge Data" << endl;
	rff(xDelta, yDelta, prizes, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_13.txt");
	part_1_calculation(xDelta, yDelta, prizes);
	part_2_calculation(xDelta, yDelta, prizes);

}

void rff(vector<vector<double>>& xd, vector<vector<double>>& yd, vector<vector<double>>& pz, string path) {
	xd.clear();
	yd.clear();
	pz.clear();
	ifstream f(path);
	string l;
	int counter = 0;
	vector<double> xV = {}, yV = {}, pV = {};

	while (getline(f, l)) {
		int nStart = 0, ind = 0, length = 0;

		while (ind < l.size()) {
			if (l[ind] == '+') {
				ind++;
				nStart = ind;
				while (l[ind] <= '9' && l[ind] >= '0') {
					length++;
					ind++;
				}
				xV.push_back(stod(l.substr(nStart, length)));
				while (l[ind] != '+') { ind++; }
				ind++;
				nStart = ind;
				length = 0;
				while (ind < l.size() && l[ind] <= '9' && l[ind] >= '0') {
					length++;
					ind++;
				}
				yV.push_back(stod(l.substr(nStart, length)));
			}
			else if (l[ind] == '=') {
				ind++;
				nStart = ind;
				while (l[ind] <= '9' && l[ind] >= '0') {
					length++;
					ind++;
				}
				pV.push_back(stod(l.substr(nStart, length)));
				while (l[ind] != '=') { ind++; }
				ind++;
				nStart = ind;
				length = 0;
				while (ind < l.size() && l[ind] <= '9' && l[ind] >= '0') {
					length++;
					ind++;
				}
				pV.push_back(stod(l.substr(nStart, length)));

				xd.push_back(xV);
				yd.push_back(yV);
				pz.push_back(pV);

				yV.clear();
				xV.clear();
				pV.clear();
			}
			ind++;
		}

	}
	f.close();
}

void part_1_calculation(vector<vector<double>>& xd, vector<vector<double>>& yd, vector<vector<double>>& pz) {
	int result = 0;
	for (size_t i = 0; i < xd.size(); i++) {
		result += solve(xd[i], yd[i], pz[i]);
	}
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<vector<double>>& xd, vector<vector<double>>& yd, vector<vector<double>>& pz) {
	long long result = 0;
	for (size_t i = 0; i < xd.size(); i++) {
		result += solve2(xd[i], yd[i], pz[i]);
	}
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

int solve(vector<double>& x, vector<double>& y, vector<double>& p) {
	double disc = (x[0] * y[1] - x[1] * y[0]);
	double butA = (y[1] * p[0] - x[1] * p[1]);
	double butB = (x[0] * p[1] - y[0] * p[0]);

	//Early return if button a or b need more than 100 button presses
	if (butA / disc > 100 || butB / disc > 100 ) { return 0; }
	//Detect if there is a remainder after the division. Button presses are discrete, but math is... continuous?
	long tA = butA - (double)((long) (butA / disc)) * disc;
	long tB = butB - (double)((long) (butB / disc)) * disc;
	//If there is a remainder return 0
	if (tA || tB) { return 0; }

	//Adjust return for token prices.
	return butA / disc * 3 + butB / disc;
}

long long solve2(vector<double>& x, vector<double>& y, vector<double> p) {
	long long p0 = p[0] + 10000000000000;
	long long p1 = p[1] + 10000000000000;

	long long disc = (x[0] * y[1] - x[1] * y[0]);
	long long butA = (y[1] * p0 - x[1] * p1);
	long long butB = (x[0] * p1 - y[0] * p0);

	long long tA = butA - (long double)((long long)(butA / disc)) * (long double) disc;
	long long tB = butB - (long double)((long long)(butB / disc)) * (long double) disc;
	//cout << "tA: " << tA << " tB: " << tB << endl;
	if (tA || tB) { return 0; }

	//cout << butA << " " << butB << endl;
	//If there is a remainder return 0
	//if (tA || tB) { return 0; }

	//Adjust return for token prices.
	return butA / disc * 3 + butB / disc;
}
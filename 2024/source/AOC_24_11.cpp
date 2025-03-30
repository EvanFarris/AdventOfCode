//Solution to Advent of Code's 2024 day 2 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

using namespace std;

void rff(vector<long long>&, string);

void part_1_calculation(vector<long long >);
void part_2_calculation(vector<long long>);
long long getBlinks(vector<long long>& stones, size_t numBlinks);
void printStones(vector<long long>& stones);

int main() {
	vector<long long> stones;
	cout << "Example Data" << endl;
	rff(stones, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_11.txt");
	part_1_calculation(stones);
	part_2_calculation(stones);
	cout << "Challenge Data" << endl;
	rff(stones, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_11.txt");
	part_1_calculation(stones);
	part_2_calculation(stones);

}

void rff(vector<long long>& stones, string path) {
	stones.clear();
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		int nStart = 0, ind = 0, length = 0;
		while (ind != l.size()) {
			if (l[ind] == ' ') {
				if (length > 0) {
					stones.push_back(stoll(l.substr(nStart, length)));
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
			stones.push_back(stoll(l.substr(nStart, length)));
		}
	}
	f.close();
}
 
void part_1_calculation(vector<long long> stones) {
	long long result = 0;
	result = getBlinks(stones, 25);
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(vector<long long> stones) {
	long long result = 0;
	result = getBlinks(stones, 75);

	cout << "The answer to part 2 of the challenge is: " << result << endl;
}

//Memoize the value of the # of stones with the same value
//Can't maintain the list as a growing vector with individual rocks, as the time to process a blink increases exponentially.
long long getBlinks(vector<long long>& stones, size_t numBlinks) {
	string temp;
	map <long long, long long> m, mTemp;
	vector<long long> vTemp;
	auto itr = m.end();
	//Add stones to initial map
	for (size_t i = 0; i < stones.size(); i++) {
		m[stones[i]] += 1;
	}
	//Blink numBlinks times
	for (size_t b = 0; b < numBlinks; b++) {
		mTemp.clear();
		itr = m.begin();

		while (itr != m.end()) {
			if (itr->first == 0) {
				mTemp[1] += itr->second;
			}
			else if (to_string(itr->first).size() % 2 == 0) {
				long long ltemp = pow(10, ((long long)(log10(itr->first) + 1) / 2));
				mTemp[itr->first / ltemp] += itr->second;
				mTemp[itr->first % ltemp] += itr->second;
			}
			else {
				mTemp[itr->first * 2024] = itr->second;
			}
			itr++;
		}
		m = mTemp;
	}
	//Calculate #stones
	itr = m.begin();
	long long res = 0;
	while (itr != m.end()) {
		res += itr->second;
		itr++;
	}

	return res;
}

void printStones(vector<long long>& stones) {
	for (size_t s = 0; s < stones.size(); s++) {
		cout << stones[s] << " ";
	}
	cout << endl;
}
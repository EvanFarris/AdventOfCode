//Solution to Advent of Code's 2024 day 9 challenge

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void rff(string&, string);

void part_1_calculation(string&);
void part_2_calculation(string&);

void moveVec(vector<int>& disk);
vector<int> buildVec(string inp);
vector<int> buildVec(string inp, vector<struct pt>&);
size_t calcChecksum(vector<int>& disk);
void moveVec(vector<int>& disk, vector<struct pt> pts);

struct pt {
	int ind;
	int size;
};

int main() {
	string inp;
	cout << "Example Data" << endl;
	rff(inp, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_example_9.txt");
	part_1_calculation(inp);
	part_2_calculation(inp);
	cout << "Challenge Data" << endl;
	rff(inp, "C:\\Users\\Evan\\Desktop\\AdventOfCode\\2024\\data\\aoc_input_9.txt");
	part_1_calculation(inp);
	part_2_calculation(inp);

}

void rff(string & inp, string path) {
	ifstream f(path);
	string l;

	while (getline(f, l)) {
		inp = l;
	}

	f.close();
}

void part_1_calculation(string& inp) {
	size_t result = 0;

	vector<int> disk = buildVec(inp);
	moveVec(disk);
	result = calcChecksum(disk);
	cout << "The answer to part 1 of the challenge is: " << result << endl;
}

void part_2_calculation(string& inp) {
	size_t result = 0;
	vector<struct pt> pts;
	vector<int> disk = buildVec(inp, pts);
	moveVec(disk, pts);
	result = calcChecksum(disk);
	cout << "The answer to part 2 of the challenge is: " << result << endl;
}


vector<int> buildVec(string inp) {
	vector<int> result;
	int id = 0, amt, psh;
	for (size_t i = 0; i < inp.size(); i++) {
		amt = inp[i] - '0';
		if (i % 2) {
			psh = -1;
		}
		else {
			psh = id;
			id++;
		}
		for (size_t j = 0; j < amt; j++) {
			result.push_back(psh);
		}
	}

	return result;
}

vector<int> buildVec(string inp, vector<struct pt>& freeList) {
	freeList.clear();
	vector<int> result;
	pt p;
	int id = 0, amt, psh, ind = 0;
	for (size_t i = 0; i < inp.size(); i++) {
		amt = inp[i] - '0';
		if (i % 2) {
			psh = -1;
			p.ind = ind;
			p.size = amt;
			freeList.push_back(p);
		}
		else {
			psh = id;
			id++;
		}
		for (size_t j = 0; j < amt; j++) {
			result.push_back(psh);
			ind++;
		}
	}

	return result;
}

void moveVec(vector<int>& disk) {
	size_t left = 0, right = disk.size() - 1;
	while (left < right) {
		while (disk[left] != -1) {
			left++;
		}
		while (disk[right] == -1) {
			right--;
		}
		if (left < right) {
			disk[left] = disk[right];
			disk[right] = -1;
		}
	}
}

void moveVec(vector<int>& disk, vector<struct pt> pts) {
	size_t left = 0, right = disk.size() - 1;
	int cur, len;
	while (right > 0) {
		while (disk[right] == -1) {
			right--;
		}
		cur = disk[right];
		len = 1;
		while (right > 0 && disk[right - 1] == cur) {
			len++;
			right--;
		}

		for (size_t i = 0; i < pts.size(); i++) {
			if (pts[i].ind > right) { break; }
			if (pts[i].size >= len) {
				for (size_t j = 0; j < len; j++) {
					disk[pts[i].ind + j] = disk[right + j];
					disk[right + j] = -1;
				}
				if (pts[i].size > len) {
					pts[i].size -= len;
					pts[i].ind += len;
				}
				else {
					pts.erase(pts.begin() + i);
				}
				break;
			} 
		}
		if (right) {
			right--;
		}
	}
}

size_t calcChecksum(vector<int>& disk) {
	size_t total = 0;
	for(size_t ind = 0; ind < disk.size(); ind++) {
		if (disk[ind] != -1) {
			total += ind * disk[ind];
		}
	}
	return total;
}
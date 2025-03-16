// AOC_24_1.cpp : Solution for Advent of Code 2024, Day 1
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

void rff(vector<int>&, vector<int>&);
int pop(vector<int>&);
void build_min_heap(vector<int>&);
void min_heapify(vector<int>&, int);
void build_map(vector<int>&);
void part_1_calculation(vector<int>, vector<int>);
void part_2_calculation(vector<int>, vector<int>);

//Global map used for part 2 of the challenge
map<int, int> m;

int main()
{
    //Read in input data
    vector<int> llist = {}, rlist = {};
    rff(llist, rlist);
    //Build min-heaps of the two lists
    build_min_heap(llist);
    build_min_heap(rlist);

    part_1_calculation(llist, rlist);
    part_2_calculation(llist, rlist);
    return 0;
}

//Read challenge's input data from file
void rff(vector<int>& v1, vector<int>& v2) {
    ifstream f("C:\\Users\\Evan\\Downloads\\aoc_input_1.txt");
    string l;
    while (getline(f, l)) {
        int ind = 0;
        while (l[ind] != ' ') { ind++; }
        int t1 = stoi(l.substr(0, ind));
        v1.push_back(t1);
        while (l[ind] == ' ') { ind++; }
        int t2 = stoi(l.substr(ind, l.size() - ind));
        v2.push_back(t2);
        
    }
    f.close();
}

//Pop the top element off a heap and return the value to the calling function.
int pop(vector<int>& v) {
    int top = v[0];
    v[0] = v[v.size() - 1];
    v.pop_back();
    min_heapify(v, 0);
    return top;
}

//Builds a minheap from the bottom up
void build_min_heap(vector<int>& v) {
    for (int i = v.size() / 2 - 1; i >= 0; i--) {
        min_heapify(v, i);
    }
} 

//Maintains the min-heap property on the array
void min_heapify(vector<int>& v, int ind) {
    int l = 2 * ind + 1;
    int r = 2 * ind + 2;
    int smallest;
    if (l < v.size() && v[l] < v[ind]) {
        smallest = l;
    }
    else { smallest = ind; }
    if (r < v.size() && v[r] < v[smallest]) {
        smallest = r;
    }
    if (smallest != ind) {
        int temp = v[ind];
        v[ind] = v[smallest];
        v[smallest] = temp;
        min_heapify(v, smallest);
    }
}

//Counts the number of occurences of each number that appears in the right list
void build_map(vector<int>& v) {
    for (auto i = 0; i < v.size(); i++) {
        m[v[i]]++;
    }
}

void part_1_calculation(vector<int> llist, vector<int> rlist) {
    //Get distances between tops of min heaps and adds it to the sum
    int sum = 0;
    while (llist.size()) {
        sum += abs(pop(llist) - pop(rlist));
    }
    //cout sum of the distances
    cout << "The answer to part 1 of the challenge is: " << sum << endl;
}

void part_2_calculation(vector<int> llist, vector<int> rlist) {
    //Build the hash table of the right list
    build_map(rlist);
    //Calculate the similarity score of the left list, with the map of the right list
    long res = 0;
    for (auto i = 0; i < llist.size(); i++) {
        res += llist[i] * m[llist[i]];
    }
    cout << "The answer to part 2 of the challenge is: " << res << endl;
}
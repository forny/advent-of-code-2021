#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "advent.h"

using namespace std;

void part1(const vector<int32_t>& iDepths) {
	int32_t last = iDepths[0];
	int32_t nrIncreasing = 0;
	for (int32_t x = 1; x < iDepths.size(); ++x) {
		if (iDepths[x] > last) {
			++nrIncreasing;
		}
		last = iDepths[x];
	}
	cout << nrIncreasing << endl;
}

void part2(const vector<int32_t>& iDepths) {
	int32_t last = iDepths[0] + iDepths[1] + iDepths[2];
	int32_t nrIncreasing = 0;
	for (int32_t x = 3; x < iDepths.size(); ++x) {
		int32_t sum3 = last + iDepths[x] - iDepths[x - 3];
		if (sum3 > last) {
			++nrIncreasing;
		}
		last = sum3;
	}
	cout << nrIncreasing << endl;
}

int main()
{
	const vector<string> lines = readInputFile("day1_input.txt");
	std::vector<int> depths;
	for (const string& line : lines) {
		depths.push_back(stoi(line));
	}

	cout << "Part 1:" << endl;
	part1(depths);
	cout << "Part 2:" << endl;
	part2(depths);
	return 0;
}

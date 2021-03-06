#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "advent.h"

using namespace std;

vector<int32_t> countBits(const vector<string>& iLines) {
	const int32_t nrBits = iLines[0].size();
	std::vector<int32_t> counters(nrBits, 0);
	for (const auto& line : iLines) {
		for (int32_t i = 0; i < nrBits; ++i) {
			if (line[i] == '0') {
				--counters[i];
			}
			else {
				++counters[i];
			}
		}
	}
	return counters;
}

void part1(const vector<string>& iLines) {
	const int32_t nrBits = iLines[0].size();
	vector<int32_t> counters = countBits(iLines);

	int32_t gamma = 0;
	for (int32_t i = 0; i < nrBits; ++i) {
		if (counters[i] > 0) {
			gamma += (1 << (nrBits - i - 1));
		}
	}
	int epsilon = (~gamma) & ((1 << nrBits) - 1);
	cout << gamma * epsilon << endl;
}

int bitCriteriaFilter(const vector<string>& iLines, const function<bool(int32_t, char)>& iBitFilter) {
	vector<string> linesKept = iLines;
	const int nrBits = iLines[0].size();

	for (int32_t bit = 0; bit < nrBits && linesKept.size() > 1; ++bit) {
		vector<int32_t> counters = countBits(linesKept);
		vector<string> linesToKeep;
		for (const string& line : linesKept) {
			if (iBitFilter(counters[bit], line[bit])) {
				linesToKeep.push_back(line);
			}
		}
		linesKept = linesToKeep;
	}
	assert(linesKept.size() == 1);
	int32_t rating = stoi(linesKept[0], 0, 2);
	return rating;
}

void part2(const vector<string>& iLines) {
	int oxygenRating = bitCriteriaFilter(iLines, [](int32_t counter, char bitValue) -> bool {
		return counter >= 0 ? bitValue == '1' : bitValue == '0';
	});

	int co2Rating = bitCriteriaFilter(iLines, [](int32_t counter, char bitValue) -> bool {
		return counter < 0 ? bitValue == '1' : bitValue == '0';
	});

	cout << oxygenRating * co2Rating << endl;
}

int main() {
	const vector<string> lines = readInputFile("day3_input.txt");
	cout << "Part 1:" << endl;
	part1(lines);
	cout << "Part 2:" << endl;
	part2(lines);
	return 0;
}


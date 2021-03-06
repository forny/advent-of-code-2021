#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "advent.h"

using namespace std;

vector<int> parse(const vector<string>& iLines) {
	string line0 = iLines[0];
	vector<string> nrs_str;
	split(line0, nrs_str, ",");
	vector<int> nrs;
	for (const string& nr_str : nrs_str) {
		nrs.push_back(stoi(nr_str));
	}
	return nrs;
}

void do_the_fishy_thing(const int iDays, const vector<int>& iNrs) {
	constexpr int spawn_days = 7;
	constexpr int newborn_days = 2;
	constexpr int nr_days = spawn_days + newborn_days;

	vector<int64_t> d(nr_days, 0);
	for (const int nr : iNrs) {
		++d[nr];
	}
	
	int day0_index = 0;
	for (int day = 0; day < iDays; ++day) {
		// Day 0 will automatically become newly spawned fishes
		// Move/add same number to day 7 so they can keep spawning 4ever! <3
		d[(day0_index + spawn_days) % nr_days] += d[day0_index];
		day0_index = (day0_index + 1) % nr_days;
	}

	int64_t sum = 0;
	for (int i = 0; i < nr_days; ++i) {
		sum += d[i];
	}
	cout << sum << endl;
}

void part1(const vector<int>& iNrs) {
	do_the_fishy_thing(80, iNrs);
}

void part2(const vector<int>& iNrs) {
	do_the_fishy_thing(256, iNrs);
}

int main() {
	const vector<string> lines_str = readInputFile("day6_input.txt");
	vector<int> nrs = parse(lines_str);

	cout << "Part 1:" << endl;
	part1(nrs);
	cout << "Part 2:" << endl;
	part2(nrs);
	return 0;
}


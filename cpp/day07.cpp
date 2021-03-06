#include <algorithm>
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

void fuel_calc(const vector<int>& iNrs, const function<int(int,int)>& cost_fun) {
	int max_value = *max_element(iNrs.begin(), iNrs.end());
	int min_fuel = numeric_limits<int>::max();
	for (int x = 0; x <= max_value; ++x) {
		int fuel = 0;
		for (int nr : iNrs) {
			fuel += cost_fun(nr, x);
		}
		if (fuel < min_fuel) {
			min_fuel = fuel;
		}
	}
	cout << min_fuel << endl;
}

void part1(const vector<int>& iNrs) {
	fuel_calc(iNrs, [](int start, int end) -> int { 
		return abs(end - start); 
	});
}

void part2(const vector<int>& iNrs) {
	fuel_calc(iNrs, [](int start, int end) -> int { 
		int steps = abs(end - start);
		return  steps * (1 + steps) / 2;
	});
}

int main() {
	const vector<string> lines_str = readInputFile("day7_input.txt");
	vector<int> nrs = parse(lines_str);

	cout << "Part 1:" << endl;
	part1(nrs);
	cout << "Part 2:" << endl;
	part2(nrs);
	return 0;
}


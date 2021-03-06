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
typedef vector<string> tParsed;

bool is_low_point(const tParsed& iItems, const int x, const int y) {
	const int value = iItems[y][x];
	bool is_min = true;
	if (x > 0 && iItems[y][x - 1] <= value) is_min = false;
	if (y > 0 && iItems[y - 1][x] <= value) is_min = false;
	if (x < iItems[0].size() - 1 && iItems[y][x + 1] <= value) is_min = false;
	if (y < iItems.size() - 1 && iItems[y + 1][x] <= value) is_min = false;
	return is_min;
}

void part1(const tParsed& iItems) {
	int sum = 0;
	for (int y = 0; y < iItems.size(); ++y) {
		for (int x = 0; x < iItems[0].size(); ++x) {
			if (is_low_point(iItems, x, y)) {
				sum += iItems[y][x] - '0' + 1;
			}
		}
	}
	cout << sum << endl;
}


int basin_search(int x, int y, char from_value, tParsed& searched) {
	int xs = searched[0].size();
	int ys = searched.size();
	if (x < 0 || x >= xs || y < 0 || y >= ys) {
		return 0;
	}
	char value = searched[y][x];
	if (value == 'x' || value == '9' || value <= from_value) {
		return 0;
	}
	searched[y][x] = 'x';
	
	int sum = 1;
	sum += basin_search(x - 1, y, value, searched);
	sum += basin_search(x, y - 1, value, searched);
	sum += basin_search(x + 1, y, value, searched);
	sum += basin_search(x, y + 1, value, searched);
	return sum;
}

void part2(const tParsed& iItems) {
	vector<int> sizes;
	for (int y = 0; y < iItems.size(); ++y) {
		for (int x = 0; x < iItems[0].size(); ++x) {
			if (is_low_point(iItems, x, y)) {
				tParsed searched = iItems;
				int basin_size = basin_search(x, y, ' ', searched);
				sizes.push_back(basin_size);
			}
		}
	}

	sort(sizes.begin(), sizes.end(), greater<int>());
	int64_t result = sizes[0] * sizes[1] * sizes[2];
	cout << result << endl;
}

int main() {
	const tParsed parsed = readInputFile("day9_input.txt");

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}


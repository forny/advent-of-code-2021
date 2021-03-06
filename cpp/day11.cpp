#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "advent.h"

using namespace std;

typedef vector<vector<int>> tParsed;

tParsed parse(const vector<string>& iLines) {
	tParsed parsed;
	for (const string& line : iLines) {
		vector<int> v;
		for (char c : line) {
			v.push_back(c - '0');
		}
		parsed.push_back(v);
	}
	return parsed;
}

int simulate(tParsed& m) {
	int flashes = 0;
	vector<pair<int, int>> flash;
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			if (++m[y][x] == 10) {
				flash.push_back(make_pair(x, y));
			}
		}
	}
	while (!flash.empty()) {
		++flashes;
		auto f = flash.back();
		flash.pop_back();
		int x = f.first;
		int y = f.second;
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;
				int newx = x + dx;
				int newy = y + dy;
				if (newx >= 0 && newx < 10 && newy >= 0 && newy < 10) {
					if (++m[newy][newx] == 10) {
						flash.push_back(make_pair(newx, newy));
					}
				}
			}
		}
	}
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			if (m[y][x] >= 10) {
				m[y][x] = 0;
			}
		}
	}
	return flashes;
}

void part1(const tParsed& iItems) {
	tParsed m = iItems;
	int flashes = 0;
	for (int steps = 0; steps < 100; ++steps) {
		flashes += simulate(m);
	}
	cout << flashes << endl;
}


void part2(const tParsed& iItems) {
	tParsed m = iItems;
	int steps = 1;
	int flashes = 0;
	for (; flashes != 100; ++steps) {
		flashes = simulate(m);
		if (flashes == 100) {
			break;
		}
	}
	cout << steps << endl;
}

int main() {
	const vector<string> lines = readInputFile("day11_input.txt");
	const tParsed parsed = parse(lines);

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

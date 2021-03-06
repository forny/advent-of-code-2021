#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "advent.h"

using namespace std;

typedef set<pair<int, int>> tPoints;
typedef vector<pair<int, int>> tFolds;
typedef pair<tPoints, tFolds> tParsed;

tParsed parse(const vector<string>& iLines) {
	tPoints dots;
	tFolds folds;
	bool first_part = true;
	for (const string& line : iLines) {
		if (line.empty()) {
			first_part = false;
			continue;
		}
		if (first_part) {
			vector<string> line_str;
			split(line, line_str, ",");
			int x = stoi(line_str[0]);
			int y = stoi(line_str[1]);
			dots.insert(make_pair(x, y));
		}
		else {
			vector<string> line_str;
			split(line, line_str, "=");
			int nr = stoi(line_str[1]);
			if (line_str[0].back() == 'x') folds.push_back(make_pair(nr, -1));
			else folds.push_back(make_pair(-1, nr));
		}
	}
	return make_pair(dots, folds);
}

pair<int, int> fold_dot(const pair<int, int>& iDot, const pair<int,int>& iFold) {
	int x_fold = iFold.first;
	int y_fold = iFold.second;
	if (x_fold != -1) {
		if (iDot.first >= x_fold) return make_pair(2 * x_fold - iDot.first, iDot.second);
		else return iDot;
	}
	else {
		assert(y_fold != -1);
		if (iDot.second >= y_fold) return make_pair(iDot.first, 2 * y_fold - iDot.second);
		else return iDot;
	}
}

void part1(const tParsed& iItems) {
	const tPoints& old_dots = iItems.first;
	tPoints new_dots;
	const auto& first_fold = iItems.second[0];
	for (const auto& dot : old_dots) {
		new_dots.insert(fold_dot(dot, first_fold));
	}
	cout << new_dots.size() << endl;
}

void part2(const tParsed& iItems) {
	tPoints old_dots = iItems.first;
	for (const auto& fold : iItems.second) {
		tPoints new_dots;
		for (const auto& dot : old_dots) {
			new_dots.insert(fold_dot(dot, fold));
		}
		old_dots = new_dots;
	}

	int x_max = -1, y_max = -1;
	for (const auto& dot : old_dots) {
		if (dot.first > x_max) x_max = dot.first;
		if (dot.second > y_max) y_max = dot.second;
	}
	for (int y = 0; y <= y_max; ++y) {
		for (int x = 0; x <= x_max; ++x) {
			if (old_dots.find(make_pair(x, y)) != old_dots.end()) cout << "#";
			else cout << ".";
		}
		cout << endl;
	}
}


int main() {
	const vector<string> lines = readInputFile("day13_input.txt");
	const tParsed parsed = parse(lines);

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

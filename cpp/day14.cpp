#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "advent.h"

using namespace std;

typedef pair<string, vector<string>> tParsed;

tParsed parse(const vector<string>& iLines) {
	cout << iLines[0] << endl;
	string poly;
	vector<string> rules;
	bool first_part = true;
	for (const string& line : iLines) {
		if (line.empty()) {
			first_part = false;
			continue;
		}
		if (first_part) poly = line;
		else rules.push_back({ line[0], line[1], line[6] });
	}
	return make_pair(poly, rules);
}

void process(const tParsed& iItems, const int iSteps) {
	const string& poly_template = iItems.first;
	const vector<string>& rules = iItems.second;

	map<string, int64_t> m_pair2count;
	for (int i = 0; i < poly_template.size() - 1; ++i) {
		++m_pair2count[{poly_template[i], poly_template[i + 1]}];
	}

	map<string, int64_t> m_pair2count_new = m_pair2count;
	for (int step = 0; step < iSteps; ++step) {
		for (const auto& it : m_pair2count) {
			for (const auto& rule : rules) {
				if (rule[0] == it.first[0] && rule[1] == it.first[1]) {
					m_pair2count_new[it.first] -= it.second;
					m_pair2count_new[{rule[0], rule[2]}] += it.second;
					m_pair2count_new[{rule[2], rule[1]}] += it.second;
					break;
				}
			}
		}
		m_pair2count = m_pair2count_new;
	}
	map<char, int64_t> count;
	for (const auto& it : m_pair2count) {
		count[it.first[0]] += it.second;
		count[it.first[1]] += it.second;
	}
	++count[poly_template[0]];
	++count[poly_template.back()];

	int64_t cmax = -1;
	int64_t cmin = numeric_limits<int64_t>::max();
	for (auto& it : count) {
		if (it.second > cmax) cmax = it.second;
		if (it.second < cmin) cmin = it.second;
	}
	cout << cmax / 2 - cmin / 2 << endl;
}

void part1(const tParsed& iItems) {
	process(iItems, 10);
}

void part2(const tParsed& iItems) {
	process(iItems, 40);
}

int main() {
	const vector<string> lines = readInputFile("day14_input.txt");
	const tParsed parsed = parse(lines);

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

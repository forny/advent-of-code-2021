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

map<char, char> matching{ { '(',')' },{ '[',']' },{ '{','}' },{ '<','>' }, };

stack<char> get_stack_at_error(const string iLine, char& oFirstInvalid) {
	stack<char> s;
	for (const char c : iLine) {
		if (c == '{' || c == '[' || c == '(' || c == '<') {
			s.push(c);
		}
		else {
			char c1 = s.top();
			if (matching[c1] != c) {
				oFirstInvalid = c;
				break;
			}
			s.pop();
		}
	}
	return s;
}

void part1(const vector<string>& iItems) {
	map<char, int> score_p1{ { ')',3 },{ ']',57 },{ '}',1197 },{ '>',25137 } };
	int sum = 0;
	for (const string& line : iItems) {
		char first_invalid = 'x';
		stack<char> s = get_stack_at_error(line, first_invalid);
		if (first_invalid != 'x') {
			sum += score_p1[first_invalid];
		}
	}
	cout << sum << endl;
}


void part2(const vector<string>& iItems) {
	map<char, int> score_p2{ { ')',1 },{ ']',2 },{ '}',3 },{ '>',4 } };
	vector<int64_t> scores;
	for (const string& line : iItems) {
		char first_invalid = 'x';
		stack<char> s = get_stack_at_error(line, first_invalid);
		if (first_invalid == 'x') {
			int64_t points = 0;
			while (!s.empty()) {
				char c1 = s.top();
				s.pop();
				points = points * 5 + score_p2[matching[c1]];
			}
			scores.push_back(points);
		}
	}
	sort(scores.begin(), scores.end());
	cout << scores[scores.size() / 2] << endl;
}

int main() {
	const vector<string> parsed = readInputFile("day10_input.txt");

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

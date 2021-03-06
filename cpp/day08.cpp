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

vector<vector<vector<string>>> parse(const vector<string>& iLines) {
	vector<vector<vector<string>>> items;

	for (const string& line : iLines) {
		vector<string> line_str;
		split(line, line_str, "|");
		
		vector<string> parts_str;
		split(line_str[0], parts_str, " ");
		parts_str.erase(parts_str.end() - 1);
		
		vector<string> results_str;
		split(line_str[1], results_str, " ");
		results_str.erase(results_str.begin());
		
		for (auto& s : parts_str) {
			sort(s.begin(), s.end());
		}
		for (auto& s : results_str) {
			sort(s.begin(), s.end());
		}
		vector<vector<string>> x;
		x.push_back(parts_str);
		x.push_back(results_str);
		items.push_back(x);
	}
	return items;
}

void part1(const vector<vector<vector<string>>>& iItems) {
	int sum = 0;
	for (const vector<vector<string>>& item : iItems) {
		for (const auto& s : item[1]) {
			if (s.size() == 2 || s.size() == 3 || s.size() == 4 || s.size() == 7) {
				++sum;
			}
		}
	}
	cout << sum << endl;
}

void part2(const vector<vector<vector<string>>>& iItems) {
	int sum = 0;
	map<string, int> map_str2nr{ {"abcefg",0}, {"cf", 1}, {"acdeg",2}, {"acdfg",3}, {"bcdf",4}, {"abdfg", 5}, {"abdefg", 6}, {"acf", 7}, {"abcdefg",8}, {"abcdfg",9} };
	map<int, char> map_count2char{ {6,'b'}, {4,'e'}, {9,'f'} };
	map<char, char> mapping;
	for (const vector<vector<string>>& item : iItems) {
		map<char, int> map_char2count; 
		string s2nr1, s4nr4;
		for (const auto& s : item[0]) {
			if (s.size() == 2) s2nr1 = s;
			else if (s.size() == 4) s4nr4 = s;
			for (char c : "abcdefg") {
				if (s.find(c) != string::npos) map_char2count[c] += 1;
			}
		}
		for (const auto it : map_char2count) {
			int nr = it.second;
			if (nr == 8) {
				bool in_nr1 = s2nr1.find(it.first) != string::npos;
				mapping[it.first] = in_nr1 ? 'c' : 'a';
			}
			else if (nr == 7) {
				bool in_nr4 = s4nr4.find(it.first) != string::npos;
				mapping[it.first] = in_nr4 ? 'd' : 'g';
			}
			else {
				mapping[it.first] = map_count2char[it.second];
			}
		}

		int nr = 0;
		for (const auto& s : item[1]) {
			string translated = s;
			for (auto& c : translated) {
				c = mapping[c];
			}
			sort(translated.begin(), translated.end());
			int val = map_str2nr[translated];
			nr = 10 * nr + val;
		}
		sum += nr;
	}

	cout << sum << endl;
}

int main() {
	const vector<string> lines_str = readInputFile("day8_input.txt");
	const vector<vector<vector<string>>> nrs = parse(lines_str);

	cout << "Part 1:" << endl;
	part1(nrs);
	cout << "Part 2:" << endl;
	part2(nrs);
	return 0;
}


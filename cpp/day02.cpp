#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "advent.h"

using namespace std;

void part1(const vector<string>& iLines)
{
	int64_t pos = 0;
	int64_t depth = 0;
	for (const string& line : iLines) {
		vector<string> parts;
		split(line, parts, " ");
		const string& command = parts[0];
		const int32_t nr = stoi(parts[1]);
		if (command == "forward") {
			pos += nr;
		}
		else if (command == "down") {
			depth += nr;
		}
		else if (command == "up") {
			depth -= nr;
		}
	}
	cout << pos * depth << endl;
}

void part2(const vector<string>& iLines)
{
	int64_t aim = 0;
	int64_t pos = 0;
	int64_t depth = 0;
	for (int32_t i = 0; i < iLines.size(); ++i) {
		std::vector<std::string> cmd;
		split(iLines[i], cmd, " ");
		int nr = stoi(cmd[1]);
		if (cmd[0] == "forward") {
			pos += nr;
			depth += nr * aim;
		}
		if (cmd[0] == "down") {
			aim += nr;
		}
		if (cmd[0] == "up") {
			aim -= nr;
		}
	}
	cout << pos * depth << endl;
}

int main()
{
	const vector<string> lines = readInputFile("day2_input.txt");
	cout << "Part 1:" << endl;
	part1(lines);
	cout << "Part 2:" << endl;
	part2(lines);
	return 0;
}

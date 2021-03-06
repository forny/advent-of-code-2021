#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "advent.h"

using namespace std;

struct Point {
	int x;
	int y;
	bool operator<(const Point& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
};

struct Line {
	Point p1;
	Point p2;
}; 


vector<Line> parse(const vector<string>& iLines) {
	vector<Line> lines;
	for (const string& line : iLines) {
		vector<string> parts;
		split(line, parts, " ");
		vector<string> nrs;
		split(parts[0], nrs, ",");
		int x1 = stoi(nrs[0]);
		int y1 = stoi(nrs[1]);
		Point p1{ stoi(nrs[0]) , stoi(nrs[1]) };
		nrs.clear();
		split(parts[2], nrs, ",");
		int x2 = stoi(nrs[0]);
		int y2 = stoi(nrs[1]);
		Point p2{ stoi(nrs[0]) , stoi(nrs[1]) };
		Line line{ p1, p2 };
		lines.push_back(line);
	}
	return lines;
}

void drawLine(map<Point, int>& ioOcean, const Line& iLine) {
	const int x1 = iLine.p1.x;
	const int y1 = iLine.p1.y;
	const int x2 = iLine.p2.x;
	const int y2 = iLine.p2.y;
	int dx = 0, dy = 0;
	if (x2 > x1) {
		dx = 1;
	}
	else if (x2 < x1) {
		dx = -1;
	}
	if (y2 > y1) {
		dy = 1;
	}
	else if (y2 < y1) {
		dy = -1;
	}
	int x = x1, y = y1;
	for (; x != x2 || y != y2; x += dx, y += dy) {
		ioOcean[Point{ x, y }] += 1;
	}
	ioOcean[Point{ x, y }] += 1;
}

int getOverlaps(const map<Point, int>& iOcean) {
	int sum = 0;
	for (const auto it : iOcean) {
		if (it.second >= 2) {
			++sum;
		}
	}
	return sum;
}

void part1(const vector<Line>& iLines) {
	map<Point, int> ocean;
	for (const Line& line : iLines) {
		if (line.p1.x == line.p2.x || line.p1.y == line.p2.y) {
			drawLine(ocean, line);
		}

	}
	int overlaps = getOverlaps(ocean);
	cout << overlaps << endl;
}

void part2(const vector<Line>& iLines) {
	map<Point, int> ocean;
	for (const Line& line : iLines) {
		drawLine(ocean, line);
	}
	int overlaps = getOverlaps(ocean);
	cout << overlaps << endl;
}

int main() {
	const vector<string> lines_str = readInputFile("day5_input.txt");
	vector<Line> lines = parse(lines_str);

	cout << "Part 1:" << endl;
	part1(lines);
	cout << "Part 2:" << endl;
	part2(lines);
	return 0;
}


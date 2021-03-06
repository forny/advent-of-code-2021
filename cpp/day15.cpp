#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
		for (char c : line) v.push_back(c - '0');
		parsed.push_back(v);
	}
	return parsed;
}

typedef pair<int, int> tPair;
typedef pair<int, tPair> tCostPair;

void shortest_path(const vector<vector<int>>& iRiskMap) {
	constexpr tPair dirs[4] = { {-1,0}, {0,-1}, {1,0}, {0,1} };
	const int size_x = iRiskMap[0].size();
	const int size_y = iRiskMap.size();
	
	priority_queue <tCostPair, vector<tCostPair>, greater<tCostPair> > pq;
	vector<int> distance(size_x * size_y, 99999999);
	distance[0] = 0;
	pq.push(make_pair(0, make_pair(0, 0)));
	while (!pq.empty()) {
		tPair pos = pq.top().second;
		pq.pop();
		for (const tPair& dir : dirs) {
			tPair newPos = make_pair(pos.first + dir.first, pos.second + dir.second);
			if (newPos.first >= 0 && newPos.first < size_x && newPos.second >= 0 && newPos.second < size_y) {
				int newCost = distance[pos.second * size_x + pos.first] + iRiskMap[newPos.second][newPos.first];
				if (newCost < distance[newPos.second * size_x + newPos.first]) {
					distance[newPos.second * size_x + newPos.first] = newCost;
					pq.push(make_pair(newCost, newPos));
				}
			}
		}
	}
	cout << "Lowest risk: " << distance.back() << endl;
}

void part1(const tParsed& iItems) {
	shortest_path(iItems);
}

void part2(const tParsed& iItems) {
	vector<vector<int>> bigMap = iItems;
	int size_x = iItems[0].size();
	int size_y = iItems.size();
	for (int y = 0; y < size_y; ++y) {
		for (int x = size_x; x < size_x * 5; ++x) {
			int risk = bigMap[y][x - size_x] % 9 + 1;
			bigMap[y].push_back(risk);
		}
	}
	for (int y = size_y; y < size_y * 5; ++y) {
		bigMap.push_back(vector<int>());
		for (int x = 0; x < size_x * 5; ++x) {
			int risk = bigMap[y - size_y][x] % 9 + 1;
			bigMap[y].push_back(risk);
		}
	}

	shortest_path(bigMap);
}

int main() {
	const vector<string> lines = readInputFile("day15_input.txt");
	const tParsed parsed = parse(lines);

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

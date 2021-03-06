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

struct Node {
	string name;
	bool isSmall;
	vector<int> routes;	
};
typedef vector<Node> tParsed;

void createNode(map<string, int>& ioNameToIndex, tParsed& ioParsed, const string& iName) {
	if (ioNameToIndex.find(iName) == ioNameToIndex.end()) {
		ioNameToIndex[iName] = ioParsed.size();
		Node node{ iName, iName[0]>='a' && iName[0]<='z' , {} };
		ioParsed.push_back(node);
	}
}

tParsed parse(const vector<string>& iLines) {
	tParsed parsed;
	map<string, int> nameToIndex;
	for (const string& line : iLines) {
		vector<string> line_str;
		split(line, line_str, "-");
		createNode(nameToIndex, parsed, line_str[0]);
		createNode(nameToIndex, parsed, line_str[1]);
		int start_index = nameToIndex[line_str[0]];
		int end_index = nameToIndex[line_str[1]];
		parsed[start_index].routes.push_back(end_index);
		parsed[end_index].routes.push_back(start_index);
	}
	return parsed;
}

int visit(const int iVisitIndex, const bool iAreTwoSmallCavesOk, const tParsed& iNodes, const int iStartIndex, const int iEndIndex, map<int, int>& ioVisited) {
	if (iVisitIndex == iEndIndex) return 1;

	const Node& node = iNodes[iVisitIndex];
	int maxSmallVisit = iAreTwoSmallCavesOk ? 2 : 1;
	if (node.isSmall && ioVisited[iVisitIndex] >= maxSmallVisit) return 0;
	
	if (node.isSmall) ++ioVisited[iVisitIndex];
	bool twoCavesOk = iVisitIndex != iStartIndex && ioVisited[iVisitIndex] >= 2 ? false : iAreTwoSmallCavesOk;

	int sum = 0;
	for (int nodeIndex : node.routes) {
		sum += visit(nodeIndex, twoCavesOk, iNodes, iStartIndex, iEndIndex, ioVisited);
	}
	if (node.isSmall) --ioVisited[iVisitIndex];

	return sum;
}

void part1(const tParsed& iNodes, const int iStartIndex, const int iEndIndex) {
	map<int, int> visited; 
	int sum = visit(iStartIndex, false, iNodes, iStartIndex, iEndIndex, visited);
	cout << sum << endl;
}

void part2(const tParsed& iNodes, const int iStartIndex, const int iEndIndex) {
	map<int, int> visited;
	++visited[iStartIndex];
	int sum = visit(iStartIndex, true, iNodes, iStartIndex, iEndIndex, visited);
	cout << sum << endl;
}

int main() {
	const vector<string> lines = readInputFile("day12_input.txt");

	tParsed nodes = parse(lines);
	int start_index, end_index;
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i].name == "start") start_index = i;
		if (nodes[i].name == "end") end_index = i;
	}

	cout << "Part 1:" << endl;
	part1(nodes, start_index, end_index);
	cout << "Part 2:" << endl;
	part2(nodes, start_index, end_index);
	cout << "hello" << endl;
	return 0;
}

#pragma once
#include <vector>
#include <fstream>
#include <string>

template <class Container>
void split(const std::string& iString, Container& oContainer, const std::string& iDelimeters = " ")
{
	std::size_t current = 0;
	std::size_t previous = 0;
	current = iString.find_first_of(iDelimeters);
	while (current != std::string::npos) {
		oContainer.push_back(iString.substr(previous, current - previous));
		previous = current + 1;
		current = iString.find_first_of(iDelimeters, previous);
	}
	oContainer.push_back(iString.substr(previous, current - previous));
}

std::vector<std::string> readInputFile(const std::string& iFileName) {
	std::vector<std::string> lines;
	std::ifstream ifs("../inputs/" + iFileName);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	split(content, lines, "\n");
	return lines;
}

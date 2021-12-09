#pragma once
#include <algorithm>
#include <cctype>
#include <vector>
#include <fstream>
#include <string>

typedef int32_t i32;
typedef int64_t i64;
#define VS std::vector<std::string>
#define VVS std::vector<std::vector<std::string>>
#define VI std::vector<i32>
#define VVI std::vector<std::vector<i32>>
#define VI64 std::vector<i64>

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
	ltrim(s);
	return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
	rtrim(s);
	return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
	trim(s);
	return s;
}


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

std::vector<int> parseToInts(const std::string& iLine) {
	std::vector<std::string> nrs_str;
	split(iLine, nrs_str, ",");
	std::vector<int> nrs;
	for (const std::string& nr_str : nrs_str) {
		nrs.push_back(stoi(trim_copy(nr_str)));
	}
	return nrs;
}

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

typedef vector<int> tParsed;

tParsed parse(const string& iLine) {
	tParsed parsed;
	for (char c : iLine) {
		int nr;
		if (c >= '0' && c <= '9') nr = c - '0';
		else nr = c - 'A' + 10;
		for (int i = 0; i < 4; ++i) {
			if (nr & (1<<(3-i))) parsed.push_back(1);
			else parsed.push_back(0);
		}
	}
	return parsed;
}

int read_bits(const tParsed& bits, int& index, const int nr_bits) {
	int nr = 0;
	for (int bit = 0; bit < nr_bits; ++bit) {
		if (bits[index + bit] == 1) nr += 1 << (nr_bits - bit - 1);
	}
	index += nr_bits;
	return nr;
}

vector<int64_t> parse_packets(const tParsed& bits, int& index, int64_t& sum_versions, const int max_packets, const int max_length) {
	vector<int64_t> ret;
	int packets_parsed = 0;
	const int start_index = index;
	while (index < bits.size()) {
		if (max_packets != -1 && packets_parsed >= max_packets) break;
		if (max_length != -1 && (index - start_index) >= max_length) break;
		++packets_parsed;

		const int version = read_bits(bits, index, 3);
		sum_versions += version;
		const int type_id = read_bits(bits, index, 3);

		if (type_id == 4) {
			int64_t literal_nr = 0;
			while (true) {
				const int index_prefix = index++;
				int nr = read_bits(bits, index, 4);
				literal_nr = (literal_nr << 4) + nr;
				if (bits[index_prefix] == 0) break;
			}
			ret.push_back(literal_nr);
		}
		else {
			vector<int64_t> nrs;
			int length_type_id = bits[index++];
			if (length_type_id == 0) {
				int length = read_bits(bits, index, 15);
				nrs = parse_packets(bits, index, sum_versions, -1, length);
			}
			else {
				int nr_packets = read_bits(bits, index, 11);
				nrs = parse_packets(bits, index, sum_versions, nr_packets, -1);
			}
			if (type_id == 0) {
				int64_t op_sum = 0;
				for (int64_t x : nrs) op_sum += x;
				ret.push_back(op_sum);
			}
			else if (type_id == 1) {
				int64_t op_product = 1;
				for (int64_t x : nrs) op_product *= x;
				ret.push_back(op_product);
			}
			else if (type_id == 2) {
				int64_t min_value = numeric_limits<int64_t>::max();
				for (int64_t x : nrs) {
					if (x < min_value) min_value = x;
				}
				ret.push_back(min_value);
			}
			else if (type_id == 3) {
				int64_t max_value = numeric_limits<int64_t>::min();
				for (int64_t x : nrs) {
					if (x > max_value) max_value = x;
				}
				ret.push_back(max_value);
			}
			else if (type_id == 5) {
				if (nrs[0] > nrs[1]) ret.push_back(1);
				else ret.push_back(0);
			}
			else if (type_id == 6) {
				if (nrs[0] < nrs[1]) ret.push_back(1);
				else ret.push_back(0);
			}
			else if (type_id == 7) {
				if (nrs[0] == nrs[1]) ret.push_back(1);
				else ret.push_back(0);
			}
		}
		// Ignore last zeros
		if (max_packets == -1 && max_length == -1) break;
	}
	return ret;
}

void part1(const tParsed& v) {
	int64_t sum_versions = 0;
	int index = 0;
	vector<int64_t> ret = parse_packets(v, index, sum_versions, -1, -1);
	cout << sum_versions << endl;
}


void part2(const tParsed& v) {
	int64_t sum_versions = 0;
	int index = 0;
	vector<int64_t> ret = parse_packets(v, index, sum_versions, -1, -1);
	cout << ret[0] << endl;
}

int main() {
	const vector<string> lines = readInputFile("day16_input.txt");
	const tParsed parsed = parse(lines[0]);

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

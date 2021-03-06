#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "advent.h"

using namespace std;

typedef vector<pair<vector<pair<int,int>>, bool>> tParsed;

tParsed parse(const vector<string>& iLines) {
	tParsed parsed;
	for (const string& line : iLines) {
		vector<string> onoff_box = split(line, " ");
		bool on = onoff_box[0] == "on";
		vector<string> dim_str = split(onoff_box[1], ",");
		vector<pair<int, int>> dims;
		for (int i = 0; i < 3; ++i) {
			string onedim(dim_str[i].begin()+2, dim_str[i].end());
			vector<string> onedim_vec = split(onedim, ".");
			int low = stoi(onedim_vec[0]);
			int hi = stoi(onedim_vec.back()) + 1;
			dims.push_back(make_pair(low, hi));
		}
		parsed.push_back(make_pair(dims, on));
	}
	return parsed;
}

void calc(const tParsed& iItems) {
	set<int> range_edge_set[3];
	for (const auto& box_onoff : iItems) {
		const vector<pair<int, int>>& box = box_onoff.first;
		for (int dim = 0; dim < 3; ++dim) {
			range_edge_set[dim].insert(box[dim].first);
			range_edge_set[dim].insert(box[dim].second);
		}
	}
	vector<int> range_edge[3];
	for (int dim = 0; dim < 3; ++dim) {
		range_edge[dim].assign(range_edge_set[dim].begin(), range_edge_set[dim].end());
		sort(range_edge[dim].begin(), range_edge[dim].end());
	}

	int dim0 = range_edge[0].size() - 1;
	int dim1 = range_edge[1].size() - 1;
	int dim2 = range_edge[2].size() - 1;
	vector<bool> paint(dim0 * dim1 * dim2, false);

	for (const auto& box_onoff : iItems) {
		const vector<pair<int, int>>& box = box_onoff.first;
		const bool on_flag = box_onoff.second;
		for (int ix_x = 0; ix_x < dim0; ++ix_x) {
			if (range_edge[0][ix_x + 1] <= box[0].first || range_edge[0][ix_x] >= box[0].second) continue;
			for (int ix_y = 0; ix_y < dim1; ++ix_y) {
				if (range_edge[1][ix_y + 1] <= box[1].first || range_edge[1][ix_y] >= box[1].second) continue;
				for (int ix_z = 0; ix_z < dim2; ++ix_z) {
					if (range_edge[2][ix_z + 1] <= box[2].first || range_edge[2][ix_z] >= box[2].second) continue;
					paint[ix_x * dim1 * dim2 + ix_y * dim2 + ix_z] = on_flag;
				}
			}
		}
	}

	int64_t count = 0;
	for (int ix_x = 0; ix_x < dim0; ++ix_x) {
		for (int ix_y = 0; ix_y < dim1; ++ix_y) {
			for (int ix_z = 0; ix_z < dim2; ++ix_z) {
				if (paint[ix_x * dim1 * dim2 + ix_y * dim2 + ix_z]) {
					count += static_cast<int64_t>(range_edge[0][ix_x + 1] - range_edge[0][ix_x]) *
						static_cast<int64_t>(range_edge[1][ix_y + 1] - range_edge[1][ix_y]) *
						static_cast<int64_t>(range_edge[2][ix_z + 1] - range_edge[2][ix_z]);
				}
			}
		}
	}
	cout << count << endl;
}

void part1(const tParsed& iItems) {
	tParsed reboot_items;
	for (const auto& item : iItems) {
		const auto& v_dim = item.first;
		if (v_dim[0].first >= -50 && v_dim[0].second <= 50 && 
			v_dim[1].first >= -50 && v_dim[1].second <= 50 && 
			v_dim[2].first >= -50 && v_dim[2].second <= 50) 
		{
			reboot_items.push_back(item);
		}
	}
	calc(reboot_items);
}
	
void part2(const tParsed& iItems) {
	calc(iItems);
}

int main() {
	const vector<string> lines = readInputFile("day22_input.txt");
	const tParsed parsed = parse(lines);

	cout << "Part 1:" << endl;
	part1(parsed);
	cout << "Part 2:" << endl;
	part2(parsed);
	return 0;
}

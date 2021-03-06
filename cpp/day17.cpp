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

void parts() {
	constexpr int x1 = 135;
	constexpr int x2 = 155;
	constexpr int y1 = -102;
	constexpr int y2 = -78;

	int max_height = 0;
	int count_valid = 0;
	for (int s_dy = y1; s_dy <= x2; ++s_dy) {
		for (int s_dx = 1; s_dx <= x2; ++s_dx) {
			int dx = s_dx;
			int dy = s_dy;
			int x = 0;
			int y = 0;
			int trajectory_max_height = 0;
			while (true) {
				x += dx;
				y += dy;
				if (dx > 0) dx -= 1;
				dy -= 1;
				if (y > trajectory_max_height) trajectory_max_height = y;
				if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
					if (trajectory_max_height > max_height) max_height = trajectory_max_height;
					++count_valid;
					break;
				}
				if (y < y1 && dy < 0) break;
				if (x > x2) break;
				if (x < x1 && dx == 0) break;
			}
		}
	}
	cout << "Part 1:" << endl;
	cout << max_height << endl;
	cout << "Part 2:" << endl;
	cout << count_valid << endl;
}

int main() {
	parts();
	return 0;
}

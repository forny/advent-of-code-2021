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

void part1(int p1_start, int p2_start) {
	int dice = 0, rolls = 0;
	int pos[2] = { p1_start - 1, p2_start - 1 };
	int score[2] = { 0, 0 };
	for (int turn=0; true; turn ^= 1) {
		rolls += 3;
		int roll = ((dice + 1) % 100) + ((dice + 2) % 100) + ((dice + 3) % 100);
		dice = (dice + 3) % 100;
		pos[turn] = (pos[turn] + roll) % 10;
		score[turn] += pos[turn] + 1;
		if (score[turn] >= 1000) {
			cout << score[turn ^ 1] * rolls << endl;
			break;
		}
	}
}

void part2(int p1_start, int p2_start) {
	const int kDistribution[7] = { 1,3,6,7,6,3,1 };
	const int kNrPositions = 10;
	const int kWinScore = 21;
	int64_t nr_universes[2][kWinScore][kWinScore][kNrPositions][kNrPositions] = {};
	int64_t nr_universes_wins[2] = {};
	nr_universes[0][0][0][p1_start - 1][p2_start - 1] = 1;

	while (true) {
		bool did_extend = false;
		for (int turn = 0; turn < 2; ++turn) {
			for (int p1_score = 0; p1_score < kWinScore; ++p1_score) {
				for (int p2_score = 0; p2_score < kWinScore; ++p2_score) {
					for (int p1_pos = 0; p1_pos < kNrPositions; ++p1_pos) {
						for (int p2_pos = 0; p2_pos < kNrPositions; ++p2_pos) {
							int64_t nr = nr_universes[turn][p1_score][p2_score][p1_pos][p2_pos];
							if (nr != 0) {
								did_extend = true;;
								for (int roll = 3; roll <= 9; ++roll) {
									if (turn == 0) {
										int p1_new_score = p1_score + (p1_pos + roll) % kNrPositions + 1;
										int p1_new_pos = (p1_pos + roll) % kNrPositions;
										if (p1_new_score >= kWinScore) nr_universes_wins[0] += nr * kDistribution[roll - 3];
										else nr_universes[1][p1_new_score][p2_score][p1_new_pos][p2_pos] += nr * kDistribution[roll - 3];
									}
									else {
										int p2_new_score = p2_score + (p2_pos + roll) % kNrPositions + 1;
										int p2_new_pos = (p2_pos + roll) % kNrPositions;
										if (p2_new_score >= kWinScore) nr_universes_wins[1] += nr * kDistribution[roll - 3];
										else nr_universes[0][p1_score][p2_new_score][p1_pos][p2_new_pos] += nr * kDistribution[roll - 3];
									}
								}
							}
						}
					}
				}
			}
			memset(nr_universes[turn], 0, kWinScore*kWinScore*kNrPositions*kNrPositions * sizeof(int64_t));
		}
		if (!did_extend) break;
	}

	cout << max(nr_universes_wins[0], nr_universes_wins[1]) << endl;
}

int main() {
	cout << "Part 1:" << endl;
	part1(4, 2);
	cout << "Part 2:" << endl;
	part2(4, 2);
	return 0;
}

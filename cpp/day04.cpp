#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "advent.h"

using namespace std;

typedef vector<vector<int32_t>> tBoard;
typedef vector<tBoard> tBoards;

void parseBoards(const vector<string>& iLines, tBoards& oBoards, vector<int32_t>& oNumbers) {
	vector<string> numbersStr;
	split(iLines[0], numbersStr, ",");
	for (const string& nr : numbersStr) {
		oNumbers.push_back(stoi(nr));
	}

	for (int32_t i = 2; i < iLines.size(); i += 6) {
		tBoard board;
		for (int y = 0; y < 5; ++y) {
			string lineIn = iLines[i + y];
			vector<string> lineStrings;
			split(lineIn, lineStrings, " ");
			vector<int32_t> lineNumbers;
			for (const string& item : lineStrings) {
				if (!item.empty()) {
					lineNumbers.push_back(stoi(item));
				}
			}
			board.push_back(lineNumbers);
		}
		oBoards.push_back(board);
	}
}

bool checkBingo(const tBoard& iBoard, const int32_t x, const int32_t y)  {
	bool isBingo = true;
	const int32_t sizeY = iBoard.size();
	const int32_t sizeX = iBoard[0].size();
	for (int32_t bingoY = 0; bingoY < sizeY; ++bingoY) {
		if (iBoard[bingoY][x] != -1) {
			isBingo = false;
			break;
		}
	}
	if (!isBingo) {
		isBingo = true;
		for (int32_t bingoX = 0; bingoX < sizeX; ++bingoX) {
			if (iBoard[y][bingoX] != -1) {
				isBingo = false;
				break;
			}
		}
	}
	return isBingo;
}

bool processNumber(tBoard& ioBoard, const int32_t iNumber) {
	const int32_t sizeY = ioBoard.size();
	const int32_t sizeX = ioBoard[0].size();
	for (int32_t y = 0; y < sizeY; ++y) {
		for (int32_t x = 0; x < sizeX; ++x) {
			if (ioBoard[y][x] == iNumber) {
				ioBoard[y][x] = -1;
				return checkBingo(ioBoard, x, y);
			}
		}
	}
	return false;
}

int32_t getScore(const tBoard& iBoard, const int32_t iNumber) {
	int32_t sum = 0;
	const int32_t sizeY = iBoard.size();
	const int32_t sizeX = iBoard[0].size();
	for (int32_t bingo_y = 0; bingo_y < sizeY; ++bingo_y) {
		for (int32_t bingo_x = 0; bingo_x < sizeX; ++bingo_x) {
			int thisNr = iBoard[bingo_y][bingo_x];
			if (thisNr != -1) {
				sum += thisNr;
			}
		}
	}
	return sum * iNumber;
}

void part1(const tBoards& iBoards, const vector<int32_t>& iNumbers) {
	tBoards boards = iBoards;
	for (const int32_t nr : iNumbers) {
		for (int32_t boardNr = 0; boardNr < boards.size(); ++boardNr) {
			bool isBingo = processNumber(boards[boardNr], nr);
			if (isBingo) {
				int32_t score = getScore(boards[boardNr], nr);
				cout << score << endl;
				return;
			}
		}
	}
}

void part2(const tBoards& iBoards, const vector<int32_t>& iNumbers) {
	tBoards boardsKept = iBoards;
	for (const int32_t nr : iNumbers) {
		tBoards boardsKeep;
		for (int32_t boardNr = 0; boardNr < boardsKept.size(); ++boardNr) {
			bool isBingo = processNumber(boardsKept[boardNr], nr);
			if (isBingo && boardsKept.size() == 1) {
				int32_t score = getScore(boardsKept[boardNr], nr);
				cout << score << endl;
				return;
			}
			if (!isBingo) {
				boardsKeep.push_back(boardsKept[boardNr]);
			}
		}
		boardsKept = boardsKeep;
	}
}

int main() {
	const vector<string> lines = readInputFile("day4_input.txt");
	vector<int32_t> numbers;
	tBoards boards;
	parseBoards(lines, boards, numbers);

	cout << "Part 1:" << endl;
	part1(boards, numbers);
	cout << "Part 2:" << endl;
	part2(boards, numbers);
	return 0;
}


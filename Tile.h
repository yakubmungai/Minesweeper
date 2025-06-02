#pragma once

struct Tile {
	//string pos;
	int tileRow;
	int tileColumn;
	bool is_Hidden = true;
	bool is_a_Mine = false;
	bool is_a_Flag = false;
	bool is_in_Debug = false;
	bool is_countedasRevealed = false;
	int numAdjacentMines = 0;
	std::vector<Tile*> neighborsVec;
};

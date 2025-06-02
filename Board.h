#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#include "Tile.h"

class Board
{
private:
	int rows;
	int columns;
	int numMines;
	int numFlags = 0;
	int numtilesRevealed = 0;
	bool toggleDebug = false;
	bool gameWon = false;
	bool gameOver = false;
	void readfromCFG(std::string cfg_filename);
	std::vector<std::vector<Tile>> boardVec;

public:
	Board(std::string filename);

	int GetRows();

	int GetColumns();

	int GetnumMines();

	int GetnumFlags();

	void calculatenumtilesRevealed();

	bool GetgameWon();

	bool GetgameOver();

	bool SetgameOver();

	//void addnumtilesRevealed();

	Tile& GetTile(int Tilerows, int Tilecolumns);

	void initalizeBoard();

	void DrawBoard(sf::RenderWindow& gameWindow);

	void showNeighbors(Tile& clickedTile);

	void restartBoard();

	void debugBoard();

	void revealMines();

	void checkifWin();

	void drawbackgroundTiles(sf::RenderWindow& gameWindow);

	void readLeaderboard(std::vector<std::string>& timeVec, std::vector<std::string>& nameVec);

	//void showMines(sf::RenderWindow& gameWindow);
};
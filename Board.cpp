#pragma once
#include "Board.h"
#include "Random.h"


Board::Board(std::string filename) {
	readfromCFG(filename);
 
}

int Board::GetRows() {
	return rows;
}

int Board::GetColumns() {
	return columns;
}

int Board::GetnumMines() {
	return numMines;
}

int Board::GetnumFlags() {
    return numFlags;
}

void Board::calculatenumtilesRevealed() {
   // cout << "beforeFunctnumtilesRevealed: " << numtilesRevealed << endl;
    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            if (!boardVec[ii][jj].is_a_Mine && !boardVec[ii][jj].is_Hidden && !boardVec[ii][jj].is_countedasRevealed) {      
                numtilesRevealed += 1;
                boardVec[ii][jj].is_countedasRevealed = true;
                cout << "NumtilesRevealed: " << numtilesRevealed << endl;
            }
        }
    }
    //cout << "Tiles Revealed: " << numtilesRevealed << endl;  
}

Tile& Board::GetTile(int tileRows, int tileColumns) {
    return boardVec[tileRows][tileColumns];
}

bool Board::GetgameWon() {
    return gameWon;

}

bool Board::GetgameOver() {
    return gameOver;

}

bool Board::SetgameOver() {
    gameOver = !gameOver;
    return gameOver;
}

void Board::readfromCFG(std::string cfg_filename) {
    std::ifstream stream(cfg_filename);
    if (stream.is_open()) {
        std::string line;

        getline(stream, line);
        columns = std::stoi(line);

        getline(stream, line);
        rows = std::stoi(line);

        getline(stream, line);
        numMines = std::stoi(line);
    }
    else {
        std::cout << "Error reading from: " << cfg_filename << "!" << std::endl;
    }
}

void Board::initalizeBoard() {
    // BoardVec of Tile objects initialization
    boardVec.resize(rows, std::vector<Tile>(columns));
    int minesAdded = 0;
    cout << "numMines: " << numMines << endl;

    // Placing random Mine
    while (minesAdded < numMines) {
        int randomRowMine = Random::Int(0, rows - 1);
        int randomColMine = Random::Int(0, columns - 1);
        /*cout << randomRowMine << "," << randomColMine << endl;*/
        if (!boardVec[randomRowMine][randomColMine].is_a_Mine) {
            boardVec[randomRowMine][randomColMine].is_a_Mine = true;
            minesAdded += 1;
        }
    }
    int num = 0;
    for (auto& row : boardVec) {
        for (auto& tile : row) {
            if (tile.is_a_Mine)
                num++;
        }
    }
    cout << num << endl;
    
    //// Checking Adjacent Mines (Review to make changes)
    //for (int ii = 0; ii < rows; ii++) {
    //    for (int jj = 0; jj < columns; jj++) {
    //        Tile& currentTile = boardVec[ii][jj];
    //        if (!currentTile.is_a_Mine) {
    //            
    //            int deltas[8][2] = { {0,1}, {0,-1}, {1,0}, {-1, 0}, {1, 1}, {-1,-1}, {-1,1}, {1,-1} };
    //            for (auto delta : deltas) {
    //                // delta = {deltaCol,deltaRow}
    //                int neighborCol = jj + delta[0];
    //                int neighborRow = ii + delta[1];

    //                if (neighborRow < boardVec.size() && neighborCol < boardVec[ii].size()) {
    //                    if (!(neighborRow == ii && neighborCol == jj)) {
    //                        if (boardVec[neighborRow][neighborCol].is_a_Mine) {
    //                            currentTile.neighborsVec.push_back(&boardVec[neighborRow][neighborCol]);
    //                            currentTile.numAdjacentMines += 1;

    //                            // Print debug information for neighborsVec size
    //                            cout << "NeighborsVec size: " << currentTile.neighborsVec.size() << endl;
    //                        }
    //                    }
    //                }
    //            }                                          
    //        }
    //    }
    //}

  // Checking Adjacent Mines (Review to make changes)
    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            Tile& currentTile = boardVec[ii][jj];
            if (!currentTile.is_a_Mine) {
                
                int directionArray[8][2] = { {0,1}, {0,-1}, {1,0}, {-1, 0}, {1, 1}, {-1,-1}, {-1,1}, {1,-1} };
                for (auto directionArray : directionArray) {
                    // directionArray = {deltaCol,deltaRow}
                    int neighborCol = jj + directionArray[0];
                    int neighborRow = ii + directionArray[1];

                    if (neighborRow < boardVec.size() && neighborCol < boardVec[ii].size()) {
                        if (!(neighborRow == ii && neighborCol == jj)) {
                            currentTile.neighborsVec.push_back(&boardVec[neighborRow][neighborCol]);
                            if (boardVec[neighborRow][neighborCol].is_a_Mine) {                    
                                currentTile.numAdjacentMines += 1;

                                // Print debug information for neighborsVec size
                                //cout << "NeighborsVec size: " << currentTile.neighborsVec.size() << endl;
                            }
                        }
                    }
                }               
            }
        }
    }
}

void Board::DrawBoard(sf::RenderWindow& gameWindow) {
    sf::Texture& hiddentileTexture = TextureManager::getTexture("tile_hidden");
    sf::Texture& revealedtileTexture = TextureManager::getTexture("tile_revealed");
    sf::Texture& flagtileTexture = TextureManager::getTexture("flag");
    sf::Texture& minetileTexture = TextureManager::getTexture("mine");
    sf::Texture& onetileTexture = TextureManager::getTexture("number_1");
    sf::Texture& twotileTexture = TextureManager::getTexture("number_2");
    sf::Texture& threetileTexture = TextureManager::getTexture("number_3");
    sf::Texture& fourtileTexture = TextureManager::getTexture("number_4");
    sf::Texture& fivetileTexture = TextureManager::getTexture("number_5");
    sf::Texture& sixtileTexture = TextureManager::getTexture("number_6");
    sf::Texture& seventileTexture = TextureManager::getTexture("number_7");
    sf::Texture& eighttileTexture = TextureManager::getTexture("number_8");
    
    numFlags = 0;

    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            //string pos = to_string(ii) + "," + to_string(jj);
            boardVec[ii][jj].tileRow = ii;
            boardVec[ii][jj].tileColumn = jj;

            sf::Sprite revealedtileSprite;
            revealedtileSprite.setTexture(revealedtileTexture);
            revealedtileSprite.setPosition(jj * 32, ii * 32);
            gameWindow.draw(revealedtileSprite);

            if (boardVec[ii][jj].is_a_Mine) {
                sf::Sprite minetileSprite;
                minetileSprite.setTexture(minetileTexture);
                minetileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(minetileSprite);
            
            }

            //Code for drawing the numbers
            if (boardVec[ii][jj].numAdjacentMines == 1) {
                sf::Sprite onetileSprite;
                onetileSprite.setTexture(onetileTexture);
                onetileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(onetileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 2) {
                sf::Sprite twotileSprite;
                twotileSprite.setTexture(twotileTexture);
                twotileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(twotileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 3) {
                sf::Sprite threetileSprite;
                threetileSprite.setTexture(threetileTexture);
                threetileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(threetileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 4) {
                sf::Sprite fourtileSprite;
                fourtileSprite.setTexture(fourtileTexture);
                fourtileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(fourtileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 5) {
                sf::Sprite fivetileSprite;
                fivetileSprite.setTexture(fivetileTexture);
                fivetileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(fivetileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 6) {
                sf::Sprite sixtileSprite;
                sixtileSprite.setTexture(sixtileTexture);
                sixtileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(sixtileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 7) {
                sf::Sprite seventileSprite;
                seventileSprite.setTexture(seventileTexture);
                seventileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(seventileSprite);

            }

            if (boardVec[ii][jj].numAdjacentMines == 8) {
                sf::Sprite eighttileSprite;
                eighttileSprite.setTexture(onetileTexture);
                eighttileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(eighttileSprite);


            }

            if (boardVec[ii][jj].is_Hidden && boardVec[ii][jj].is_a_Mine && gameWon) {
                sf::Sprite hiddentileSprite;
                hiddentileSprite.setTexture(hiddentileTexture);
                hiddentileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(hiddentileSprite);
                boardVec[ii][jj].is_a_Flag = true;
                boardVec[ii][jj].is_in_Debug = false;
            }

            if (boardVec[ii][jj].is_Hidden) {
                sf::Sprite hiddentileSprite;
                hiddentileSprite.setTexture(hiddentileTexture);
                hiddentileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(hiddentileSprite);               
            }      

            if (boardVec[ii][jj].is_a_Flag) {
                sf::Sprite flagtileSprite;
                flagtileSprite.setTexture(flagtileTexture);
                flagtileSprite.setPosition(jj * 32, ii * 32);
                gameWindow.draw(flagtileSprite);   
                numFlags += 1;
               
            }          

            if (boardVec[ii][jj].is_in_Debug) {                   
                    sf::Sprite minetileSprite;
                    minetileSprite.setTexture(minetileTexture);
                    minetileSprite.setPosition(jj * 32, ii * 32);
                    gameWindow.draw(minetileSprite);  
            }

        }
    }
    //cout << "numFlags: " << numFlags << endl;
    /*if (gameWon) {
        for (int ii = 0; ii < rows; ii++) {
            for (int jj = 0; jj < columns; jj++) {
                if (boardVec[ii][jj].is_a_Flag) {
                    sf::Sprite flagtileSprite;
                    flagtileSprite.setTexture(flagtileTexture);
                    flagtileSprite.setPosition(jj * 32, ii * 32);
                    gameWindow.draw(flagtileSprite);
                }
            }
        }
    }*/
}

void Board::showNeighbors(Tile& clickedTile) {
    for (int ii = 0; ii < clickedTile.neighborsVec.size(); ii++) {
        Tile* neighborTile = clickedTile.neighborsVec[ii];

        if (!neighborTile->is_a_Mine && neighborTile->is_Hidden && !neighborTile->is_a_Flag) {         
            neighborTile->is_Hidden = false;
            /*numtilesRevealed += 1;
            cout << "numTiles Revealed: " << numtilesRevealed << endl;*/

            if (neighborTile->numAdjacentMines == 0) {
                showNeighbors(*neighborTile);
            }         
        }
    }
}

void Board::restartBoard() {
    boardVec.clear();
    gameOver = false;
    gameWon = false;
    toggleDebug = false;
    numFlags = 0;
    numtilesRevealed = 0;
    initalizeBoard();
    
}

void Board::debugBoard() {
    toggleDebug = !toggleDebug; // Handles the on/off of debugMode
    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            if (boardVec[ii][jj].is_a_Mine) {
                boardVec[ii][jj].is_in_Debug = toggleDebug; // Handles the drawing
            }
        }
    }      
}

void Board::revealMines() {
    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            if (boardVec[ii][jj].is_a_Mine) {
                boardVec[ii][jj].is_Hidden = false;
            }
        }
    }
}

void Board::checkifWin() {
    int totalnonmineTiles = (rows * columns) - numMines;
    if (numtilesRevealed == totalnonmineTiles) {
        gameWon = true;
        /*for (int ii = 0; ii < rows; ii++) {
            for (int jj = 0; jj < columns; jj++) {
                if (boardVec[ii][jj].is_a_Mine) {
                    boardVec[ii][jj].is_a_Flag = true;
                }
            }
        }*/
    }
}

void Board::drawbackgroundTiles(sf::RenderWindow& gameWindow) {
    sf::Texture& revealedtileTexture = TextureManager::getTexture("tile_revealed");
    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            //string pos = to_string(ii) + "," + to_string(jj);
            boardVec[ii][jj].tileRow = ii;
            boardVec[ii][jj].tileColumn = jj;

            sf::Sprite revealedtileSprite;
            revealedtileSprite.setTexture(revealedtileTexture);
            revealedtileSprite.setPosition(jj * 32, ii * 32);
            gameWindow.draw(revealedtileSprite);

        }
    }
}

void Board::readLeaderboard(std::vector<std::string>& timeVec, std::vector<std::string>& nameVec) {
    std::ifstream stream("leaderboard.txt");

    std::string line;
    std::string time;
    std::string name;
    while (getline(stream, line, ',')) {
        cout << "Enters loop" << endl;
        time = line;
        timeVec.push_back(time);
        getline(stream, line);
        name = line;
        nameVec.push_back(name);
    
    }
}

//std::ifstream stream(cfg_filename);
//if (stream.is_open()) {
//    std::string line;
//
//    getline(stream, line);
//    columns = std::stoi(line);
//
//    getline(stream, line);
//    rows = std::stoi(line);
//
//    getline(stream, line);
//    numMines = std::stoi(line);
//}
//else {
//    std::cout << "Error reading from: " << cfg_filename << "!" << std::endl;
//}
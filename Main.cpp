#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "TextureManager.h"
#include <chrono>


map<int, sf::Sprite> parseDigits(sf::Sprite digits) {
	map<int, sf::Sprite> digitsMap;

	for (int i = 0; i < 10; i++) {
		sf::IntRect rect(i * 21, 0, 21, 32);
		digits.setTextureRect(rect);
		sf::Sprite sprite = digits;
		digitsMap.emplace(i, sprite);
	}

	return digitsMap;
}

int main() {
	// Init
	Board boardObj("config.cfg");
	int winWidth = boardObj.GetColumns() * 32;
	int winHeight = (boardObj.GetRows() * 32) + 100;

	// Welcome Window
	sf::RenderWindow welcomeWindow(sf::VideoMode(winWidth, winHeight), "Minesweeper!");
	sf::Font font;
	font.loadFromFile("font.ttf");

	if (!font.loadFromFile(("font.ttf"))) {
		std::cout << "Unable to load font" << std::endl;
		return 0;
	}

	sf::Text welcomeText;
	welcomeText.setString("WELCOME TO MINESWEEPER!");
	welcomeText.setFont(font);
	welcomeText.setCharacterSize(24);
	welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	welcomeText.setFillColor(sf::Color::White);
	sf::FloatRect welcomeTextRect = welcomeText.getLocalBounds();
	welcomeText.setOrigin(welcomeTextRect.left + welcomeTextRect.width / 2.0f, welcomeTextRect.top + welcomeTextRect.height / 2.0f);
	welcomeText.setPosition(sf::Vector2f(winWidth / 2.0f, (winHeight / 2.0f) - 150));


	sf::Text enternameText;
	enternameText.setString("Enter Name:");
	enternameText.setFont(font);
	enternameText.setCharacterSize(20);
	enternameText.setStyle(sf::Text::Bold);
	enternameText.setFillColor(sf::Color::White);
	sf::FloatRect enternameRect = enternameText.getLocalBounds();
	enternameText.setOrigin(enternameRect.left + enternameRect.width / 2.0f, enternameRect.top + enternameRect.height / 2.0f);
	enternameText.setPosition(sf::Vector2f(winWidth / 2.0f, (winHeight / 2.0f) - 75));

	sf::Text inputnameText;
	inputnameText.setFont(font);
	inputnameText.setCharacterSize(18);
	inputnameText.setStyle(sf::Text::Bold);
	inputnameText.setFillColor(sf::Color::Yellow);
	inputnameText.setString("|");
	sf::FloatRect inputnameRect = inputnameText.getLocalBounds();
	inputnameText.setOrigin(inputnameRect.left + inputnameRect.width / 2.0f, inputnameRect.top + inputnameRect.height / 2.0f);
	inputnameText.setPosition(sf::Vector2f(winWidth / 2.0f, (winHeight / 2.0f) - 45));
	std::string playerName;
	bool welcomeWindowClosed = false;
	

	while (welcomeWindow.isOpen()) {
		sf::Event event;
		while (welcomeWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				welcomeWindow.close();
				welcomeWindowClosed = true;
			}

			if (event.type == sf::Event::TextEntered) {
				if (std::isalpha(event.text.unicode)) {
					if (playerName.empty()) {
						playerName += static_cast<char>(std::toupper(event.text.unicode));
					}
					else {
						playerName += static_cast<char>(std::tolower(event.text.unicode));
					}

					inputnameText.setString(playerName + "|");
					sf::FloatRect inputnameRect = inputnameText.getLocalBounds();
					inputnameText.setOrigin(inputnameRect.left + inputnameRect.width / 2.0f, inputnameRect.top + inputnameRect.height / 2.0f);
					inputnameText.setPosition(sf::Vector2f(winWidth / 2.0f, (winHeight / 2.0f) - 45));
				}
				else if (!playerName.empty() && event.text.unicode == 8) {
					playerName.pop_back();
					inputnameText.setString(playerName + "|");
					sf::FloatRect inputnameRect = inputnameText.getLocalBounds();
					inputnameText.setOrigin(inputnameRect.left + inputnameRect.width / 2.0f, inputnameRect.top + inputnameRect.height / 2.0f);
					inputnameText.setPosition(sf::Vector2f(winWidth / 2.0f, (winHeight / 2.0f) - 45));
				}

				if (playerName.length() > 10) {
					playerName.pop_back();
					inputnameText.setString(playerName + "|");
					sf::FloatRect inputnameRect = inputnameText.getLocalBounds();
					inputnameText.setOrigin(inputnameRect.left + inputnameRect.width / 2.0f, inputnameRect.top + inputnameRect.height / 2.0f);
					inputnameText.setPosition(sf::Vector2f(winWidth / 2.0f, (winHeight / 2.0f) - 45));
				}
			}

			if (event.type == sf::Event::KeyPressed && playerName.length() > 0) {
				if (event.key.code == sf::Keyboard::Enter) {
					welcomeWindow.close();
				}
			
			}
		}
		welcomeWindow.clear(sf::Color::Blue);
		welcomeWindow.draw(welcomeText);
		welcomeWindow.draw(enternameText);
		welcomeWindow.draw(inputnameText);
		welcomeWindow.display();
	}

	// Creating Game Window
	sf::RenderWindow gameWindow(sf::VideoMode(winWidth, winHeight), "Jacs Minesweeper");

	//Timer initialization
	//Below is just for initialization, in the end, this will be overwritten, just needed to equal something. TLDR: Ignore what it equals here (below).
	auto pauseTime = chrono::high_resolution_clock::now();
	auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime).count();
	bool paused = false; //false when game in not paused, true when the game is paused

	
	// Creating face sprite
	sf::Sprite faceSprite;

	//Loading Happy Face Texture
	sf::Texture& happyfaceTexture = TextureManager::getTexture("face_happy");
	faceSprite.setTexture(happyfaceTexture);
	faceSprite.setPosition(((boardObj.GetColumns()/2.0f)*32)-32, 32*(boardObj.GetRows() + 0.5f));

	//Loading Lose Face Texture
	sf::Texture& losefaceTexture = TextureManager::getTexture("face_lose");

	//Loading Win Face Texture
	sf::Texture& winfaceTexture = TextureManager::getTexture("face_win");

	//Loading Debug Button Texture
	sf::Texture& debugbuttonTexture = TextureManager::getTexture("debug");
	sf::Sprite debugbuttonSprite;
	debugbuttonSprite.setTexture(debugbuttonTexture);
	debugbuttonSprite.setPosition(((boardObj.GetColumns() * 32)- 304), 32 * (boardObj.GetRows() + 0.5f));

	//Loading Play Button Texture
	sf::Texture& playbuttonTexture = TextureManager::getTexture("play");
	sf::Sprite playbuttonSprite;
	playbuttonSprite.setTexture(playbuttonTexture);
	playbuttonSprite.setPosition(((boardObj.GetColumns() * 32) - 240), 32 * (boardObj.GetRows() + 0.5f));

	//Loading Pause Button Texture
	sf::Texture& pausebuttonTexture = TextureManager::getTexture("pause");
	sf::Sprite pausebuttonSprite;
	pausebuttonSprite.setTexture(pausebuttonTexture);
	pausebuttonSprite.setPosition(((boardObj.GetColumns() * 32) - 240), 32 * (boardObj.GetRows() + 0.5f));

	//Loading Leaderboard Button Texture
	sf::Texture& leaderboardbuttonTexture = TextureManager::getTexture("leaderboard");
	sf::Sprite leaderboardbuttonSprite;
	leaderboardbuttonSprite.setTexture(leaderboardbuttonTexture);
	leaderboardbuttonSprite.setPosition(((boardObj.GetColumns() * 32) - 176), 32 * (boardObj.GetRows() + 0.5f));

	//Digits
	sf::Texture& digitsTexture = TextureManager::getTexture("digits");
	//sf::IntRect digitRect = 

	//Minus Digit
	sf::Sprite minusdigitSprite;
	minusdigitSprite.setTexture(digitsTexture);
	int ypos = (32 * (boardObj.GetRows() + 0.5f) + 16);
	minusdigitSprite.setTextureRect(sf::IntRect(210, 0, 21, 32));

	sf::Texture& digitsText = TextureManager::getTexture("digits");
	sf::Sprite digits;
	digits.setTexture(digitsText);

	map<int, sf::Sprite> digitsMap = parseDigits(digits); //map for my digits
	

	boardObj.initalizeBoard();
	
	bool gamePaused = false;
	bool leaderboardactive = false;
	int minutes;
	int seconds;
	
	auto start_time = chrono::high_resolution_clock::now();//starting the timer when the program begins to run!
	//In project 3, this(^^^) would go above the Game Window while loops, but below the Welcome Window while loops
		while (gameWindow.isOpen() && !welcomeWindowClosed) {
			sf::Event event;


			while (gameWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gameWindow.close();
				}
				if ((gamePaused && !boardObj.GetgameOver() && !boardObj.GetgameWon())) {
					boardObj.drawbackgroundTiles(gameWindow);
				}
				
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					//if (sf::Mouse::getPosition(gameWindow).y < boardObj.GetRows()) {
						sf::Vector2i leftMouse;
						leftMouse = sf::Mouse::getPosition(gameWindow);
						Tile& clickedTile = boardObj.GetTile(leftMouse.y / 32, leftMouse.x / 32);

						if (debugbuttonSprite.getGlobalBounds().contains(gameWindow.mapPixelToCoords(leftMouse))) {
							cout << "debugClicked" << endl;
							if (!boardObj.GetgameOver() && !boardObj.GetgameWon()) {
								boardObj.debugBoard();
								//boardObj.debugBoard(gameWindow);
							}

						}
						else if (faceSprite.getGlobalBounds().contains(gameWindow.mapPixelToCoords(leftMouse))) {
							/*sf::Texture& happyfaceTexture = TextureManager::getTexture("face_happy");
							sf::Sprite happyfaceSprite;*/
							cout << "happyFace Clicked" << endl;
							faceSprite.setTexture(happyfaceTexture);
							faceSprite.setPosition(((boardObj.GetColumns() / 2.0f) * 32) - 32, 32 * (boardObj.GetRows() + 0.5f));
							boardObj.restartBoard();
							start_time = chrono::high_resolution_clock::now();
							elapsed_paused_time = 0;
							gamePaused = false;


						}
						else if (pausebuttonSprite.getGlobalBounds().contains(gameWindow.mapPixelToCoords(leftMouse))) {
							if (!boardObj.GetgameOver() && !boardObj.GetgameWon()) {
								//cout << "PauseButton clicked" << endl;
								gamePaused = !gamePaused;
								if (gamePaused) {
									//cout << "paused" << endl;
									pauseTime = chrono::high_resolution_clock::now();
								}
								else {
									//unpaused
									auto unPausedTime = chrono::steady_clock::now();
									elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count(); //Addition is necessary for when hitting the pause button more than once
									cout << elapsed_paused_time % 60 << " " << endl;
								}
							}

						}
						else if (leaderboardbuttonSprite.getGlobalBounds().contains(gameWindow.mapPixelToCoords(leftMouse))) {
							leaderboardactive = !leaderboardactive;
							//cout << "Leaderboardbutton Clicked" << endl;
							int xpos = (boardObj.GetColumns() * 16) / 2.0f;
							int ypos = (((boardObj.GetRows() * 16) + 50) / 2.0f) - 120;

							// Leaderboard Window
							boardObj.drawbackgroundTiles(gameWindow);
							gameWindow.display();

							sf::RenderWindow leaderboardWindow(sf::VideoMode((boardObj.GetColumns() * 16), (boardObj.GetRows() * 16) + 50), "Jacs Minesweeper Leaderboard");

							//Text
							sf::Text leaderboardText;
							leaderboardText.setString("LEADERBOARD");
							leaderboardText.setFont(font);
							leaderboardText.setCharacterSize(20);
							leaderboardText.setStyle(sf::Text::Bold | sf::Text::Underlined);
							leaderboardText.setFillColor(sf::Color::White);
							sf::FloatRect leaderboardTextRect = leaderboardText.getLocalBounds();
							leaderboardText.setOrigin(leaderboardTextRect.left + leaderboardTextRect.width / 2.0f, leaderboardTextRect.top + leaderboardTextRect.height / 2.0f);
							leaderboardText.setPosition(sf::Vector2f(xpos, ypos));

							// Getting Leaderboard stats
							vector<string> timeVector;
							vector<string> nameVector;

							boardObj.readLeaderboard(timeVector, nameVector);
							cout << "Size of timeVector: " << timeVector.size() << endl;
							cout << "Size of nameVector: " << nameVector.size() << endl;

							// Drawing Leaderboard stats
							sf::Text leaderboardstatsText;
							leaderboardstatsText.setFont(font);
							leaderboardstatsText.setCharacterSize(18);
							leaderboardstatsText.setStyle(sf::Text::Bold);
							leaderboardstatsText.setFillColor(sf::Color::White);
							sf::FloatRect leaderboardstatsTextRect = leaderboardstatsText.getLocalBounds();
							leaderboardstatsText.setOrigin(leaderboardstatsTextRect.left + leaderboardstatsTextRect.width / 2.0f, leaderboardstatsTextRect.top + leaderboardstatsTextRect.height / 2.0f);
							leaderboardstatsText.setPosition(sf::Vector2f(xpos, ypos + 40));

							int numelementsinVec = nameVector.size();
							string statline;
							int rank = 0;

							for (int ii = 0; ii < numelementsinVec; ii++) {
								rank += 1;
								statline += to_string(rank) + "." + "\t" + timeVector[ii] + "\t" + nameVector[ii] + "\n" + "\n";

							}
							leaderboardstatsText.setString(statline);
							leaderboardstatsText.move(leaderboardstatsText.getLocalBounds().width / 2 * -1, 0);


							//Window While loops
							while (leaderboardWindow.isOpen()) {
								sf::Event event;
								while (leaderboardWindow.pollEvent(event)) {
									if (event.type == sf::Event::Closed) {
										leaderboardWindow.close();
									}
								}

								leaderboardWindow.clear(sf::Color::Blue);
								leaderboardWindow.draw(leaderboardText);
								leaderboardstatsText.setString(statline);
								leaderboardstatsText.setOrigin(leaderboardstatsTextRect.left + leaderboardstatsTextRect.width / 2.0f, leaderboardstatsTextRect.top + leaderboardstatsTextRect.height / 2.0f);
								// Drawing the tilesrevealed when game is paused

								leaderboardWindow.draw(leaderboardstatsText);
								leaderboardWindow.display();

							}

						}
						else if (clickedTile.is_Hidden && !clickedTile.is_a_Flag) {
							//click on non mine tile
							if (!gamePaused) {
								if (!boardObj.GetgameOver()) {
									/*std::cout << "Mouse button pressed at X: " << leftMouse.x / 32;
									std::cout << " Y: " << leftMouse.y / 32 << std::endl;*/
									cout << clickedTile.is_Hidden << endl;
									clickedTile.is_Hidden = false;
									boardObj.calculatenumtilesRevealed();
									boardObj.checkifWin();
									cout << "numMines: " << boardObj.GetnumMines() << endl;


									if (clickedTile.numAdjacentMines == 0) {
										cout << "Here1" << endl;
										boardObj.showNeighbors(clickedTile);
									}

									if (boardObj.GetgameWon()) {
										cout << "enters loop if game won" << endl;
										faceSprite.setTexture(winfaceTexture);
										faceSprite.setPosition(((boardObj.GetColumns() / 2.0f) * 32) - 32, 32 * (boardObj.GetRows() + 0.5f));
										gamePaused = true;


									}
									/*cout << "BeforeImplementationnumtilesRevealed" << endl;
									boardObj.calculatenumtilesRevealed();
									cout << "AfterImplementationnumtilesRevealed" << endl;*/

								}
							}

							//click on mine code
							if (clickedTile.is_a_Mine) {
								boardObj.SetgameOver(); //gameOver = true;
								gamePaused = true;
								boardObj.revealMines();
								faceSprite.setTexture(losefaceTexture);
								faceSprite.setPosition(((boardObj.GetColumns() / 2.0f) * 32) - 32, 32 * (boardObj.GetRows() + 0.5f));
							}

							//game win code
							if (boardObj.GetgameWon()) {
								cout << "Voila!" << endl;
								faceSprite.setTexture(winfaceTexture);
								faceSprite.setPosition(((boardObj.GetColumns() / 2.0f) * 32) - 32, 32 * (boardObj.GetRows() + 0.5f));
							}
						} //else if (clickedTile.is_Hidden && !clickedTile.is_a_Flag) {
					//}
				}
				
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
					sf::Vector2i rightMouse;
					rightMouse = sf::Mouse::getPosition(gameWindow);
					/*std::cout << "Mouse button pressed at X: " << rightMouse.x / 32;
					std::cout << " Y: " << rightMouse.y / 32 << std::endl;*/

					Tile& clickedTile = boardObj.GetTile(rightMouse.y / 32, rightMouse.x / 32);
					cout << clickedTile.is_Hidden << endl;

					if (!gamePaused) {
						if (clickedTile.is_Hidden) {
							/*cout << "numFlags: " << boardObj.GetnumFlags() << endl;*/
							cout << "Made it!" << endl;
							clickedTile.is_a_Flag = !clickedTile.is_a_Flag;

						}
					}
				}			
			}
			// Drawing White background
			gameWindow.clear(sf::Color::White);

			//Timer Implementation
			auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
			int total_time = game_duration.count(); // necessary to subtract elapsed time later because "game_duration.count()" is const

			if (!gamePaused) {
				//enters if the game is NOT paused. This is the condition that keeps the timer from incrementing when paused.
				total_time = total_time - elapsed_paused_time; //
				minutes = total_time / 60;
				seconds = total_time % 60;
			}

			//"separating" the integers. So.... 68 -> seconds0 = 6 and seconds1 = 8
			int minutes0 = minutes / 10 % 10; //minutes index 0
			int minutes1 = minutes % 10; // minutes index 1
			int seconds0 = seconds / 10 % 10; // seconds index 0
			int seconds1 = seconds % 10; // seconds index 1

			// Draw Timer
			digitsMap[minutes0].setPosition((boardObj.GetColumns() * 32) - 97, (32 * (boardObj.GetRows() + 0.5f) + 16));
			gameWindow.draw(digitsMap[minutes0]);

			digitsMap[minutes1].setPosition((boardObj.GetColumns() * 32) - 76, (32 * (boardObj.GetRows() + 0.5f) + 16));
			gameWindow.draw(digitsMap[minutes1]);

			digitsMap[seconds0].setPosition((boardObj.GetColumns() * 32) - 54, (32 * (boardObj.GetRows() + 0.5f) + 16));
			gameWindow.draw(digitsMap[seconds0]);

			digitsMap[seconds1].setPosition((boardObj.GetColumns() * 32) - 33, (32 * (boardObj.GetRows() + 0.5f) + 16));
			gameWindow.draw(digitsMap[seconds1]);

			gameWindow.draw(pausebuttonSprite);

			/*if (gamePaused) {
				gameWindow.draw(playbuttonSprite);
				boardObj.drawbackgroundTiles(gameWindow);
			}*/


			// Counter Implementation
			int abscounterNum = std::abs(boardObj.GetnumMines() - boardObj.GetnumFlags());
			int counterNum = boardObj.GetnumMines() - boardObj.GetnumFlags();
			/*cout << "numFlags: " << boardObj.GetnumFlags() << endl;
			cout << "abscounterNum: " << abscounterNum << endl;
			cout << "counterNum: " << counterNum << endl;*/

			//"separating" the digits
			int hundreds = abscounterNum / 100 % 10;
			int tens = abscounterNum / 10 % 10; 
			int ones = abscounterNum % 10; 

			// Draw Counter
			if (counterNum >= 0) {
				digitsMap[hundreds].setPosition(33, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[hundreds]);

				digitsMap[tens].setPosition(54, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[tens]);

				digitsMap[ones].setPosition(75, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[ones]);

			} 
			else if (counterNum < 0 && counterNum > -10) {
				cout << "Yessir" << endl;
				/*digitsMap[10].setPosition(54, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[10]);*/
				minusdigitSprite.setPosition(54, ypos);
				gameWindow.draw(minusdigitSprite);

				digitsMap[ones].setPosition(75, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[ones]);

				
			} 
			else {
				/*digitsMap[10].setPosition(33, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[10]);*/
				minusdigitSprite.setPosition(33, ypos);
				gameWindow.draw(minusdigitSprite);

				digitsMap[tens].setPosition(54, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[tens]);

				digitsMap[ones].setPosition(75, (32 * (boardObj.GetRows() + 0.5f) + 16));
				gameWindow.draw(digitsMap[ones]);
			}

			// Drawing
			gameWindow.draw(debugbuttonSprite);
			gameWindow.draw(leaderboardbuttonSprite);
			gameWindow.draw(faceSprite);
			boardObj.DrawBoard(gameWindow);
			
			// Drawing the tilesrevealed when game is paused
			if ((gamePaused && !boardObj.GetgameOver() && !boardObj.GetgameWon())) {

				gameWindow.draw(playbuttonSprite);
				boardObj.drawbackgroundTiles(gameWindow);
			}

			
			gameWindow.display();
		}
	return 0;
}

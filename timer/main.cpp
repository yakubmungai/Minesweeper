///Written by Gabriela Taboada, edited by Summer Bossman.
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

///Be sure to include the "images" folder from project files and sfml if you want to run

map<int, sf::Sprite> parseDigits(sf::Sprite digits){
    map<int, sf::Sprite> digitsMap;

    for(int i = 0; i < 10; i++){
        sf::IntRect rect(i*21,0,21,32);
        digits.setTextureRect(rect);
        sf::Sprite sprite = digits;
        digitsMap.emplace(i, sprite);
    }

    return digitsMap;
}

int main() {

    sf::RenderWindow window(sf::VideoMode(300, 100), "Timer");

    auto start_time = chrono::high_resolution_clock::now();//starting the timer when the program begins to run!
    //In project 3, this(^^^) would go above the Game Window while loops, but below the Welcome Window while loops

    //Below is just for initialization, in the end, this will be overwritten, just needed to equal something. TLDR: Ignore what it equals here (below).
    auto pauseTime = chrono::high_resolution_clock::now();
    auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime).count();

    bool paused = false; //false when game in not paused, true when the game is paused

    sf::Texture& digitsText = TextureManager::getTexture("digits");
    sf::Sprite digits;
    digits.setTexture(digitsText);

    map<int, sf::Sprite> digitsMap = parseDigits(digits); //map for my digits

    sf::Texture& pauseText = TextureManager::getTexture("pause");
    sf::Sprite pauseBttn;
    pauseBttn.setTexture(pauseText);
    pauseBttn.setPosition(50, 20);

    sf::Texture& playText = TextureManager::getTexture("play");
    sf::Sprite playBttn;
    playBttn.setTexture(playText);
    playBttn.setPosition(50, 20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i vec = sf::Mouse::getPosition(window);

            if (event.type == sf::Event::Closed)
                window.close();

            else if(sf::Event::MouseButtonPressed == event.type && sf::Mouse::Left == event.key.code){
                if(pauseBttn.getGlobalBounds().contains(vec.x, vec.y)){
                    paused = !paused; //boolean changed everytime pause button is clicked

                    if(paused) {
                        cout << "paused" << endl;
                        pauseTime = chrono::high_resolution_clock::now();

                    }else{
                        //unpaused
                        auto unPausedTime = chrono::steady_clock::now();
                        elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count(); //Addition is necessary for when hitting the pause button more than once
                        //cout << elapsed_paused_time % 60 << " " << endl;
                     
                    }
                }
            }
        }
        window.clear(sf::Color::Blue); //changing the color of the window backround

        //this finds the time elapsed, so the current time - the time the window opened.
        auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
        int total_time = game_duration.count(); // necessary to subtract elapsed time later because "game_duration.count()" is const

        int minutes;
        int seconds;

        if(!paused) {
            //enters if the game is NOT paused. This is the condition that keeps the timer from incrementing when paused.
            //cout << "not paused\n";
            total_time =  total_time - elapsed_paused_time; //
            minutes = total_time / 60;
            seconds = total_time % 60;
        }

        //"separating" the integers. So.... 68 -> seconds0 = 6 and seconds1 = 8
        int minutes0 = minutes / 10 % 10; //minutes index 0
        int minutes1 = minutes % 10; // minutes index 1
        int seconds0 = seconds / 10 % 10; // seconds index 0
        int seconds1 = seconds % 10; // seconds index 1


        digitsMap[minutes0].setPosition(250 - 97, (10 + 0.5f) + 20);
        window.draw(digitsMap[minutes0]);

        digitsMap[minutes1].setPosition(250 - 76,  (10 + 0.5f) + 20);
        window.draw(digitsMap[minutes1]);

        digitsMap[seconds0].setPosition(250 - 54,  (10 + 0.5f) + 20);
        window.draw(digitsMap[seconds0]);

        digitsMap[seconds1].setPosition(250 - 33, (10 + 0.5f) + 20);
        window.draw(digitsMap[seconds1]);

        window.draw(pauseBttn);

        if(paused){
            window.draw(playBttn);
        }

        window.display();

    }
    return 0;
}

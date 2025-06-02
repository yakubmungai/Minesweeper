#pragma once
#include <random>

class Random { // Class for the randomness of the board.
public:
    // One and only one of this function.
    static int Int(int min, int max); // Gets a random integer between the inputted min and max number.
    static float Float(float min, float max); // Gets a random float between the inputted min and max number.
private:
    // One instance of the x variable, and all instances SHARE this variable.
    // Static variables/functions exist for the lifetime of your program.
    static std::mt19937 random; // Static variable for a random number.
};

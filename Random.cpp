#include "Random.h"
#include <ctime>

// Static variables must be redeclared in global space.
std::mt19937 Random::random(time(0));

int Random::Int(int min, int max) { // Gets a random integer between the inputted min and max number.
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

float Random::Float(float min, float max) { // Gets a random float between the inputted min and max number.
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}
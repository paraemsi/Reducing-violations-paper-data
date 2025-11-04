#include "dnd_character.h"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace dnd_character {

ability_score_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<ability_score_t> dis(1, 6);
    
    std::vector<ability_score_t> rolls;
    for (ability_score_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<ability_score_t>());
    
    // Sum the largest three
    ability_score_t sum = 0;
    for (ability_score_t i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

ability_score_t modifier(ability_score_t constitution) {
    // Calculate floor((constitution - 10) / 2)
    // For integer division, when the result is negative, we need to adjust
    ability_score_t diff = constitution - 10;
    if (diff >= 0) {
        return diff / 2;
    } else {
        // For negative numbers, integer division truncates towards zero, but we need floor
        // So (diff - 1) / 2 will give the correct result
        return (diff - 1) / 2;
    }
}

}  // namespace dnd_character

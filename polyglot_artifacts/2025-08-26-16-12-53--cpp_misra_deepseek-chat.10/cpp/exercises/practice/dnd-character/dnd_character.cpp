#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

namespace dnd_character {

ability_score_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<ability_score_t::value_type> dis(1, 6);
    static auto roller = [&]() { return ability_score_t(dis(gen)); };
    
    std::vector<ability_score_t> rolls;
    for (ability_score_t::value_type i = 0; i < 4; ++i) {
        rolls.push_back(roller());
    }
    
    // Sort in descending order to easily access the top 3
    std::sort(rolls.begin(), rolls.end(), [](const ability_score_t& a, const ability_score_t& b) {
        return a.value > b.value;
    });
    
    // Sum the top 3
    ability_score_t::value_type sum = 0;
    for (ability_score_t::value_type i = 0; i < 3; ++i) {
        sum += rolls[i].value;
    }
    return ability_score_t(sum);
}

ability_score_t modifier(ability_score_t constitution) {
    ability_score_t::value_type diff = (constitution.value - 10);
    // To always floor the division, we adjust for negative numbers
    if (diff >= 0) {
        return ability_score_t(diff / 2);
    } else {
        // For negative numbers, this ensures floor division
        return ability_score_t((diff - 1) / 2);
    }
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(ability_score_t(static_cast<ability_score_t::value_type>(10) + modifier(constitution).value)) {
}

}  // namespace dnd_character

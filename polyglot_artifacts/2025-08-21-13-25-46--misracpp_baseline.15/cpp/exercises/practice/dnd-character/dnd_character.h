#pragma once

#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

namespace dnd_character {

class Character {
public:
    Character();

    int strength() const;
    int dexterity() const;
    int constitution() const;
    int intelligence() const;
    int wisdom() const;
    int charisma() const;

    int hitpoints() const;
    int ability_modifier(int ability_score) const;

    // Expose ability scores as public data members for test compatibility
    // Remove public data members, only keep private

private:
    std::array<int, 6> abilities_;
    int hitpoints_;
};

int ability_modifier(int ability_score);

// Add a free function named modifier for test compatibility
inline int modifier(int ability_score) {
    return ability_modifier(ability_score);
}

// Add a free function named ability for test compatibility
inline int ability() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    std::vector<int> rolls(4);
    for (int& roll : rolls) {
        std::uniform_int_distribution<int> dist(1, 6);
        roll = dist(rng);
    }
    std::sort(rolls.begin(), rolls.end());
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

}  // namespace dnd_character

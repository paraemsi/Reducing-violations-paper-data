#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace {
    // Shared RNG for this translation unit
    std::mt19937& rng() {
        static std::mt19937 engine{std::random_device{}()};
        return engine;
    }
}

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::array<int, 4> rolls{};
    for (auto& r : rolls) {
        r = dist(rng());
    }
    std::sort(rolls.begin(), rolls.end()); // ascending
    return rolls[1] + rolls[2] + rolls[3]; // sum largest three
}

int modifier(int score) {
    int n = score - 10;
    return n >= 0 ? n / 2 : (n - 1) / 2;
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

}  // namespace dnd_character

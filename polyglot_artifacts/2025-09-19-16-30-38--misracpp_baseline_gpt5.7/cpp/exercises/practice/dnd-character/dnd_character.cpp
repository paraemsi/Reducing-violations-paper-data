#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

namespace dnd_character {

namespace {
int roll_d6(std::mt19937& gen) {
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(gen);
}
}  // namespace

int ability() {
    thread_local std::mt19937 gen(std::random_device{}());

    std::array<int, 4> rolls{};
    for (auto& r : rolls) {
        r = roll_d6(gen);
    }
    std::sort(rolls.begin(), rolls.end());  // ascending
    return rolls[1] + rolls[2] + rolls[3];  // sum highest three
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character() noexcept
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

}  // namespace dnd_character

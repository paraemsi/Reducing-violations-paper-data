#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

std::uint32_t ability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::uint32_t> dist(1, 6);

    std::array<std::uint32_t, 4> rolls;
    for (auto& r : rolls) {
        r = dist(gen);
    }
    std::sort(rolls.begin(), rolls.end(), std::greater<std::uint32_t>());
    std::uint32_t sum = (rolls[0] + rolls[1]) + rolls[2];
    return sum;
}

std::int32_t modifier(std::uint32_t score) {
    std::int32_t diff = (static_cast<std::int32_t>(score) - 10);
    std::int32_t mod = (diff / 2);
    if (((diff % 2) != 0) && (diff < 0)) {
        mod = (mod - 1);
    }
    return mod;
}

Character generate_character() {
    Character c;
    c.strength = ability();
    c.dexterity = ability();
    c.constitution = ability();
    c.intelligence = ability();
    c.wisdom = ability();
    c.charisma = ability();
    c.hitpoints = static_cast<std::uint32_t>(10 + modifier(c.constitution));
    return c;
}

}  // namespace dnd_character

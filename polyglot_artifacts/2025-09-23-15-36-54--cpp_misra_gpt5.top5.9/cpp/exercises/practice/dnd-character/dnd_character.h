#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = std::int32_t;

auto ability() -> score_t;
auto modifier(score_t score) noexcept -> score_t;

class Character {
public:
    Character();

    score_t strength;
    score_t dexterity;
    score_t constitution;
    score_t intelligence;
    score_t wisdom;
    score_t charisma;
    score_t hitpoints;
};

}  // namespace dnd_character

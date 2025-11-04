#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

// Use fixed-width types for MISRA compliance
using ability_score_t = int32_t;
using hitpoint_t = int32_t;

// Standalone modifier function as required by tests
auto modifier(ability_score_t score) -> ability_score_t;

auto ability() -> ability_score_t;

class Character {
public:
    Character();

    auto ability_strength() const -> ability_score_t;
    auto ability_dexterity() const -> ability_score_t;
    auto ability_constitution() const -> ability_score_t;
    auto ability_intelligence() const -> ability_score_t;
    auto ability_wisdom() const -> ability_score_t;
    auto ability_charisma() const -> ability_score_t;

    // Expose public data members as required by tests
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    hitpoint_t hitpoints;

private:
    std::array<ability_score_t, 6> abilities_;

    static ability_score_t roll_ability();
};

}  // namespace dnd_character

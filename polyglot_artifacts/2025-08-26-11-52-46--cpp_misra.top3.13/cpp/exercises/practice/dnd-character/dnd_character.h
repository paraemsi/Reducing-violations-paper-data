#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

#include <cmath>

using ability_score_t = ::std::int32_t;

// Standalone modifier function as required by tests
inline ability_score_t modifier(ability_score_t score) {
    // ((score - 10) / 2) rounded down
    return static_cast<ability_score_t>((score - 10) / 2);
}

// Standalone ability function as required by tests
ability_score_t ability();

class Character {
public:
    Character();

    auto strength() const -> ability_score_t;
    auto dexterity() const -> ability_score_t;
    auto constitution() const -> ability_score_t;
    auto intelligence() const -> ability_score_t;
    auto wisdom() const -> ability_score_t;
    auto charisma() const -> ability_score_t;
    auto hitpoints() const -> ability_score_t;

private:
    ::std::array<ability_score_t, 6> m_abilities;
    ability_score_t m_hitpoints;
};

}  // namespace dnd_character

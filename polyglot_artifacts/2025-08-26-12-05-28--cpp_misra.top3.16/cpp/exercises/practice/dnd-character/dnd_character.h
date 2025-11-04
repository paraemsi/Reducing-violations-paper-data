#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

using ability_score_t = std::int32_t;
using hitpoint_t = std::int32_t;

class Character {
public:
    Character();

    auto ability_strength() const -> ability_score_t;
    auto ability_dexterity() const -> ability_score_t;
    auto ability_constitution() const -> ability_score_t;
    auto ability_intelligence() const -> ability_score_t;
    auto ability_wisdom() const -> ability_score_t;
    auto ability_charisma() const -> ability_score_t;

    auto hitpoints() const -> hitpoint_t;
    static auto ability_modifier(ability_score_t score) -> ability_score_t;

private:
    std::array<ability_score_t, 6> abilities_;
    hitpoint_t hitpoints_;

    static auto roll_ability() -> ability_score_t;
};

auto modifier(ability_score_t score) -> ability_score_t;
auto ability() -> ability_score_t;

auto modifier(ability_score_t score) -> ability_score_t;
auto ability() -> ability_score_t;

}  // namespace dnd_character

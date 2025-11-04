#pragma once

#include <array>
#include <cstdint>
#include <random>
namespace dnd_character {

using ability_score_t = std::int32_t;
using hitpoint_t = std::int32_t;

// Standalone modifier function as required by tests
ability_score_t modifier(ability_score_t score);

// Standalone ability function as required by tests
ability_score_t ability();

class Character {
public:
    Character();

    ability_score_t ability_strength() const;
    ability_score_t ability_dexterity() const;
    ability_score_t ability_constitution() const;
    ability_score_t ability_intelligence() const;
    ability_score_t ability_wisdom() const;
    ability_score_t ability_charisma() const;
    hitpoint_t hitpoints() const;

    // This method is not required by the tests, but can remain for internal use
    ability_score_t ability_modifier(ability_score_t score) const;

    // Expose these as public const data members for test compatibility
    const ability_score_t& strength;
    const ability_score_t& dexterity;
    const ability_score_t& constitution;
    const ability_score_t& intelligence;
    const ability_score_t& wisdom;
    const ability_score_t& charisma;
    const hitpoint_t& hitpoints;

private:
    std::array<ability_score_t, 6U> abilities_;
    hitpoint_t hitpoints_;

    static ability_score_t roll_ability();
};

}  // namespace dnd_character

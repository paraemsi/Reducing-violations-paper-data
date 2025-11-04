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
ability_score_t ability(void);

class Character {
public:
    Character();

    ability_score_t ability_strength(void) const;
    ability_score_t ability_dexterity(void) const;
    ability_score_t ability_constitution(void) const;
    ability_score_t ability_intelligence(void) const;
    ability_score_t ability_wisdom(void) const;
    ability_score_t ability_charisma(void) const;

    hitpoint_t hitpoints(void) const;
    ability_score_t ability_modifier(ability_score_t score) const;

    // Public fields as required by tests
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    hitpoint_t hitpoints;

private:
    std::array<ability_score_t, 6> abilities_;
    hitpoint_t hitpoints_;

    static ability_score_t roll_ability(void);
    static ability_score_t calculate_modifier(ability_score_t score);
};

}  // namespace dnd_character

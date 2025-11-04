#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_score_t = std::int32_t;

/*  Generate a single ability score by rolling four six-sided dice,
 *  discarding the lowest roll and summing the remaining three.        */
ability_score_t ability();

/*  Calculate the ability modifier as ⌊(score − 10) / 2⌋.               */
ability_score_t modifier(ability_score_t score);

class Character {
public:
    Character();

    const ability_score_t strength;
    const ability_score_t dexterity;
    const ability_score_t constitution;
    const ability_score_t intelligence;
    const ability_score_t wisdom;
    const ability_score_t charisma;
    const ability_score_t hitpoints;
};

}  // namespace dnd_character

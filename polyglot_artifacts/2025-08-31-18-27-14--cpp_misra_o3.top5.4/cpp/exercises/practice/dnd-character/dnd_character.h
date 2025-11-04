#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;

/* Generate a single ability score (four d6, drop lowest). */
ability_t ability();

/* Calculate the ability modifier for a given score. */
ability_t modifier(ability_t score);

class Character {
public:
    Character();

    /* public – directly accessed by the tests */
    ability_t strength{0};
    ability_t dexterity{0};
    ability_t constitution{0};
    ability_t intelligence{0};
    ability_t wisdom{0};
    ability_t charisma{0};
    ability_t hitpoints{0};

};

}  // namespace dnd_character

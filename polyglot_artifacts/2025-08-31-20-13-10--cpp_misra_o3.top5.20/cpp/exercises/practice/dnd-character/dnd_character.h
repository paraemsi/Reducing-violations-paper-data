#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

/*  Generate a single ability score by rolling four 6-sided dice,
    discarding the lowest roll and summing the remaining three. */
[[nodiscard]] std::int32_t ability();

/*  Compute the ability modifier for a given ability score. */
[[nodiscard]] std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();

    /* ability scores */
    std::int32_t strength {0};
    std::int32_t dexterity {0};
    std::int32_t constitution {0};
    std::int32_t intelligence {0};
    std::int32_t wisdom {0};
    std::int32_t charisma {0};

    /* derived attribute */
    std::int32_t hitpoints {0};

};

} // namespace dnd_character

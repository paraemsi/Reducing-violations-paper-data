#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

/* Generate a single ability score by rolling four six–sided dice and
 * summing the largest three results. */
auto ability() -> std::int32_t;

/* Calculate the ability modifier that corresponds to a particular score.
 * The result is floor((score - 10) / 2). */
auto modifier(std::int32_t score) -> std::int32_t;

/* Representation of a D&D character with six ability scores and hit-points
 * computed from the constitution modifier. */
class Character {
public:
    Character();

    /* Ability scores are exposed as public data members because the
     * exercism tests access them directly. */
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};

    /* Hit-points derived from constitution. */
    std::int32_t hitpoints{};
};

}  // namespace dnd_character

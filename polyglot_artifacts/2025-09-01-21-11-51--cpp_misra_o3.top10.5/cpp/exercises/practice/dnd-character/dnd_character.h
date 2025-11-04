#pragma once

#include <cstdint>

namespace dnd_character {

/*
 * Character
 *
 * Generates and stores the six Dungeons & Dragons ability scores as well
 * as the derived hit-points value.
 */
class Character
{
public:
    Character();  // rolls abilities on construction

    // (modifier is provided as a free function – see below)

    /*  Public data members – tests expect direct access
     *  All are initialised in the constructor.
     */
    std::int32_t strength     {};
    std::int32_t dexterity    {};
    std::int32_t constitution {};
    std::int32_t intelligence {};
    std::int32_t wisdom       {};
    std::int32_t charisma     {};

    std::int32_t hitpoints {};
};

/*  Roll a single ability score (4d6, drop lowest, sum the rest).
 *  Declared at namespace scope because tests expect
 *  dnd_character::ability() to be available.
 */
[[nodiscard]] std::int32_t ability();

/*  Calculate the modifier for an ability score (D&D rule).
 *  Exposed at namespace scope so tests can call dnd_character::modifier().
 */
[[nodiscard]] std::int32_t modifier(std::int32_t ability_score) noexcept;

}  // namespace dnd_character

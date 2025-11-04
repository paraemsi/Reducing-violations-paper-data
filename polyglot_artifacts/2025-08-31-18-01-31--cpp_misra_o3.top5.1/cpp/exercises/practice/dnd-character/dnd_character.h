#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

class Character
{
public:
    Character();

    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};

    std::int32_t hitpoints{};
};

/*  Compute the ability modifier (namespace-level, not a class member). */
std::int32_t modifier(std::int32_t ability_score) noexcept;

/*  Generate a single ability score (4d6, drop the lowest). */
std::int32_t ability() noexcept;

}  // namespace dnd_character

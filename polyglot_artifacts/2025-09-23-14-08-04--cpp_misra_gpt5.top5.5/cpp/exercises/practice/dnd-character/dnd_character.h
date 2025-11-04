#pragma once

#include <cstdint>

namespace dnd_character {

 // Compute the ability modifier from an ability score.
 // Modifier is floor((score - 10) / 2).
[[nodiscard]] constexpr auto modifier(std::int32_t score) noexcept -> std::int32_t {
    return ((score / 2) - 5);
}

// Roll four six-sided dice and sum the highest three.
[[nodiscard]] auto ability() -> std::int32_t;

class Character {
public:
    Character();

    std::int32_t strength{0};
    std::int32_t dexterity{0};
    std::int32_t constitution{0};
    std::int32_t intelligence{0};
    std::int32_t wisdom{0};
    std::int32_t charisma{0};
    std::int32_t hitpoints{0};
};

}  // namespace dnd_character

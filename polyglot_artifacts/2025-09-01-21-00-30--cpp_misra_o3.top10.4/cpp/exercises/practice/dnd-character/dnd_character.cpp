#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {

// Roll one six-sided die (1-6)
std::int32_t roll_die()
{
    static std::random_device rd;
    static std::mt19937 engine{ rd() };
    static std::uniform_int_distribution<std::int32_t> dist(1, 6);
    return dist(engine);
}

}  // unnamed namespace

std::int32_t ability()
{
    std::array<std::int32_t, 4U> rolls{};
    for (auto & value : rolls) {
        value = roll_die();
    }

    (void)std::sort(rolls.begin(), rolls.end());

    const std::int32_t sum_of_top_three =
        std::accumulate(rolls.begin() + 1U, rolls.end(), static_cast<std::int32_t>(0));

    return sum_of_top_three;
}

std::int32_t modifier(std::int32_t score)
{
    /*  Calculate the ability modifier as:
     *      floor((score - 10) / 2)
     *
     *  Because C++ integer division truncates toward zero, negative odd
     *  numerators need an extra ‑1 adjustment to achieve the required
     *  “round toward −∞” behaviour.
     */
    const std::int32_t diff =
        score - static_cast<std::int32_t>(10);

    const bool needs_adjust =
        ((diff < static_cast<std::int32_t>(0)) &&
         ((diff % static_cast<std::int32_t>(2)) != static_cast<std::int32_t>(0)));

    return (diff / static_cast<std::int32_t>(2)) -
           (needs_adjust ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(0));
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(static_cast<std::int32_t>(10) + modifier(constitution))
{
}


}  // namespace dnd_character

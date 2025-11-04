#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
/*  One engine & distribution shared by all rolls.
    The fixed range [1,6] models a standard 6-sided die. */
std::random_device                                   rd;
std::mt19937                                          engine(rd());
std::uniform_int_distribution<std::int32_t>           dice_dist(1, 6);
} // namespace

/*  Free-function versions matching the public interface. */
[[nodiscard]] std::int32_t ability()
{
    std::array<std::int32_t, 4U> rolls {};
    for (std::int32_t & roll : rolls) {
        roll = dice_dist(engine);
    }

    const auto min_it = std::min_element(rolls.cbegin(), rolls.cend());
    std::int32_t total = std::accumulate(rolls.cbegin(),
                                         rolls.cend(),
                                         static_cast<std::int32_t>(0));
    total = total - (*min_it);
    return total;
}

[[nodiscard]] std::int32_t modifier(std::int32_t score)
{
    const std::int32_t diff {score - 10};
    if (diff >= 0) {
        return diff / 2;
    } else {
        return (diff - 1) / 2; /* floor toward -∞ for negatives */
    }
}



Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution))
{
}


} // namespace dnd_character

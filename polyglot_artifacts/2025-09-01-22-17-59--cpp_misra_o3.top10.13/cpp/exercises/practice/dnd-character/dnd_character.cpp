#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <random>

namespace {

// Roll one die with inclusive range [min, max]
[[nodiscard]] score_t roll_die(score_t min, score_t max)
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::mt19937 s_engine {std::random_device {}()};
    std::uniform_int_distribution<score_t> dist(min, max);
    return dist(s_engine);
}

}  // unnamed namespace

namespace dnd_character {

score_t ability()
{
    std::array<score_t, 4U> rolls {};
    for(std::uint32_t i {0U}; i < 4U; ++i)
    {
        rolls[i] = roll_die(1, 6);
    }

    const auto  min_it = std::min_element(rolls.begin(), rolls.end());
    const score_t sum_best_three =
        std::accumulate(rolls.begin(),
                        rolls.end(),
                        static_cast<score_t>(0)) - *min_it;

    return sum_best_three;
}

score_t modifier(score_t score)
{
    const score_t delta {score - static_cast<score_t>(10)};
    score_t       result {delta / static_cast<score_t>(2)};

    if((delta < static_cast<score_t>(0)) &&
       ((delta % static_cast<score_t>(2)) != static_cast<score_t>(0)))
    {
        --result;  // ensure floor division for negatives
    }

    return result;
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(static_cast<score_t>(10) + modifier(constitution))
{
}








}  // namespace dnd_character

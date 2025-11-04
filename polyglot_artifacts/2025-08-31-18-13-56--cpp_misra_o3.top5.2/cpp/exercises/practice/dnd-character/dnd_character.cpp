#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <functional>

namespace {

/* Create and seed a Mersenne Twister engine once for the entire program. */
auto make_random_engine() -> std::mt19937 {
    std::random_device rd{};
    std::array<std::uint32_t, std::mt19937::state_size> seed_data{};
    std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
    std::seed_seq seq(seed_data.begin(), seed_data.end());
    return std::mt19937{seq};
}

static std::mt19937 rng{make_random_engine()};

}  // unnamed namespace

namespace dnd_character {

auto ability() -> std::int32_t
{
    std::uniform_int_distribution<std::int32_t> dist(1, 6);

    std::array<std::int32_t, 4> rolls{};
    for (std::int32_t & r : rolls) {
        r = dist(rng);
    }

    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());

    /* Sum of the three highest rolls. */
    return static_cast<std::int32_t>(rolls[0] + rolls[1] + rolls[2]);
}

auto modifier(std::int32_t score) -> std::int32_t
{
    const std::int32_t diff{score - static_cast<std::int32_t>(10)};
    std::int32_t mod{diff / static_cast<std::int32_t>(2)};

    if ((diff < static_cast<std::int32_t>(0)) &&
        ((diff % static_cast<std::int32_t>(2)) != static_cast<std::int32_t>(0))) {
        --mod;
    }
    return mod;
}

/* ----- Character implementation --------------------------------------- */

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{static_cast<std::int32_t>(
          static_cast<std::int32_t>(10) + modifier(constitution))}
{
}


}  // namespace dnd_character

#include "dnd_character.h"

#include <algorithm>
#include <random>
#include <cstddef>

namespace dnd_character {

namespace {
/*  Obtain a thread-local pseudo-random number generator. */
inline auto rng() -> std::mt19937& {
    static thread_local std::random_device rd {};
    static thread_local std::mt19937 gen { rd() };
    return gen;
}
}  // unnamed namespace

auto ability() -> ability_t {
    std::array<ability_t, 4U> rolls {};
    std::uniform_int_distribution<ability_t> dist { static_cast<ability_t>(1),
                                                    static_cast<ability_t>(6) };

    for (ability_t& die : rolls) {
        die = dist(rng());
    }

    const ability_t lowest_value =
        *std::min_element(rolls.begin(), rolls.end());

    ability_t sum { static_cast<ability_t>(0) };
    for (const ability_t value : rolls) {
        sum = static_cast<ability_t>(sum + value);
    }

    return static_cast<ability_t>(sum - lowest_value);
}

auto modifier(ability_t score) -> ability_t {
    const ability_t diff { static_cast<ability_t>(score - static_cast<ability_t>(10)) };
    ability_t mod { static_cast<ability_t>(diff / static_cast<ability_t>(2)) };

    /*  If diff is negative and odd, integer division rounded toward zero
        is one too high; adjust downward to obtain floor-division. */
    if ((diff < static_cast<ability_t>(0)) &&
        ((diff % static_cast<ability_t>(2)) != static_cast<ability_t>(0))) {
        mod = static_cast<ability_t>(mod - static_cast<ability_t>(1));
    }
    return mod;
}

auto abilities() -> std::array<ability_t, 6U> {
    std::array<ability_t, 6U> result {};
    for (ability_t& score : result) {
        score = ability();
    }
    return result;
}

/* ===== Character ======================================================= */

Character::Character()
    : strength { ability() },
      dexterity { ability() },
      constitution { ability() },
      intelligence { ability() },
      wisdom { ability() },
      charisma { ability() },
      hitpoints{
          static_cast<ability_t>(10) +
          modifier(constitution)
      } {
}








}  // namespace dnd_character

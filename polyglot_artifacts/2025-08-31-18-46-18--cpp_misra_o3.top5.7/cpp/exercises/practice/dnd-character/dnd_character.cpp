#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace {
// single engine & distribution reused to avoid expensive re-seeding
std::random_device seed_device_;
std::mt19937 engine_{seed_device_()};
std::uniform_int_distribution<std::int32_t> die_dist_{1, 6};

std::int32_t roll_die()
{
    return die_dist_(engine_);
}
}  // unnamed namespace

std::int32_t ability()
{
    std::array<std::int32_t, 4U> rolls{};
    for (std::int32_t &value : rolls) {
        value = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    return static_cast<std::int32_t>(rolls[1] + rolls[2] + rolls[3]);
}

std::int32_t modifier(std::int32_t score)
{
    const std::int32_t diff{static_cast<std::int32_t>(score - 10)};

    if (diff >= 0) {
        return diff / 2;
    } else {
        /* For negative odd values ensure mathematical floor behaviour */
        return (diff - 1) / 2;
    }
}

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{static_cast<std::int32_t>(10 + modifier(constitution))}
{
}


}  // namespace dnd_character

#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
/*
 * Roll a single die that yields an integer in the inclusive range [min, max].
 */
std::int32_t roll_die(std::int32_t min, std::int32_t max)
{
    static std::random_device rd {};
    static std::mt19937 engine { rd() };
    std::uniform_int_distribution<std::int32_t> dist(min, max);
    return dist(engine);
}
}  // unnamed namespace

std::int32_t ability()
{
    std::array<std::int32_t, 4U> rolls {};
    for (std::int32_t & value : rolls) {
        value = roll_die(1, 6);
    }
    std::sort(rolls.begin(), rolls.end());
    /*  parenthesise sub-expression (rolls.begin() + 1) per MISRA precedence rule  */
    const std::int32_t sum =
        std::accumulate((rolls.begin() + 1), rolls.end(), static_cast<std::int32_t>(0));
    return sum;
}

std::int32_t modifier(const std::int32_t score)
{
    const std::int32_t diff = (score - 10);
    std::int32_t mod = diff / 2;
    if ((diff < 0) && ((diff % 2) != 0)) {
        --mod;
    }
    return mod;
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<std::int32_t>(10) + modifier(constitution))
{
}

}  // namespace dnd_character

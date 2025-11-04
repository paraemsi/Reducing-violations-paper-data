#include "dnd_character.h"

#include <cstdint>
#include <random>

namespace dnd_character {

namespace {

// Roll a single six-sided die.
auto roll_d6() -> std::int32_t
{
    static std::random_device rd{};
    using engine_type = std::mt19937;
    static engine_type eng{static_cast<engine_type::result_type>(rd())};
    static std::uniform_int_distribution<std::int32_t> dist(static_cast<std::int32_t>(1), static_cast<std::int32_t>(6));
    return dist(eng);
}

auto ability_roll() -> std::int32_t
{
    const std::int32_t a = roll_d6();
    const std::int32_t b = roll_d6();
    const std::int32_t c = roll_d6();
    const std::int32_t d = roll_d6();

    const std::int32_t min_ab = ((a < b) ? a : b);
    const std::int32_t min_cd = ((c < d) ? c : d);
    const std::int32_t min_all = ((min_ab < min_cd) ? min_ab : min_cd);

    const std::int32_t sum_all = ((a + b) + (c + d));
    const std::int32_t top3 = (sum_all - min_all);

    return top3;
}

}  // unnamed namespace

auto ability() -> std::int32_t
{
    return ability_roll();
}

auto modifier(std::int32_t score) -> std::int32_t
{
    const std::int32_t ten = static_cast<std::int32_t>(10);
    const std::int32_t two = static_cast<std::int32_t>(2);
    const std::int32_t delta = (score - ten);

    if (((delta < static_cast<std::int32_t>(0))) && (((delta % two) != static_cast<std::int32_t>(0)))) {
        return ((delta - static_cast<std::int32_t>(1)) / two);
    } else {
        return (delta / two);
    }
}

Character::Character()
    : strength{ability()}
    , dexterity{ability()}
    , constitution{ability()}
    , intelligence{ability()}
    , wisdom{ability()}
    , charisma{ability()}
    , hitpoints{(static_cast<std::int32_t>(10) + modifier(constitution))}
{
}

}  // namespace dnd_character

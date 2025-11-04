#include "dnd_character.h"

#include <random>

namespace dnd_character {

namespace {
// Pseudo-random generator (thread-local) seeded once per thread
std::mt19937& rng()
{
    static thread_local std::mt19937 engine{ std::random_device{}() };
    return engine;
}

dnd_character::i32 roll_die6()
{
    static thread_local std::uniform_int_distribution<dnd_character::i32> dist(
        static_cast<dnd_character::i32>(1),
        static_cast<dnd_character::i32>(6));
    return dist(rng());
}

// Floor division by 2 for all integers without using floating point
dnd_character::i32 floor_div2(dnd_character::i32 a)
{
    return ((a - ((a < static_cast<dnd_character::i32>(0)) ? static_cast<dnd_character::i32>(1) : static_cast<dnd_character::i32>(0)))
        / static_cast<dnd_character::i32>(2));
}
}  // namespace

dnd_character::i32 ability()
{
    i32 total = static_cast<i32>(0);
    i32 minv = static_cast<i32>(6);

    for (i32 i = static_cast<i32>(0); (i < static_cast<i32>(4)); i = (i + static_cast<i32>(1))) {
        i32 die = roll_die6();
        total = (total + die);
        if ((die < minv)) {
            minv = die;
        }
    }

    return (total - minv);
}

dnd_character::i32 modifier(dnd_character::i32 score)
{
    i32 diff = (score - static_cast<i32>(10));
    return floor_div2(diff);
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints((static_cast<i32>(10) + modifier(constitution)))
{
}

}  // namespace dnd_character

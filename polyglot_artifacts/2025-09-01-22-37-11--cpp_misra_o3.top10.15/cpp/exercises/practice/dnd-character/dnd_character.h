#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

namespace dnd_character {

/*  Fixed-width signed integer type used throughout the interface to
 *  comply with MISRA C++ rules that forbid usage of the built-in
 *  signed/unsigned integer names.
 */
using Score = std::int32_t;

/*  Roll four six-sided dice, drop the lowest roll and return the sum
 *  of the remaining three ‑ this is a single D&D ability score.
 */
auto ability() -> Score;

/*  Calculate the ability modifier as floor((score − 10) / 2). */
auto modifier(Score score) -> Score;

/*  A randomly generated D&D character. */
class Character {
public:
    Character();

    /*  Ability scores and derived hit-points are exposed as public
     *  data members to satisfy the test-suite interface. They are
     *  declared const to prevent accidental modification once the
     *  character has been generated.
     */
    const Score strength;
    const Score dexterity;
    const Score constitution;
    const Score intelligence;
    const Score wisdom;
    const Score charisma;
    const Score hitpoints;
};

}  // namespace dnd_character

#include "dnd_character.h"

#include <algorithm>
#include <random>

namespace dnd_character {

//  Random engine – one per translation unit.
namespace {
    auto make_rng() -> std::mt19937 {
        std::random_device rd{};
        //  Using deterministic seed would simplify testing, but the
        //  exercise expects true randomness.
        return std::mt19937{ rd() };
    }

    std::mt19937 rng{ make_rng() };
}   // unnamed namespace

auto ability() -> ability_score_t
{
    std::uniform_int_distribution<ability_score_t> dist{ 1, 6 };

    std::array<ability_score_t, 4U> rolls{};
    for (auto & value : rolls) {
        value = dist(rng);
    }

    std::sort(rolls.begin(), rolls.end());

    //  Sum the highest three values (indices 1,2,3 after sort)
    const ability_score_t sum_top_three{
        (rolls[1] + rolls[2]) + rolls[3]
    };

    return sum_top_three;
}

auto abilities() -> std::array<ability_score_t, 6U>
{
    std::array<ability_score_t, 6U> result{};
    for (auto & score : result) {
        score = ability();
    }
    return result;
}

auto ability_modifier(const ability_score_t score) -> ability_score_t
{
    const ability_score_t diff{ score - static_cast<ability_score_t>(10) };
    /*  Integer division of negative numbers truncates toward zero,
        therefore subtract one before dividing to realise floor() when
        the dividend is negative. */
    if (diff >= static_cast<ability_score_t>(0)) {
        return diff / static_cast<ability_score_t>(2);
    } else {
        return (diff - static_cast<ability_score_t>(1)) / static_cast<ability_score_t>(2);
    }
}

/*  Wrapper required by the supplied tests – delegates to the implementation
    above. */
auto modifier(const ability_score_t score) -> ability_score_t
{
    return ability_modifier(score);
}

/* ---- Character -------------------------------------------------------- */
Character::Character()
{
    const auto scores{ abilities() };

    strength      = scores[0];
    dexterity     = scores[1];
    constitution  = scores[2];
    intelligence  = scores[3];
    wisdom        = scores[4];
    charisma      = scores[5];

    const ability_score_t base_hp{ static_cast<ability_score_t>(10) };
    hitpoints = base_hp + modifier(constitution);
}








}   // namespace dnd_character

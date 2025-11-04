#include "dnd_character.h"

namespace dnd_character {

namespace
{
    constexpr std::size_t NUM_ABILITIES = 6U;
    constexpr std::size_t DICE_PER_ABILITY = 4U;
    constexpr std::size_t DICE_SIDES = 6U;

    using std::array;
    using std::int32_t;

    // Roll a single 6-sided die
    int32_t roll_die(std::mt19937& rng)
    {
        std::uniform_int_distribution<int32_t> dist(1, static_cast<int32_t>(DICE_SIDES));
        return dist(rng);
    }

    // Roll 4d6, drop the lowest, sum the rest
    int32_t roll_ability(std::mt19937& rng)
    {
        array<int32_t, DICE_PER_ABILITY> rolls{};
        for(std::size_t i = 0U; i < DICE_PER_ABILITY; ++i)
        {
            rolls[i] = roll_die(rng);
        }

        // Find the lowest roll
        std::size_t min_index = 0U;
        for(std::size_t i = 1U; i < DICE_PER_ABILITY; ++i)
        {
            if(rolls[i] < rolls[min_index])
            {
                min_index = i;
            }
        }

        // Sum all except the lowest
        int32_t sum = 0;
        for(std::size_t i = 0U; i < DICE_PER_ABILITY; ++i)
        {
            if(i != min_index)
            {
                sum = (sum + rolls[i]);
            }
        }
        return sum;
    }
}

dnd_character::ability_score_t dnd_character::ability()
{
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    return static_cast<ability_score_t>(::roll_ability(rng));
}

int dnd_character::modifier(dnd_character::ability_score_t score)
{
    // ((score - 10) / 2), rounded down
    return static_cast<int>((score - 10) / 2);
}

dnd_character::character dnd_character::generate_character()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    ::std::array<ability_score_t, NUM_ABILITIES> abilities{};

    for(std::size_t i = 0U; i < NUM_ABILITIES; ++i)
    {
        abilities[i] = static_cast<ability_score_t>(::roll_ability(rng));
    }

    int con_mod = modifier(abilities[2]);
    hitpoint_t hp = static_cast<hitpoint_t>(10 + con_mod);

    character c{abilities, hp};
    return c;
}

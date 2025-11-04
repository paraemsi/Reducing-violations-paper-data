#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

//  ---------------------------------------------------------------------------
//  Helpers – dice rolling and ability / modifier calculations
//  ---------------------------------------------------------------------------

[[nodiscard]] auto ability() -> Score
{
    // 4d6, drop the lowest
    static thread_local std::mt19937 engine { std::random_device {}() };
    std::uniform_int_distribution<Score> dist(static_cast<Score>(1), static_cast<Score>(6));

    std::array<Score, 4> rolls {};
    for (Score& r : rolls)
    {
        r = dist(engine);
    }

    std::sort(rolls.begin(), rolls.end());

    // Keep the highest three
    return (rolls[1] + rolls[2]) + rolls[3];
}

[[nodiscard]] auto modifier(const Score score) -> Score
{
    const Score diff { score - static_cast<Score>(10) };
    Score       mod  { diff / static_cast<Score>(2) };

    if ((diff < static_cast<Score>(0)) && ((diff % static_cast<Score>(2)) != static_cast<Score>(0)))
    {
        --mod;
    }
    return mod;
}

//  ---------------------------------------------------------------------------
//  Character implementation
//  ---------------------------------------------------------------------------

Character::Character()
{
    strength     = ability();
    dexterity    = ability();
    constitution = ability();
    intelligence = ability();
    wisdom       = ability();
    charisma     = ability();

    hitpoints = static_cast<Score>(10) + modifier(this->constitution);
}


} // namespace dnd_character

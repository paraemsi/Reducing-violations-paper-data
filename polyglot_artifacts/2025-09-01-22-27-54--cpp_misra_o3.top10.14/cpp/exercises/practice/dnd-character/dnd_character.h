#pragma once

#include <cstdint>

namespace dnd_character {

//  ---------------------------------------------------------------------------
//  Type aliases
//  ---------------------------------------------------------------------------

using Score = std::int32_t;

//  ---------------------------------------------------------------------------
//  Forward declarations
//  ---------------------------------------------------------------------------

[[nodiscard]] auto ability() -> Score;
[[nodiscard]] auto modifier(Score score) -> Score;

//  ---------------------------------------------------------------------------
//  Character – represents a complete D&D character
//  ---------------------------------------------------------------------------

class Character
{
public:
    Character();

    //  Ability scores (public for direct test access)
    Score strength     { static_cast<Score>(0) };
    Score dexterity    { static_cast<Score>(0) };
    Score constitution { static_cast<Score>(0) };
    Score intelligence { static_cast<Score>(0) };
    Score wisdom       { static_cast<Score>(0) };
    Score charisma     { static_cast<Score>(0) };

    //  Derived attribute
    Score hitpoints    { static_cast<Score>(0) };
};

} // namespace dnd_character

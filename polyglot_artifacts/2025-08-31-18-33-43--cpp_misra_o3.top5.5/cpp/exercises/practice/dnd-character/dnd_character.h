#pragma once

#include <cstdint>

namespace dnd_character {

// Fixed-width signed integer alias for all arithmetic in this module
using score_t = std::int32_t;

class Character {
public:
    Character();                                // generate all abilities on construction

    static score_t ability();                   // generate a single ability score
    static score_t modifier(score_t ability);   // calculate ability modifier

    // Public ability scores generated on construction
    score_t strength{};
    score_t dexterity{};
    score_t constitution{};
    score_t intelligence{};
    score_t wisdom{};
    score_t charisma{};

    score_t hitpoints{};                        // 10 + constitution modifier
};

// free helpers kept for compatibility with common test-suites
score_t ability();
score_t modifier(score_t ability);

}  // namespace dnd_character

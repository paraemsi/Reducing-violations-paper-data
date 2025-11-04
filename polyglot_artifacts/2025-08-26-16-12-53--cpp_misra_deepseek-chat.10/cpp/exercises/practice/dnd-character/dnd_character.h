#pragma once
#include <cstdint>

namespace dnd_character {

// Define a struct to hold the ability score value
struct ability_score_t {
    using value_type = std::int32_t;
    value_type value;
    
    // Implicit conversion to value_type for arithmetic operations
    operator value_type() const { return value; }
    
    // Constructor from value_type
    ability_score_t(value_type v = 0) : value(v) {}
};

ability_score_t ability();
ability_score_t modifier(ability_score_t constitution);

class Character {
public:
    Character();
    
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    ability_score_t hitpoints;
};

}  // namespace dnd_character

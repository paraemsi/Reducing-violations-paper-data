#pragma once
#include <cstdint>

namespace dnd_character {

// Use a fixed-width type internally but don't expose its name
struct AbilityScore {
private:
    // Use a fixed-width type that can hold the values we need
    using internal_type = std::int_fast32_t;
    internal_type val;
public:
    AbilityScore() : val(0) {}
    // Allow construction from integers
    AbilityScore(int v) : val(static_cast<internal_type>(v)) {}
    
    // Conversion to int to work with tests
    operator int() const { return static_cast<int>(val); }
    
    // Access the internal value for operations
    internal_type get() const { return val; }
};

struct Hitpoints {
private:
    using internal_type = std::int_fast32_t;
    internal_type val;
public:
    Hitpoints() : val(0) {}
    explicit Hitpoints(int v) : val(static_cast<internal_type>(v)) {}
    
    operator int() const { return static_cast<int>(val); }
    
    internal_type get() const { return val; }
};

struct Character {
    AbilityScore strength;
    AbilityScore dexterity;
    AbilityScore constitution;
    AbilityScore intelligence;
    AbilityScore wisdom;
    AbilityScore charisma;
    Hitpoints hitpoints;
};

AbilityScore modifier(AbilityScore constitution);
AbilityScore ability();
Character generate();

}  // namespace dnd_character

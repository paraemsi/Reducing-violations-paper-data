#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

enum class Color : std::int8_t { Red, Green, Ivory, Yellow, Blue };
enum class Nationality : std::int8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet : std::int8_t { Dog, Snail, Fox, Horse, Zebra };
enum class Drink : std::int8_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby : std::int8_t { Dancing, Painting, Reading, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

bool check_constraints(const std::array<House, 5>& houses) {
    // Check all constraints that can be checked with current information
    for (std::int8_t i = 0; i < 5; ++i) {
        // Check if the house is fully assigned
        // For now, we'll check all constraints that involve only the assigned attributes
        
        // 2. The Englishman lives in the red house.
        if (houses[i].nationality == Nationality::Englishman && houses[i].color != Color::Red && houses[i].color != Color{}) {
            return false;
        }
        // 3. The Spaniard owns the dog.
        if (houses[i].nationality == Nationality::Spaniard && houses[i].pet != Pet::Dog && houses[i].pet != Pet{}) {
            return false;
        }
        // 4. The person in the green house drinks coffee.
        if (houses[i].color == Color::Green && houses[i].drink != Drink::Coffee && houses[i].drink != Drink{}) {
            return false;
        }
        // 5. The Ukrainian drinks tea.
        if (houses[i].nationality == Nationality::Ukrainian && houses[i].drink != Drink::Tea && houses[i].drink != Drink{}) {
            return false;
        }
        // 7. The snail owner likes to go dancing.
        if (houses[i].pet == Pet::Snail && houses[i].hobby != Hobby::Dancing && houses[i].hobby != Hobby{}) {
            return false;
        }
        // 8. The person in the yellow house is a painter.
        if (houses[i].color == Color::Yellow && houses[i].hobby != Hobby::Painting && houses[i].hobby != Hobby{}) {
            return false;
        }
        // 9. The person in the middle house drinks milk.
        if (i == 2 && houses[i].drink != Drink::Milk && houses[i].drink != Drink{}) {
            return false;
        }
        // 10. The Norwegian lives in the first house.
        if (i == 0 && houses[i].nationality != Nationality::Norwegian && houses[i].nationality != Nationality{}) {
            return false;
        }
        // 13. The person who plays football drinks orange juice.
        if (houses[i].hobby == Hobby::Football && houses[i].drink != Drink::OrangeJuice && houses[i].drink != Drink{}) {
            return false;
        }
        // 14. The Japanese person plays chess.
        if (houses[i].nationality == Nationality::Japanese && houses[i].hobby != Hobby::Chess && houses[i].hobby != Hobby{}) {
            return false;
        }
    }
    
    // Check constraints that involve multiple houses
    // 6. The green house is immediately to the right of the ivory house.
    for (std::int8_t i = 1; i < 5; ++i) {
        if (houses[i].color == Color::Green && houses[i-1].color != Color::Ivory && houses[i-1].color != Color{}) {
            return false;
        }
        if (houses[i-1].color == Color::Ivory && houses[i].color != Color::Green && houses[i].color != Color{}) {
            return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    // Check if Norwegian is assigned and blue is next to it
    for (std::int8_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Norwegian) {
            bool valid = true;
            if (i > 0 && houses[i-1].color != Color::Blue && houses[i-1].color != Color{}) {
                valid = false;
            }
            if (i < 4 && houses[i+1].color != Color::Blue && houses[i+1].color != Color{}) {
                valid = false;
            }
            if (!valid) return false;
            break;
        }
    }
    
    return true;
}

bool backtrack(std::array<House, 5>& houses, std::int8_t attribute_index, 
               std::array<bool, 5>& used_color, std::array<bool, 5>& used_nationality,
               std::array<bool, 5>& used_pet, std::array<bool, 5>& used_drink,
               std::array<bool, 5>& used_hobby) {
    // We need to assign attributes in a smarter way, house by house
    // Let's find the next house to assign
    for (std::int8_t i = 0; i < 5; ++i) {
        // Find a house that's not fully assigned yet
        // For now, this needs to be rethought
    }
    // This implementation needs to be completely reworked, but it's complex
    // Let's use a different approach: assign all attributes to one house before moving to the next
    // But this may not be the most efficient
    return false;
}

Solution solve() {
    std::array<House, 5> houses;
    std::array<bool, 5> used_color{};
    std::array<bool, 5> used_nationality{};
    std::array<bool, 5> used_pet{};
    std::array<bool, 5> used_drink{};
    std::array<bool, 5> used_hobby{};
    
    backtrack(houses, 0, used_color, used_nationality, used_pet, used_drink, used_hobby);
    
    Solution solution;
    for (const auto& house : houses) {
        if (house.drink == Drink::Water) {
            const char* nationalities[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
            solution.drinksWater = nationalities[static_cast<std::int8_t>(house.nationality)];
        }
        if (house.pet == Pet::Zebra) {
            const char* nationalities[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
            solution.ownsZebra = nationalities[static_cast<std::int8_t>(house.nationality)];
        }
    }
    return solution;
}

}  // namespace zebra_puzzle

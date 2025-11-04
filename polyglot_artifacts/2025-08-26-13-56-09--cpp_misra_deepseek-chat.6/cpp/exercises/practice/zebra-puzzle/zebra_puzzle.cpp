#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace zebra_puzzle {

enum class Nationality : std::int8_t {
    Englishman,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};

enum class Color : std::int8_t {
    Red,
    Green,
    Ivory,
    Yellow,
    Blue
};

enum class Drink : std::int8_t {
    Coffee,
    Tea,
    Milk,
    OrangeJuice,
    Water
};

enum class Pet : std::int8_t {
    Dog,
    Snails,
    Fox,
    Horse,
    Zebra
};

enum class Hobby : std::int8_t {
    Dancing,
    Painting,
    Reading,
    Football,
    Chess
};

struct House {
    Nationality nationality;
    Color color;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

bool is_valid(const std::array<House, 5>& houses, std::int8_t index) {
    const House& h = houses[index];
    
    // Check constraints that involve only the current house
    // 2. The Englishman lives in the red house.
    if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
    // 3. The Spaniard owns the dog.
    if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
    // 4. The person in the green house drinks coffee.
    if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
    // 5. The Ukrainian drinks tea.
    if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
    // 8. The person in the yellow house is a painter.
    if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
    // 9. The person in the middle house drinks milk.
    if (index == 2 && h.drink != Drink::Milk) return false;
    // 10. The Norwegian lives in the first house.
    if (index == 0 && h.nationality != Nationality::Norwegian) return false;
    // 13. The person who plays football drinks orange juice.
    if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
    // 14. The Japanese person plays chess.
    if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
    // 7. The snail owner likes to go dancing.
    if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
    
    // Check constraints that involve relationships between houses
    for (std::int8_t i = 0; i <= index; ++i) {
        // 6. The green house is immediately to the right of the ivory house.
        // We can only check this if both houses are assigned
        if (i > 0) {
            if (houses[i].color == Color::Green && houses[i-1].color != Color::Ivory) return false;
            if (houses[i-1].color == Color::Green && houses[i].color != Color::Ivory) return false;
        }
        // 15. The Norwegian lives next to the blue house.
        if (houses[i].nationality == Nationality::Norwegian) {
            bool valid = false;
            if (i > 0 && houses[i-1].color == Color::Blue) valid = true;
            if (i < index && houses[i+1].color == Color::Blue) valid = true;
            // If we're still assigning and the next house isn't set yet, we can't be sure it's invalid
            if (i == index && index < 4) valid = true;
            if (!valid) return false;
        }
        // 11. The person who enjoys reading lives in the house next to the person with the fox.
        // Check if both are set
        if (houses[i].hobby == Hobby::Reading) {
            bool valid = false;
            if (i > 0 && houses[i-1].pet == Pet::Fox) valid = true;
            if (i < index && houses[i+1].pet == Pet::Fox) valid = true;
            // If adjacent houses aren't set yet, we can't be sure it's invalid
            if (i == index && (index > 0 || index < 4)) valid = true;
            if (!valid) return false;
        }
        // 12. The painter's house is next to the house with the horse.
        if (houses[i].hobby == Hobby::Painting) {
            bool valid = false;
            if (i > 0 && houses[i-1].pet == Pet::Horse) valid = true;
            if (i < index && houses[i+1].pet == Pet::Horse) valid = true;
            // If adjacent houses aren't set yet, we can't be sure it's invalid
            if (i == index && (index > 0 || index < 4)) valid = true;
            if (!valid) return false;
        }
    }
    return true;
}

bool solve_impl(std::array<House, 5>& houses, std::int8_t index, 
                std::array<bool, 5>& used_nat, std::array<bool, 5>& used_col,
                std::array<bool, 5>& used_drink, std::array<bool, 5>& used_pet,
                std::array<bool, 5>& used_hobby) {
    if (index == 5) {
        // Check all constraints that involve relationships between all houses
        // For now, we can rely on is_valid checks during assignment
        return true;
    }
    
    // Try all possible assignments for the current index
    for (std::int8_t nat = 0; nat < 5; ++nat) {
        if (used_nat[nat]) continue;
        houses[index].nationality = static_cast<Nationality>(nat);
        used_nat[nat] = true;
        for (std::int8_t col = 0; col < 5; ++col) {
            if (used_col[col]) continue;
            houses[index].color = static_cast<Color>(col);
            used_col[col] = true;
            for (std::int8_t drink = 0; drink < 5; ++drink) {
                if (used_drink[drink]) continue;
                houses[index].drink = static_cast<Drink>(drink);
                used_drink[drink] = true;
                for (std::int8_t pet = 0; pet < 5; ++pet) {
                    if (used_pet[pet]) continue;
                    houses[index].pet = static_cast<Pet>(pet);
                    used_pet[pet] = true;
                    for (std::int8_t hobby = 0; hobby < 5; ++hobby) {
                        if (used_hobby[hobby]) continue;
                        houses[index].hobby = static_cast<Hobby>(hobby);
                        used_hobby[hobby] = true;
                        
                        if (is_valid(houses, index)) {
                            if (solve_impl(houses, index + 1, used_nat, used_col, used_drink, used_pet, used_hobby)) {
                                return true;
                            }
                        }
                        
                        used_hobby[hobby] = false;
                    }
                    used_pet[pet] = false;
                }
                used_drink[drink] = false;
            }
            used_col[col] = false;
        }
        used_nat[nat] = false;
    }
    return false;
}

Solution solve() {
    std::array<House, 5> houses{};
    std::array<bool, 5> used_nat{};
    std::array<bool, 5> used_col{};
    std::array<bool, 5> used_drink{};
    std::array<bool, 5> used_pet{};
    std::array<bool, 5> used_hobby{};
    
    solve_impl(houses, 0, used_nat, used_col, used_drink, used_pet, used_hobby);
    
    // Find the answers
    Solution solution;
    const std::array<std::string, 5> nationalities = {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };
    
    for (const auto& house : houses) {
        if (house.drink == Drink::Water) {
            solution.drinksWater = nationalities[static_cast<int>(house.nationality)];
        }
        if (house.pet == Pet::Zebra) {
            solution.ownsZebra = nationalities[static_cast<int>(house.nationality)];
        }
    }
    return solution;
}

}  // namespace zebra_puzzle

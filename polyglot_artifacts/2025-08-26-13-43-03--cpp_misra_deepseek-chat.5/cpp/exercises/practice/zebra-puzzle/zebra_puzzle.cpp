#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>
#include <cmath>

namespace zebra_puzzle {

using namespace std;

enum class Color { Blue, Red, Green, Ivory, Yellow };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

// Helper function to check if two houses are adjacent
bool is_adjacent(int i, int j) {
    return std::abs(i - j) == 1;
}

bool is_valid(int house, 
              const array<Color, 5>& colors,
              const array<Nationality, 5>& nationalities,
              const array<Pet, 5>& pets,
              const array<Drink, 5>& drinks,
              const array<Hobby, 5>& hobbies) {
    // Check all constraints that can be checked up to the current house
    for (int i = 0; i <= house; i++) {
        // 2. Englishman in red house
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) return false;
        // 3. Spaniard owns dog
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) return false;
        // 4. Green house drinks coffee
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) return false;
        // 5. Ukrainian drinks tea
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) return false;
        // 7. Snail owner likes dancing
        if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) return false;
        // 8. Yellow house is painter
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) return false;
        // 13. Football drinks orange juice
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) return false;
        // 14. Japanese plays chess
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) return false;
    }
    
    // Check cross-house constraints
    // 6. Green is immediately right of ivory
    for (int i = 0; i < 4; i++) {
        if (i + 1 > house) continue;
        if (colors[i] == Color::Ivory && colors[i + 1] != Color::Green) return false;
        if (colors[i + 1] == Color::Green && colors[i] != Color::Ivory) return false;
    }
    
    // 9. Middle house drinks milk (checked by fixed assignment)
    // 10. Norwegian in first house (checked by fixed assignment)
    // 15. Norwegian next to blue
    if (house >= 1) {
        if (nationalities[0] == Nationality::Norwegian) {
            if (colors[1] != Color::Blue) return false;
        }
    }
    
    return true;
}

bool backtrack(int house, 
               array<Color, 5>& colors, array<bool, 5>& used_colors,
               array<Nationality, 5>& nationalities, array<bool, 5>& used_nationalities,
               array<Pet, 5>& pets, array<bool, 5>& used_pets,
               array<Drink, 5>& drinks, array<bool, 5>& used_drinks,
               array<Hobby, 5>& hobbies, array<bool, 5>& used_hobbies,
               Solution& solution) {
    if (house == 5) {
        // Check remaining constraints
        // 11. Reading next to fox
        // 12. Painter next to horse
        for (int i = 0; i < 5; i++) {
            if (hobbies[i] == Hobby::Reading) {
                bool valid = false;
                for (int j = 0; j < 5; j++) {
                    if (pets[j] == Pet::Fox && is_adjacent(i, j)) {
                        valid = true;
                        break;
                    }
                }
                if (!valid) return false;
            }
            if (hobbies[i] == Hobby::Painting) {
                bool valid = false;
                for (int j = 0; j < 5; j++) {
                    if (pets[j] == Pet::Horse && is_adjacent(i, j)) {
                        valid = true;
                        break;
                    }
                }
                if (!valid) return false;
            }
        }
        // Found valid solution
        for (int i = 0; i < 5; i++) {
            if (drinks[i] == Drink::Water) {
                static const array<string, 5> nationality_names = {
                    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                };
                solution.drinksWater = nationality_names[static_cast<int>(nationalities[i])];
            }
            if (pets[i] == Pet::Zebra) {
                static const array<string, 5> nationality_names = {
                    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                };
                solution.ownsZebra = nationality_names[static_cast<int>(nationalities[i])];
            }
        }
        return true;
    }

    // Generate all possible assignments for the current house
    for (int c = 0; c < 5; c++) if (!used_colors[c]) {
        colors[house] = static_cast<Color>(c);
        used_colors[c] = true;
        for (int n = 0; n < 5; n++) if (!used_nationalities[n]) {
            nationalities[house] = static_cast<Nationality>(n);
            used_nationalities[n] = true;
            for (int p = 0; p < 5; p++) if (!used_pets[p]) {
                pets[house] = static_cast<Pet>(p);
                used_pets[p] = true;
                for (int d = 0; d < 5; d++) if (!used_drinks[d]) {
                    drinks[house] = static_cast<Drink>(d);
                    used_drinks[d] = true;
                    for (int h = 0; h < 5; h++) if (!used_hobbies[h]) {
                        hobbies[house] = static_cast<Hobby>(h);
                        used_hobbies[h] = true;
                        
                        if (is_valid(house, colors, nationalities, pets, drinks, hobbies)) {
                            if (backtrack(house + 1, colors, used_colors, nationalities, used_nationalities,
                                         pets, used_pets, drinks, used_drinks, hobbies, used_hobbies, solution)) {
                                return true;
                            }
                        }
                        
                        used_hobbies[h] = false;
                    }
                    used_drinks[d] = false;
                }
                used_pets[p] = false;
            }
            used_nationalities[n] = false;
        }
        used_colors[c] = false;
    }
    return false;
}

Solution solve() {
    array<Color, 5> colors;
    array<Nationality, 5> nationalities;
    array<Pet, 5> pets;
    array<Drink, 5> drinks;
    array<Hobby, 5> hobbies;
    
    array<bool, 5> used_colors{};
    array<bool, 5> used_nationalities{};
    array<bool, 5> used_pets{};
    array<bool, 5> used_drinks{};
    array<bool, 5> used_hobbies{};
    
    // Fix known values
    nationalities[0] = Nationality::Norwegian;
    used_nationalities[static_cast<int>(Nationality::Norwegian)] = true;
    drinks[2] = Drink::Milk;
    used_drinks[static_cast<int>(Drink::Milk)] = true;
    
    Solution solution;
    backtrack(0, colors, used_colors, nationalities, used_nationalities,
              pets, used_pets, drinks, used_drinks, hobbies, used_hobbies, solution);
    return solution;
}

}  // namespace zebra_puzzle

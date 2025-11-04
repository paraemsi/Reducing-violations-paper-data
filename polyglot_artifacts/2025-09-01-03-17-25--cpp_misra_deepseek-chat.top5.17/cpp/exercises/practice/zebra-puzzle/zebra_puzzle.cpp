#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using House = std::int8_t;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Reading, Dancing, Painting, Football, Chess };

// Helper function to check if two houses are next to each other
template <typename T, typename U>
bool are_adjacent(const std::array<T, 5>& attrs1, T val1, const std::array<U, 5>& attrs2, U val2) {
    for (House i = 0; i < 5; ++i) {
        if (attrs1[i] == val1) {
            if ((i > 0 && attrs2[i - 1] == val2) || (i < 4 && attrs2[i + 1] == val2)) {
                return true;
            }
        }
    }
    return false;
}

Solution solve() {
    // Define all possible values
    std::array<Color, 5> all_colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    std::array<Nationality, 5> all_nationalities = {
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
        Nationality::Norwegian, Nationality::Japanese
    };
    std::array<Pet, 5> all_pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    std::array<Drink, 5> all_drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    std::array<Hobby, 5> all_hobbies = {Hobby::Reading, Hobby::Dancing, Hobby::Painting, Hobby::Football, Hobby::Chess};

    // Generate all permutations and check constraints
    do {
        // Check if Norwegian is in first house (constraint 10)
        if (all_nationalities[0] != Nationality::Norwegian) { continue; }
        
        do {
            // Check if middle house drinks milk (constraint 9)
            if (all_drinks[2] != Drink::Milk) { continue; }
            
            do {
                do {
                    do {
                        // Check all constraints
                        bool valid = true;
                        
                        // 2. Englishman in red house
                        for (House i = 0; i < 5; ++i) {
                            if (all_nationalities[i] == Nationality::Englishman && all_colors[i] != Color::Red) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 3. Spaniard owns dog
                        for (House i = 0; i < 5; ++i) {
                            if (all_nationalities[i] == Nationality::Spaniard && all_pets[i] != Pet::Dog) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 4. Green house drinks coffee
                        for (House i = 0; i < 5; ++i) {
                            if (all_colors[i] == Color::Green && all_drinks[i] != Drink::Coffee) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 5. Ukrainian drinks tea
                        for (House i = 0; i < 5; ++i) {
                            if (all_nationalities[i] == Nationality::Ukrainian && all_drinks[i] != Drink::Tea) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 6. Green is immediately right of ivory
                        bool found = false;
                        for (House i = 1; i < 5; ++i) {
                            if (all_colors[i] == Color::Green && all_colors[i - 1] == Color::Ivory) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) { continue; }
                        
                        // 7. Snail owner likes dancing
                        for (House i = 0; i < 5; ++i) {
                            if (all_pets[i] == Pet::Snails && all_hobbies[i] != Hobby::Dancing) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 8. Yellow house is painter
                        for (House i = 0; i < 5; ++i) {
                            if (all_colors[i] == Color::Yellow && all_hobbies[i] != Hobby::Painting) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 11. Reading next to fox
                        if (!are_adjacent(all_hobbies, Hobby::Reading, all_pets, Pet::Fox)) { continue; }
                        
                        // 12. Painter next to horse
                        if (!are_adjacent(all_hobbies, Hobby::Painting, all_pets, Pet::Horse)) { continue; }
                        
                        // 13. Football drinks orange juice
                        for (House i = 0; i < 5; ++i) {
                            if (all_hobbies[i] == Hobby::Football && all_drinks[i] != Drink::OrangeJuice) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 14. Japanese plays chess
                        for (House i = 0; i < 5; ++i) {
                            if (all_nationalities[i] == Nationality::Japanese && all_hobbies[i] != Hobby::Chess) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) { continue; }
                        
                        // 15. Norwegian next to blue
                        if (!are_adjacent(all_nationalities, Nationality::Norwegian, all_colors, Color::Blue)) { continue; }
                        
                        // Found valid assignment
                        Solution solution;
                        for (House i = 0; i < 5; ++i) {
                            if (all_drinks[i] == Drink::Water) {
                                switch (all_nationalities[i]) {
                                    case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                                    case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                                    case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                                    case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                                    case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                                }
                            }
                            if (all_pets[i] == Pet::Zebra) {
                                switch (all_nationalities[i]) {
                                    case Nationality::Englishman: solution.ownsZebra = "Englishman"; break;
                                    case Nationality::Spaniard: solution.ownsZebra = "Spaniard"; break;
                                    case Nationality::Ukrainian: solution.ownsZebra = "Ukrainian"; break;
                                    case Nationality::Norwegian: solution.ownsZebra = "Norwegian"; break;
                                    case Nationality::Japanese: solution.ownsZebra = "Japanese"; break;
                                }
                            }
                        }
                        return solution;
                    } while (std::next_permutation(all_hobbies.begin(), all_hobbies.end()));
                } while (std::next_permutation(all_pets.begin(), all_pets.end()));
            } while (std::next_permutation(all_drinks.begin(), all_drinks.end()));
        } while (std::next_permutation(all_colors.begin(), all_colors.end()));
    } while (std::next_permutation(all_nationalities.begin(), all_nationalities.end()));
    
    return Solution();
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

Solution solve() {
    // Initialize with all values in some order
    array<Nationality, 5> nationalities = {
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
        Nationality::Norwegian, Nationality::Japanese
    };
    array<Color, 5> colors = {
        Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue
    };
    array<Drink, 5> drinks = {
        Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water
    };
    array<Pet, 5> pets = {
        Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra
    };
    array<Hobby, 5> hobbies = {
        Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess
    };
    
    // Sort to start permutations
    sort(nationalities.begin(), nationalities.end());
    sort(colors.begin(), colors.end());
    sort(drinks.begin(), drinks.end());
    sort(pets.begin(), pets.end());
    sort(hobbies.begin(), hobbies.end());
    
    do {
        // Constraint 10: Norwegian lives in first house
        if (nationalities[0] != Nationality::Norwegian) { continue; }
        
        do {
            // Constraint 2: Englishman lives in red house
            bool englishman_in_red = true;
            for (int32_t i = 0; i < 5; ++i) {
                if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
                    englishman_in_red = false;
                    break;
                }
            }
            if (!englishman_in_red) { continue; }
            
            // Constraint 6: Green is immediately to the right of ivory
            bool found_green_right_of_ivory = false;
            for (int32_t i = 0; i < 4; ++i) {
                if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                    found_green_right_of_ivory = true;
                    break;
                }
            }
            if (!found_green_right_of_ivory) { continue; }
            
            // Constraint 15: Norwegian lives next to blue house
            bool norwegian_next_to_blue = false;
            for (int32_t i = 0; i < 5; ++i) {
                if (nationalities[i] == Nationality::Norwegian) {
                    if (i > 0 && colors[i - 1] == Color::Blue) { norwegian_next_to_blue = true; }
                    if (i < 4 && colors[i + 1] == Color::Blue) { norwegian_next_to_blue = true; }
                    break;
                }
            }
            if (!norwegian_next_to_blue) { continue; }
            
            do {
                // Constraint 9: Middle house drinks milk
                if (drinks[2] != Drink::Milk) { continue; }
                
                // Constraint 4: Green house drinks coffee
                bool green_drinks_coffee = true;
                for (int32_t i = 0; i < 5; ++i) {
                    if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
                        green_drinks_coffee = false;
                        break;
                    }
                }
                if (!green_drinks_coffee) { continue; }
                
                // Constraint 5: Ukrainian drinks tea
                bool ukrainian_drinks_tea = true;
                for (int32_t i = 0; i < 5; ++i) {
                    if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
                        ukrainian_drinks_tea = false;
                        break;
                    }
                }
                if (!ukrainian_drinks_tea) { continue; }
                
                do {
                    // Constraint 3: Spaniard owns dog
                    bool spaniard_owns_dog = true;
                    for (int32_t i = 0; i < 5; ++i) {
                        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
                            spaniard_owns_dog = false;
                            break;
                        }
                    }
                    if (!spaniard_owns_dog) { continue; }
                    
                    do {
                        // Check all remaining constraints
                        // Constraint 7: Snail owner likes dancing
                        for (int32_t i = 0; i < 5; ++i) {
                            if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) {
                                goto next_hobby;
                            }
                        }
                        // Constraint 8: Yellow house is painter
                        for (int32_t i = 0; i < 5; ++i) {
                            if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
                                goto next_hobby;
                            }
                        }
                        // Constraint 13: Football player drinks orange juice
                        for (int32_t i = 0; i < 5; ++i) {
                            if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
                                goto next_hobby;
                            }
                        }
                        // Constraint 14: Japanese plays chess
                        for (int32_t i = 0; i < 5; ++i) {
                            if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
                                goto next_hobby;
                            }
                        }
                        // Constraint 11: Reader next to fox owner
                        for (int32_t i = 0; i < 5; ++i) {
                            if (hobbies[i] == Hobby::Reading) {
                                bool found = false;
                                if (i > 0 && pets[i - 1] == Pet::Fox) { found = true; }
                                if (i < 4 && pets[i + 1] == Pet::Fox) { found = true; }
                                if (!found) { goto next_hobby; }
                            }
                        }
                        // Constraint 12: Painter next to horse owner
                        for (int32_t i = 0; i < 5; ++i) {
                            if (hobbies[i] == Hobby::Painting) {
                                bool found = false;
                                if (i > 0 && pets[i - 1] == Pet::Horse) { found = true; }
                                if (i < 4 && pets[i + 1] == Pet::Horse) { found = true; }
                                if (!found) { goto next_hobby; }
                            }
                        }
                        
                        // All constraints satisfied
                        Solution solution;
                        for (int32_t i = 0; i < 5; ++i) {
                            if (drinks[i] == Drink::Water) {
                                switch (nationalities[i]) {
                                    case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                                    case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                                    case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                                    case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                                    case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                                }
                            }
                            if (pets[i] == Pet::Zebra) {
                                switch (nationalities[i]) {
                                    case Nationality::Englishman: solution.ownsZebra = "Englishman"; break;
                                    case Nationality::Spaniard: solution.ownsZebra = "Spaniard"; break;
                                    case Nationality::Ukrainian: solution.ownsZebra = "Ukrainian"; break;
                                    case Nationality::Norwegian: solution.ownsZebra = "Norwegian"; break;
                                    case Nationality::Japanese: solution.ownsZebra = "Japanese"; break;
                                }
                            }
                        }
                        return solution;
                        
                    next_hobby:;
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(colors.begin(), colors.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return Solution();
}

}  // namespace zebra_puzzle

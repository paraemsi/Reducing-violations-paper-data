#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Reading, Dancing, Painting, Football, Chess };

constexpr int num_houses = 5;

template<typename T>
using Permutation = array<T, num_houses>;

bool satisfies_constraints(
    const Permutation<Color>& colors,
    const Permutation<Nationality>& nationalities,
    const Permutation<Drink>& drinks,
    const Permutation<Pet>& pets,
    const Permutation<Hobby>& hobbies) {
    
    // Check all constraints
    // 2. Englishman in red house
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Englishman) {
            if (colors[i] != Color::Red) return false;
            break;
        }
    }
    
    // 3. Spaniard owns dog
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Spaniard) {
            if (pets[i] != Pet::Dog) return false;
            break;
        }
    }
    
    // 4. Green house drinks coffee
    for (int i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Green) {
            if (drinks[i] != Drink::Coffee) return false;
            break;
        }
    }
    
    // 5. Ukrainian drinks tea
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Ukrainian) {
            if (drinks[i] != Drink::Tea) return false;
            break;
        }
    }
    
    // 6. Green is immediately right of ivory
    bool found_green_right_of_ivory = false;
    for (int i = 1; i < num_houses; ++i) {
        if ((colors[i] == Color::Green) && (colors[i-1] == Color::Ivory)) {
            found_green_right_of_ivory = true;
            break;
        }
    }
    if (!found_green_right_of_ivory) return false;
    
    // 7. Snail owner dances
    for (int i = 0; i < num_houses; ++i) {
        if (pets[i] == Pet::Snails) {
            if (hobbies[i] != Hobby::Dancing) return false;
            break;
        }
    }
    
    // 8. Yellow house is painter
    for (int i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Yellow) {
            if (hobbies[i] != Hobby::Painting) return false;
            break;
        }
    }
    
    // 9. Middle drinks milk
    if (drinks[2] != Drink::Milk) return false;
    
    // 10. Norwegian in first
    if (nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. Reader next to fox
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            bool found = false;
            if (i > 0 && pets[i-1] == Pet::Fox) found = true;
            if (i < num_houses - 1 && pets[i+1] == Pet::Fox) found = true;
            if (!found) return false;
        }
    }
    
    // 12. Painter next to horse
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            bool found = false;
            if (i > 0 && pets[i-1] == Pet::Horse) found = true;
            if (i < num_houses - 1 && pets[i+1] == Pet::Horse) found = true;
            if (!found) return false;
        }
    }
    
    // 13. Football drinks orange juice
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Football) {
            if (drinks[i] != Drink::OrangeJuice) return false;
            break;
        }
    }
    
    // 14. Japanese plays chess
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Japanese) {
            if (hobbies[i] != Hobby::Chess) return false;
            break;
        }
    }
    
    // 15. Norwegian next to blue
    {
        // Norwegian is at index 0 (constraint 10)
        if (colors[1] != Color::Blue) return false;
    }
    
    return true;
}

Solution solve() {
    // Generate all permutations and check constraints
    array<Color, num_houses> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Nationality, num_houses> nationalities = {Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    array<Drink, num_houses> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    array<Pet, num_houses> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Hobby, num_houses> hobbies = {Hobby::Reading, Hobby::Dancing, Hobby::Painting, Hobby::Football, Hobby::Chess};
    
    Solution solution;
    
    // Generate all permutations and check constraints
    do {
        // Norwegian is in first house (constraint 10)
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        do {
            // Green is right of ivory (constraint 6)
            bool valid = false;
            for (int i = 1; i < num_houses; ++i) {
                if (colors[i] == Color::Green && colors[i-1] == Color::Ivory) {
                    valid = true;
                    break;
                }
            }
            if (!valid) continue;
            
            // Norwegian lives next to blue house (constraint 15)
            int norwegian_idx = 0;
            bool next_to_blue = false;
            if (norwegian_idx > 0 && colors[norwegian_idx-1] == Color::Blue) next_to_blue = true;
            if (norwegian_idx < num_houses - 1 && colors[norwegian_idx+1] == Color::Blue) next_to_blue = true;
            if (!next_to_blue) continue;
            
            do {
                // Middle house drinks milk (constraint 9)
                if (drinks[2] != Drink::Milk) continue;
                
                do {
                    do {
                        if (satisfies_constraints(colors, nationalities, drinks, pets, hobbies)) {
                            // Find who drinks water and owns zebra
                            for (int i = 0; i < num_houses; ++i) {
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
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(colors.begin(), colors.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return solution;
}

}  // namespace zebra_puzzle

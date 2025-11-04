#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

// Define enums in order for next_permutation to work correctly
enum class Nationality { Norwegian, Englishman, Spaniard, Ukrainian, Japanese };
enum class Color { Blue, Green, Ivory, Red, Yellow };
enum class Drink { Milk, Coffee, OrangeJuice, Tea, Water };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

constexpr int num_houses = 5;

template<typename T>
using Assignment = array<T, num_houses>;

bool satisfies_constraints(
    const Assignment<Nationality>& nationalities,
    const Assignment<Color>& colors,
    const Assignment<Drink>& drinks,
    const Assignment<Pet>& pets,
    const Assignment<Hobby>& hobbies) {
    
    // Constraint 2: Englishman in red house
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Englishman) && (colors[i] != Color::Red)) {
            return false;
        }
    }
    
    // Constraint 3: Spaniard owns dog
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Spaniard) && (pets[i] != Pet::Dog)) {
            return false;
        }
    }
    
    // Constraint 4: Green house drinks coffee
    for (int i = 0; i < num_houses; ++i) {
        if ((colors[i] == Color::Green) && (drinks[i] != Drink::Coffee)) {
            return false;
        }
    }
    
    // Constraint 5: Ukrainian drinks tea
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Ukrainian) && (drinks[i] != Drink::Tea)) {
            return false;
        }
    }
    
    // Constraint 6: Green is immediately to the right of ivory
    bool found_green_right_of_ivory = false;
    for (int i = 1; i < num_houses; ++i) {
        if ((colors[i] == Color::Green) && (colors[i-1] == Color::Ivory)) {
            found_green_right_of_ivory = true;
            break;
        }
    }
    if (!found_green_right_of_ivory) return false;
    
    // Constraint 7: Snail owner dances
    for (int i = 0; i < num_houses; ++i) {
        if ((pets[i] == Pet::Snail) && (hobbies[i] != Hobby::Dancing)) {
            return false;
        }
    }
    
    // Constraint 8: Yellow house is painter
    for (int i = 0; i < num_houses; ++i) {
        if ((colors[i] == Color::Yellow) && (hobbies[i] != Hobby::Painting)) {
            return false;
        }
    }
    
    // Constraint 9: Middle drinks milk
    if (drinks[2] != Drink::Milk) return false;
    
    // Constraint 10: Norwegian in first
    if (nationalities[0] != Nationality::Norwegian) return false;
    
    // Constraint 11: Reader next to fox
    bool found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i-1] == Pet::Fox) || (i < num_houses-1 && pets[i+1] == Pet::Fox)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // Constraint 12: Painter next to horse
    found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i-1] == Pet::Horse) || (i < num_houses-1 && pets[i+1] == Pet::Horse)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // Constraint 13: Football player drinks orange juice
    for (int i = 0; i < num_houses; ++i) {
        if ((hobbies[i] == Hobby::Football) && (drinks[i] != Drink::OrangeJuice)) {
            return false;
        }
    }
    
    // Constraint 14: Japanese plays chess
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Japanese) && (hobbies[i] != Hobby::Chess)) {
            return false;
        }
    }
    
    // Constraint 15: Norwegian lives next to the blue house
    // Norwegian is in first house (index 0), so check index 1
    if (colors[1] != Color::Blue) return false;
    
    return true;
}

Solution solve() {
    // Fix Norwegian in first house and milk in middle
    // Generate permutations for other categories
    Assignment<Nationality> nationalities;
    nationalities[0] = Nationality::Norwegian;
    // The remaining nationalities
    array<Nationality, num_houses-1> other_nats = {
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Japanese
    };
    sort(other_nats.begin(), other_nats.end());
    
    Assignment<Drink> drinks;
    drinks[2] = Drink::Milk;
    // The remaining drinks
    array<Drink, num_houses-1> other_drinks = {
        Drink::Coffee, Drink::OrangeJuice, Drink::Tea, Drink::Water
    };
    sort(other_drinks.begin(), other_drinks.end());
    
    // Other categories
    Assignment<Color> colors;
    array<Color, num_houses> all_colors = {Color::Blue, Color::Green, Color::Ivory, Color::Red, Color::Yellow};
    sort(all_colors.begin(), all_colors.end());
    
    Assignment<Pet> pets;
    array<Pet, num_houses> all_pets = {Pet::Dog, Pet::Snail, Pet::Fox, Pet::Horse, Pet::Zebra};
    sort(all_pets.begin(), all_pets.end());
    
    Assignment<Hobby> hobbies;
    array<Hobby, num_houses> all_hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    sort(all_hobbies.begin(), all_hobbies.end());
    
    do {
        // Fill nationalities
        for (int i = 0; i < num_houses-1; ++i) {
            nationalities[i+1] = other_nats[i];
        }
        
        do {
            // Fill drinks around the fixed milk in the middle
            int index = 0;
            for (int i = 0; i < num_houses; ++i) {
                if (i != 2) {
                    drinks[i] = other_drinks[index];
                    index++;
                }
            }
            
            do {
                do {
                    do {
                        if (satisfies_constraints(nationalities, colors, drinks, pets, hobbies)) {
                            Solution solution;
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
                    } while (next_permutation(all_hobbies.begin(), all_hobbies.end()) && 
                             std::copy(all_hobbies.begin(), all_hobbies.end(), hobbies.begin()));
                } while (next_permutation(all_pets.begin(), all_pets.end()) && 
                         std::copy(all_pets.begin(), all_pets.end(), pets.begin()));
            } while (next_permutation(all_colors.begin(), all_colors.end()) && 
                     std::copy(all_colors.begin(), all_colors.end(), colors.begin()));
        } while (next_permutation(other_drinks.begin(), other_drinks.end()));
    } while (next_permutation(other_nats.begin(), other_nats.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

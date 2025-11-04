#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

using std::array;

template<typename T>
bool next_permutation(array<T, 5>& a) {
    return std::next_permutation(a.begin(), a.end());
}

Solution solve() {
    // Initialize all categories
    array<Nationality, 5> nationalities{
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
        Nationality::Norwegian, Nationality::Japanese
    };
    array<Color, 5> colors{
        Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue
    };
    array<Drink, 5> drinks{
        Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water
    };
    array<Pet, 5> pets{
        Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra
    };
    array<Hobby, 5> hobbies{
        Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess
    };
    
    // Sort to start from the first permutation
    std::sort(nationalities.begin(), nationalities.end());
    std::sort(colors.begin(), colors.end());
    std::sort(drinks.begin(), drinks.end());
    std::sort(pets.begin(), pets.end());
    std::sort(hobbies.begin(), hobbies.end());
    
    do {
        // Constraint 10: Norwegian in first house
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        do {
            // Constraint 15: Norwegian next to blue house (house 0 next to house 1)
            // Check if blue is in position 1
            bool blue_next_to_norwegian = false;
            for (int i = 0; i < 5; ++i) {
                if (colors[i] == Color::Blue) {
                    if (i == 1) { // Norwegian is at index 0, so next index is 1
                        blue_next_to_norwegian = true;
                    }
                    break;
                }
            }
            if (!blue_next_to_norwegian) continue;
            
            // Constraint 2: Englishman in red house
            bool englishman_in_red = true;
            for (int i = 0; i < 5; ++i) {
                if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
                    englishman_in_red = false;
                    break;
                }
                if (colors[i] == Color::Red && nationalities[i] != Nationality::Englishman) {
                    englishman_in_red = false;
                    break;
                }
            }
            if (!englishman_in_red) continue;
            
            // Constraint 6: Green is immediately to the right of ivory
            int green_pos = -1, ivory_pos = -1;
            for (int i = 0; i < 5; ++i) {
                if (colors[i] == Color::Green) green_pos = i;
                if (colors[i] == Color::Ivory) ivory_pos = i;
            }
            if (green_pos != ivory_pos + 1) continue;
            
            do {
                // Constraint 9: Middle house drinks milk
                if (drinks[2] != Drink::Milk) continue;
                
                // Constraint 4: Green house drinks coffee
                bool green_drinks_coffee = true;
                for (int i = 0; i < 5; ++i) {
                    if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
                        green_drinks_coffee = false;
                        break;
                    }
                }
                if (!green_drinks_coffee) continue;
                
                // Constraint 5: Ukrainian drinks tea
                bool ukrainian_drinks_tea = true;
                for (int i = 0; i < 5; ++i) {
                    if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
                        ukrainian_drinks_tea = false;
                        break;
                    }
                }
                if (!ukrainian_drinks_tea) continue;
                
                // Constraint 13: Football drinks orange juice
                bool football_drinks_oj = true;
                for (int i = 0; i < 5; ++i) {
                    if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
                        football_drinks_oj = false;
                        break;
                    }
                }
                if (!football_drinks_oj) continue;
                
                do {
                    do {
                        // Check remaining constraints
                        // Constraint 3: Spaniard owns dog
                        bool spaniard_owns_dog = true;
                        for (int i = 0; i < 5; ++i) {
                            if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
                                spaniard_owns_dog = false;
                                break;
                            }
                        }
                        if (!spaniard_owns_dog) continue;
                        
                        // Constraint 7: Snail owner likes dancing
                        bool snails_like_dancing = true;
                        for (int i = 0; i < 5; ++i) {
                            if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) {
                                snails_like_dancing = false;
                                break;
                            }
                        }
                        if (!snails_like_dancing) continue;
                        
                        // Constraint 8: Yellow house is painter
                        bool yellow_is_painter = true;
                        for (int i = 0; i < 5; ++i) {
                            if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
                                yellow_is_painter = false;
                                break;
                            }
                        }
                        if (!yellow_is_painter) continue;
                        
                        // Constraint 11: Reading next to fox
                        bool reading_next_to_fox = false;
                        int reading_pos = -1, fox_pos = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == Hobby::Reading) reading_pos = i;
                            if (pets[i] == Pet::Fox) fox_pos = i;
                        }
                        if (std::abs(reading_pos - fox_pos) == 1) reading_next_to_fox = true;
                        if (!reading_next_to_fox) continue;
                        
                        // Constraint 12: Painter next to horse
                        bool painter_next_to_horse = false;
                        int painting_pos = -1, horse_pos = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == Hobby::Painting) painting_pos = i;
                            if (pets[i] == Pet::Horse) horse_pos = i;
                        }
                        if (std::abs(painting_pos - horse_pos) == 1) painter_next_to_horse = true;
                        if (!painter_next_to_horse) continue;
                        
                        // Constraint 14: Japanese plays chess
                        bool japanese_plays_chess = true;
                        for (int i = 0; i < 5; ++i) {
                            if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
                                japanese_plays_chess = false;
                                break;
                            }
                        }
                        if (!japanese_plays_chess) continue;
                        
                        // Found valid solution
                        // Find water drinker and zebra owner
                        int water_drinker_idx = -1;
                        int zebra_owner_idx = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (drinks[i] == Drink::Water) water_drinker_idx = i;
                            if (pets[i] == Pet::Zebra) zebra_owner_idx = i;
                        }
                        
                        // Convert to string
                        std::array<std::string, 5> nationality_names = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };
                        
                        return Solution{
                            nationality_names[static_cast<int>(nationalities[water_drinker_idx])],
                            nationality_names[static_cast<int>(nationalities[zebra_owner_idx])]
                        };
                    } while (next_permutation(pets));
                } while (next_permutation(hobbies));
            } while (next_permutation(drinks));
        } while (next_permutation(colors));
    } while (next_permutation(nationalities));
    
    // Should not reach here according to the puzzle
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

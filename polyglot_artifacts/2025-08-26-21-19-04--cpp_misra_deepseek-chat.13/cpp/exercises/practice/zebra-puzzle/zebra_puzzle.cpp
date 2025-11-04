#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

constexpr int num_houses = 5;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

// Convert enums to strings for the answer
string nationality_to_string(Nationality n) {
    switch (n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
    }
    return "";
}

// Helper function to find index of a value in an array
template<typename T, size_t N>
int find_index(const array<T, N>& arr, T value) {
    for (size_t i = 0; i < N; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

Solution solve() {
    Solution solution;
    
    // Define options
    array<Color, num_houses> color_options{Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Nationality, num_houses> nationality_options{Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    array<Pet, num_houses> pet_options{Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Drink, num_houses> drink_options{Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    array<Hobby, num_houses> hobby_options{Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    // Generate all permutations
    array<Color, num_houses> colors = color_options;
    do {
        array<Nationality, num_houses> nationalities = nationality_options;
        do {
            // Constraint 10: Norwegian lives in first house
            if (nationalities[0] != Nationality::Norwegian) continue;
            
            array<Pet, num_houses> pets = pet_options;
            do {
                array<Drink, num_houses> drinks = drink_options;
                do {
                    // Constraint 9: Middle house drinks milk
                    if (drinks[2] != Drink::Milk) continue;
                    
                    array<Hobby, num_houses> hobbies = hobby_options;
                    do {
                        // Check all constraints
                        bool valid = true;
                        
                        // 2. Englishman in red house
                        for (int i = 0; i < num_houses; i++) {
                            if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 3. Spaniard owns dog
                        for (int i = 0; i < num_houses; i++) {
                            if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 4. Green house drinks coffee
                        for (int i = 0; i < num_houses; i++) {
                            if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 5. Ukrainian drinks tea
                        for (int i = 0; i < num_houses; i++) {
                            if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 6. Green is right of ivory
                        bool green_right_of_ivory = false;
                        for (int i = 0; i < num_houses - 1; i++) {
                            if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                                green_right_of_ivory = true;
                                break;
                            }
                        }
                        if (!green_right_of_ivory) continue;
                        
                        // 7. Snail owner likes dancing
                        for (int i = 0; i < num_houses; i++) {
                            if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 8. Yellow house is painter
                        for (int i = 0; i < num_houses; i++) {
                            if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 11. Reader next to fox owner
                        for (int i = 0; i < num_houses; i++) {
                            if (hobbies[i] == Hobby::Reading) {
                                bool found = false;
                                if (i > 0 && pets[i - 1] == Pet::Fox) found = true;
                                if (i < num_houses - 1 && pets[i + 1] == Pet::Fox) found = true;
                                if (!found) {
                                    valid = false;
                                    break;
                                }
                            }
                        }
                        if (!valid) continue;
                        
                        // 12. Painter next to horse owner
                        for (int i = 0; i < num_houses; i++) {
                            if (hobbies[i] == Hobby::Painting) {
                                bool found = false;
                                if (i > 0 && pets[i - 1] == Pet::Horse) found = true;
                                if (i < num_houses - 1 && pets[i + 1] == Pet::Horse) found = true;
                                if (!found) {
                                    valid = false;
                                    break;
                                }
                            }
                        }
                        if (!valid) continue;
                        
                        // 13. Football player drinks orange juice
                        for (int i = 0; i < num_houses; i++) {
                            if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 14. Japanese plays chess
                        for (int i = 0; i < num_houses; i++) {
                            if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) continue;
                        
                        // 15. Norwegian next to blue house
                        int norwegian_index = find_index(nationalities, Nationality::Norwegian);
                        bool found_blue = false;
                        if (norwegian_index > 0 && colors[norwegian_index - 1] == Color::Blue) found_blue = true;
                        if (norwegian_index < num_houses - 1 && colors[norwegian_index + 1] == Color::Blue) found_blue = true;
                        if (!found_blue) continue;
                        
                        // Found valid assignment
                        for (int i = 0; i < num_houses; i++) {
                            if (drinks[i] == Drink::Water) {
                                solution.drinksWater = nationality_to_string(nationalities[i]);
                            }
                            if (pets[i] == Pet::Zebra) {
                                solution.ownsZebra = nationality_to_string(nationalities[i]);
                            }
                        }
                        return solution;
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(drinks.begin(), drinks.end()));
            } while (next_permutation(pets.begin(), pets.end()));
        } while (next_permutation(nationalities.begin(), nationalities.end()));
    } while (next_permutation(colors.begin(), colors.end()));
    
    return solution;
}

}  // namespace zebra_puzzle

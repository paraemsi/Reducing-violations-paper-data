#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

constexpr int num_houses = 5;

template<typename T>
using Assignment = array<T, num_houses>;

bool satisfies_all_constraints(
    const Assignment<Nationality>& nationalities,
    const Assignment<Color>& colors,
    const Assignment<Drink>& drinks,
    const Assignment<Pet>& pets,
    const Assignment<Hobby>& hobbies) {
    
    // Check each constraint
    // 2. Englishman in red house
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) return false;
    }
    
    // 3. Spaniard owns dog
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) return false;
    }
    
    // 4. Green house drinks coffee
    for (int i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) return false;
    }
    
    // 5. Ukrainian drinks tea
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) return false;
    }
    
    // 6. Green is immediately right of ivory
    bool green_right_of_ivory = false;
    for (int i = 0; i < num_houses - 1; ++i) {
        if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
            green_right_of_ivory = true;
            break;
        }
    }
    if (!green_right_of_ivory) return false;
    
    // 7. Snail owner dances
    for (int i = 0; i < num_houses; ++i) {
        if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) return false;
    }
    
    // 8. Yellow house is painter
    for (int i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) return false;
    }
    
    // 9. Middle house drinks milk - already ensured
    
    // 10. Norwegian in first house - already ensured
    
    // 11. Reader next to fox owner
    bool reader_next_to_fox = false;
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i - 1] == Pet::Fox) || (i < num_houses - 1 && pets[i + 1] == Pet::Fox)) {
                reader_next_to_fox = true;
                break;
            }
        }
    }
    if (!reader_next_to_fox) return false;
    
    // 12. Painter next to horse owner
    bool painter_next_to_horse = false;
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i - 1] == Pet::Horse) || (i < num_houses - 1 && pets[i + 1] == Pet::Horse)) {
                painter_next_to_horse = true;
                break;
            }
        }
    }
    if (!painter_next_to_horse) return false;
    
    // 13. Football player drinks orange juice
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) return false;
    }
    
    // 14. Japanese plays chess
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) return false;
    }
    
    // 15. Norwegian next to blue house
    bool norwegian_next_to_blue = false;
    int norwegian_index = -1;
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Norwegian) {
            norwegian_index = i;
            break;
        }
    }
    if ((norwegian_index > 0 && colors[norwegian_index - 1] == Color::Blue) ||
        (norwegian_index < num_houses - 1 && colors[norwegian_index + 1] == Color::Blue)) {
        norwegian_next_to_blue = true;
    }
    if (!norwegian_next_to_blue) return false;
    
    return true;
}

Solution solve() {
    // Pre-sort the arrays to generate permutations in order
    array<Nationality, num_houses> nationalities = {
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
        Nationality::Norwegian, Nationality::Japanese
    };
    array<Color, num_houses> colors = {
        Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue
    };
    array<Drink, num_houses> drinks = {
        Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water
    };
    array<Pet, num_houses> pets = {
        Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra
    };
    array<Hobby, num_houses> hobbies = {
        Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess
    };
    
    // Sort to generate all permutations
    sort(nationalities.begin(), nationalities.end());
    sort(colors.begin(), colors.end());
    sort(drinks.begin(), drinks.end());
    sort(pets.begin(), pets.end());
    sort(hobbies.begin(), hobbies.end());
    
    do {
        // Norwegian in first house
        if (nationalities[0] != Nationality::Norwegian) continue;
        do {
            // Milk in middle
            if (drinks[2] != Drink::Milk) continue;
            do {
                // Check green right of ivory
                bool valid = false;
                for (int i = 0; i < num_houses - 1; ++i) {
                    if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                        valid = true;
                        break;
                    }
                }
                if (!valid) continue;
                // Norwegian next to blue
                if (colors[1] != Color::Blue) continue;
                do {
                    do {
                        if (satisfies_all_constraints(nationalities, colors, drinks, pets, hobbies)) {
                            Solution solution;
                            for (int i = 0; i < num_houses; ++i) {
                                if (drinks[i] == Drink::Water) {
                                    const string nationality_names[] = {
                                        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                                    };
                                    solution.drinksWater = nationality_names[static_cast<int>(nationalities[i])];
                                }
                                if (pets[i] == Pet::Zebra) {
                                    const string nationality_names[] = {
                                        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                                    };
                                    solution.ownsZebra = nationality_names[static_cast<int>(nationalities[i])];
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(colors.begin(), colors.end()));
        } while (next_permutation(drinks.begin(), drinks.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return Solution();
}

}  // namespace zebra_puzzle

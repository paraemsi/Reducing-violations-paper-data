#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

// Define enums in order for std::next_permutation to work correctly
// std::next_permutation requires the elements to be in sorted order
enum class Nationality : std::int8_t {
    Englishman,
    Japanese,
    Norwegian,
    Spaniard,
    Ukrainian
};

enum class Color : std::int8_t {
    Blue,
    Green,
    Ivory,
    Red,
    Yellow
};

enum class Drink : std::int8_t {
    Coffee,
    Milk,
    OrangeJuice,
    Tea,
    Water
};

enum class Pet : std::int8_t {
    Dog,
    Fox,
    Horse,
    Snails,
    Zebra
};

enum class Hobby : std::int8_t {
    Chess,
    Dancing,
    Football,
    Painting,
    Reading
};

constexpr std::int8_t num_houses = 5;

template <typename T>
using Houses = std::array<T, num_houses>;

bool satisfies_constraints(const Houses<Nationality>& nationalities,
                          const Houses<Color>& colors,
                          const Houses<Drink>& drinks,
                          const Houses<Pet>& pets,
                          const Houses<Hobby>& hobbies) {
    // Constraint 2: Englishman lives in the red house
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
            return false;
        }
    }
    
    // Constraint 3: Spaniard owns the dog
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
            return false;
        }
    }
    
    // Constraint 4: Green house drinks coffee
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
            return false;
        }
    }
    
    // Constraint 5: Ukrainian drinks tea
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
            return false;
        }
    }
    
    // Constraint 6: Green is immediately to the right of ivory
    bool found = false;
    for (std::int8_t i = 0; i < num_houses - 1; ++i) {
        if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
            found = true;
            break;
        }
    }
    if (!found) {
        return false;
    }
    
    // Constraint 7: Snails owner likes dancing
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) {
            return false;
        }
    }
    
    // Constraint 8: Yellow house is painter
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
            return false;
        }
    }
    
    // Constraint 9: Middle house drinks milk
    if (drinks[2] != Drink::Milk) {
        return false;
    }
    
    // Constraint 10: Norwegian lives in first house
    if (nationalities[0] != Nationality::Norwegian) {
        return false;
    }
    
    // Constraint 11: Reader next to fox owner
    bool reader_next_to_fox = false;
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i - 1] == Pet::Fox) || (i < num_houses - 1 && pets[i + 1] == Pet::Fox)) {
                reader_next_to_fox = true;
                break;
            }
        }
    }
    if (!reader_next_to_fox) {
        return false;
    }
    
    // Constraint 12: Painter next to horse owner
    bool painter_next_to_horse = false;
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i - 1] == Pet::Horse) || (i < num_houses - 1 && pets[i + 1] == Pet::Horse)) {
                painter_next_to_horse = true;
                break;
            }
        }
    }
    if (!painter_next_to_horse) {
        return false;
    }
    
    // Constraint 13: Football player drinks orange juice
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
            return false;
        }
    }
    
    // Constraint 14: Japanese plays chess
    for (std::int8_t i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
            return false;
        }
    }
    
    // Constraint 15: Norwegian next to blue house
    // Norwegian is always in position 0 per constraint 10
    // So check if position 1 is blue
    if (colors[1] != Color::Blue) {
        return false;
    }
    
    return true;
}

Solution solve() {
    // Fix Norwegian in the first house
    Houses<Nationality> nationalities;
    nationalities[0] = Nationality::Norwegian;
    // The remaining nationalities need to be permuted
    std::array<Nationality, 4> remaining_nationalities{
        Nationality::Englishman,
        Nationality::Japanese,
        Nationality::Spaniard,
        Nationality::Ukrainian
    };
    
    // Sort to start permutations
    std::sort(remaining_nationalities.begin(), remaining_nationalities.end());
    
    do {
        // Fill the rest of the houses
        for (std::int8_t i = 0; i < 4; ++i) {
            nationalities[i + 1] = remaining_nationalities[i];
        }
        
        Houses<Color> colors{Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
        do {
            // Check green is right of ivory
            bool valid = false;
            for (std::int8_t i = 0; i < num_houses - 1; ++i) {
                if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
                    valid = true;
                    break;
                }
            }
            if (!valid && num_houses > 1) continue;
            
            Houses<Drink> drinks{Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
            do {
                // Middle house drinks milk
                if (drinks[2] != Drink::Milk) continue;
                
                Houses<Pet> pets{Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
                do {
                    Houses<Hobby> hobbies{Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
                    do {
                        if (satisfies_constraints(nationalities, colors, drinks, pets, hobbies)) {
                            // Find who drinks water and owns zebra
                            Solution solution;
                            for (std::int8_t i = 0; i < num_houses; ++i) {
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
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(colors.begin(), colors.end()));
    } while (std::next_permutation(remaining_nationalities.begin(), remaining_nationalities.end()));
    
    // Should never reach here if puzzle is correct
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

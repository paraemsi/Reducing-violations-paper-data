#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

// Define enums in order for std::next_permutation to work correctly
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Hobby { Dancing, Reading, Painting, Football, Chess };

using House = std::int8_t;

template <typename T>
using Assignment = std::array<T, 5>;

bool satisfies_constraints(
    const Assignment<Color>& colors,
    const Assignment<Nationality>& nationalities,
    const Assignment<Drink>& drinks,
    const Assignment<Pet>& pets,
    const Assignment<Hobby>& hobbies) {
    
    // 2. The Englishman lives in the red house.
    for (House i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
            return false;
        }
    }
    
    // 3. The Spaniard owns the dog.
    for (House i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
            return false;
        }
    }
    
    // 4. The person in the green house drinks coffee.
    for (House i = 0; i < 5; ++i) {
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
            return false;
        }
    }
    
    // 5. The Ukrainian drinks tea.
    for (House i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
            return false;
        }
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found_green_right_of_ivory = false;
    for (House i = 0; i < 4; ++i) {
        if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
            found_green_right_of_ivory = true;
            break;
        }
    }
    if (!found_green_right_of_ivory) {
        return false;
    }
    
    // 7. The snail owner likes to go dancing.
    for (House i = 0; i < 5; ++i) {
        if (pets[i] == Pet::Snail && hobbies[i] != Hobby::Dancing) {
            return false;
        }
    }
    
    // 8. The person in the yellow house is a painter.
    for (House i = 0; i < 5; ++i) {
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
            return false;
        }
    }
    
    // 9. The person in the middle house drinks milk.
    if (drinks[2] != Drink::Milk) return false;
    
    // 10. The Norwegian lives in the first house.
    if (nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    bool found = false;
    for (House i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i - 1] == Pet::Fox) || (i < 4 && pets[i + 1] == Pet::Fox)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 12. The painter's house is next to the house with the horse.
    found = false;
    for (House i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i - 1] == Pet::Horse) || (i < 4 && pets[i + 1] == Pet::Horse)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 13. The person who plays football drinks orange juice.
    for (House i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
            return false;
        }
    }
    
    // 14. The Japanese person plays chess.
    for (House i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
            return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    // Norwegian is in first house (index 0), so check if blue is next to it (index 1)
    bool found_norwegian_next_to_blue = false;
    if (nationalities[0] == Nationality::Norwegian) {
        // Check adjacent houses
        for (House i = 0; i < 5; ++i) {
            if (nationalities[i] == Nationality::Norwegian) {
                if ((i > 0) && (colors[i - 1] == Color::Blue)) {
                    found_norwegian_next_to_blue = true;
                    break;
                }
                if ((i < 4) && (colors[i + 1] == Color::Blue)) {
                    found_norwegian_next_to_blue = true;
                    break;
                }
            }
        }
    }
    if (!found_norwegian_next_to_blue) {
        return false;
    }
    
    return true;
}

Solution solve() {
    // Generate all permutations and check constraints
    // Sort the initial arrays to use with next_permutation
    Assignment<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    Assignment<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                             Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    Assignment<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    Assignment<Pet> pets = {Pet::Dog, Pet::Snail, Pet::Fox, Pet::Horse, Pet::Zebra};
    Assignment<Hobby> hobbies = {Hobby::Dancing, Hobby::Reading, Hobby::Painting, Hobby::Football, Hobby::Chess};
    
    // Sort to start permutations from the beginning
    std::sort(colors.begin(), colors.end());
    do {
        std::sort(nationalities.begin(), nationalities.end());
        do {
            // Constraint 10: Norwegian is in first house
            if (nationalities[0] != Nationality::Norwegian) {
                continue;
            }
            std::sort(drinks.begin(), drinks.end());
            do {
                // Constraint 9: Middle house drinks milk
                if (drinks[2] != Drink::Milk) {
                    continue;
                }
                std::sort(pets.begin(), pets.end());
                do {
                    std::sort(hobbies.begin(), hobbies.end());
                    do {
                        if (satisfies_constraints(colors, nationalities, drinks, pets, hobbies)) {
                            Solution solution;
                            for (House i = 0; i < 5; ++i) {
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
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

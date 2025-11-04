#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Reading, Dancing, Painting, Football, Chess };

bool satisfies_constraints(const array<Color, 5>& colors,
                          const array<Nationality, 5>& nationalities,
                          const array<Pet, 5>& pets,
                          const array<Drink, 5>& drinks,
                          const array<Hobby, 5>& hobbies) {
    // Check all constraints
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
            return false;
        }
    }
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
            return false;
        }
    }
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < 5; ++i) {
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
            return false;
        }
    }
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
            return false;
        }
    }
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 0; i < 4; ++i) {
        if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; ++i) {
        if (pets[i] == Pet::Snail && hobbies[i] != Hobby::Dancing) {
            return false;
        }
    }
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < 5; ++i) {
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
            return false;
        }
    }
    // 9. The person in the middle house drinks milk.
    if (drinks[2] != Drink::Milk) return false;
    // 10. The Norwegian lives in the first house.
    if (nationalities[0] != Nationality::Norwegian) return false;
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    found = false;
    for (int i = 0; i < 5; ++i) {
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
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i - 1] == Pet::Horse) || (i < 4 && pets[i + 1] == Pet::Horse)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
            return false;
        }
    }
    // 14. The Japanese person plays chess.
    for (int i = 0; i < 5; ++i) {
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
            return false;
        }
    }
    // 15. The Norwegian lives next to the blue house.
    // Norwegian is always at index 0, so check if index 1 is blue
    if (colors[1] != Color::Blue) {
        return false;
    }
    return true;
}

Solution solve() {
    // Generate all valid permutations upfront to reduce the search space
    array<Color, 5> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    // Generate only color permutations where green is immediately to the right of ivory
    do {
        // Check if the current permutation satisfies constraint 6
        bool valid_colors = false;
        for (int i = 0; i < 4; ++i) {
            if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
                valid_colors = true;
                break;
            }
        }
        if (!valid_colors) continue;
        
        // Nationalities: Norwegian must be first
        array<Nationality, 5> nationalities = {Nationality::Norwegian, Nationality::Englishman, 
                                               Nationality::Spaniard, Nationality::Ukrainian, Nationality::Japanese};
        // Generate permutations where Norwegian is always first
        // Since Norwegian is fixed at index 0, we need to permute the remaining elements
        array<Nationality, 4> remaining_nats = {Nationality::Englishman, Nationality::Spaniard, 
                                               Nationality::Ukrainian, Nationality::Japanese};
        do {
            // Reconstruct the full nationalities array
            array<Nationality, 5> current_nationalities;
            current_nationalities[0] = Nationality::Norwegian;
            for (int i = 0; i < 4; ++i) {
                current_nationalities[i + 1] = remaining_nats[i];
            }
            
            // Drinks: Milk must be in the middle (index 2)
            array<Drink, 5> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
            // Generate permutations where drinks[2] is always Milk
            // To do this, we can fix index 2 and permute the others
            // Remove Milk from the list to permute
            array<Drink, 4> remaining_drinks;
            int index = 0;
            for (const auto& drink : {Drink::Coffee, Drink::Tea, Drink::OrangeJuice, Drink::Water}) {
                remaining_drinks[index++] = drink;
            }
            do {
                // Reconstruct the full drinks array with milk in the middle
                array<Drink, 5> current_drinks;
                for (int i = 0; i < 2; ++i) {
                    current_drinks[i] = remaining_drinks[i];
                }
                current_drinks[2] = Drink::Milk;
                for (int i = 2; i < 4; ++i) {
                    current_drinks[i + 1] = remaining_drinks[i];
                }
                
                // Generate all permutations for pets and hobbies
                array<Pet, 5> pets = {Pet::Dog, Pet::Snail, Pet::Fox, Pet::Horse, Pet::Zebra};
                do {
                    array<Hobby, 5> hobbies = {Hobby::Reading, Hobby::Dancing, Hobby::Painting, Hobby::Football, Hobby::Chess};
                    do {
                        if (satisfies_constraints(colors, current_nationalities, pets, current_drinks, hobbies)) {
                            Solution solution;
                            for (int i = 0; i < 5; ++i) {
                                if (current_drinks[i] == Drink::Water) {
                                    switch (current_nationalities[i]) {
                                        case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                                        case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                                        case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                                        case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                                        case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                                    }
                                }
                                if (pets[i] == Pet::Zebra) {
                                    switch (current_nationalities[i]) {
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
            } while (next_permutation(remaining_drinks.begin(), remaining_drinks.end()));
        } while (next_permutation(remaining_nats.begin(), remaining_nats.end()));
    } while (next_permutation(colors.begin(), colors.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

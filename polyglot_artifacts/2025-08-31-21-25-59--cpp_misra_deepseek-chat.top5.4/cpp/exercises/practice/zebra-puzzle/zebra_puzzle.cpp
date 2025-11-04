#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

constexpr int num_houses = 5;

// Helper function to check if all constraints are satisfied
bool satisfies_constraints(const std::array<Nationality, num_houses>& nationalities,
                          const std::array<Color, num_houses>& colors,
                          const std::array<Drink, num_houses>& drinks,
                          const std::array<Pet, num_houses>& pets,
                          const std::array<Hobby, num_houses>& hobbies) {
    // Check all 15 constraints
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Englishman) && (colors[i] != Color::Red)) {
            return false;
        }
    }
    
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Spaniard) && (pets[i] != Pet::Dog)) {
            return false;
        }
    }
    
    // 4. Coffee is drunk in the green house.
    for (int i = 0; i < num_houses; ++i) {
        if ((colors[i] == Color::Green) && (drinks[i] != Drink::Coffee)) {
            return false;
        }
    }
    
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Ukrainian) && (drinks[i] != Drink::Tea)) {
            return false;
        }
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 0; i < num_houses - 1; ++i) {
        if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < num_houses; ++i) {
        if ((pets[i] == Pet::Snail) && (hobbies[i] != Hobby::Dancing)) {
            return false;
        }
    }
    
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < num_houses; ++i) {
        if ((colors[i] == Color::Yellow) && (hobbies[i] != Hobby::Painting)) {
            return false;
        }
    }
    
    // 9. Milk is drunk in the middle house.
    if (drinks[2] != Drink::Milk) return false;
    
    // 10. The Norwegian lives in the first house.
    if (nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. The person who enjoys reading lives next to the person with the fox.
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            bool adjacent = false;
            if (i > 0 && pets[i - 1] == Pet::Fox) adjacent = true;
            if (i < num_houses - 1 && pets[i + 1] == Pet::Fox) adjacent = true;
            if (!adjacent) return false;
        }
    }
    
    // 12. The painter's house is next to the house with the horse.
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            bool adjacent = false;
            if (i > 0 && pets[i - 1] == Pet::Horse) adjacent = true;
            if (i < num_houses - 1 && pets[i + 1] == Pet::Horse) adjacent = true;
            if (!adjacent) return false;
        }
    }
    
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < num_houses; ++i) {
        if ((hobbies[i] == Hobby::Football) && (drinks[i] != Drink::OrangeJuice)) {
            return false;
        }
    }
    
    // 14. The Japanese person plays chess.
    for (int i = 0; i < num_houses; ++i) {
        if ((nationalities[i] == Nationality::Japanese) && (hobbies[i] != Hobby::Chess)) {
            return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    bool adjacent_to_blue = false;
    if (0 > 0 && colors[0 - 1] == Color::Blue) adjacent_to_blue = true;
    if (0 < num_houses - 1 && colors[0 + 1] == Color::Blue) adjacent_to_blue = true;
    if (!adjacent_to_blue) return false;
    
    return true;
}

Solution solve() {
    std::array<Nationality, num_houses> nationalities = {
        Nationality::Englishman, Nationality::Spaniard, 
        Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese
    };
    std::array<Color, num_houses> colors = {
        Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue
    };
    std::array<Drink, num_houses> drinks = {
        Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water
    };
    std::array<Pet, num_houses> pets = {
        Pet::Dog, Pet::Snail, Pet::Fox, Pet::Horse, Pet::Zebra
    };
    std::array<Hobby, num_houses> hobbies = {
        Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess
    };
    
    // Generate all permutations and check constraints
    do {
        if (nationalities[0] != Nationality::Norwegian) { continue; }
        do {
            if (drinks[2] != Drink::Milk) { continue; }
            do {
                do {
                    do {
                        if (satisfies_constraints(nationalities, colors, drinks, pets, hobbies)) {
                            Solution solution;
                            // Find who drinks water
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
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(colors.begin(), colors.end()));
    } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

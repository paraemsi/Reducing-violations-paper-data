#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct Attributes {
    std::array<Nationality, 5> nationalities;
    std::array<Color, 5> colors;
    std::array<Drink, 5> drinks;
    std::array<Pet, 5> pets;
    std::array<Hobby, 5> hobbies;
};

bool satisfies_constraints(const Attributes& attrs) {
    // Check each constraint
    // 2. Englishman in red house
    for (int i = 0; i < 5; ++i) {
        if (attrs.nationalities[i] == Nationality::Englishman && 
            attrs.colors[i] != Color::Red) {
            return false;
        }
    }
    
    // 3. Spaniard owns dog
    for (int i = 0; i < 5; ++i) {
        if (attrs.nationalities[i] == Nationality::Spaniard && 
            attrs.pets[i] != Pet::Dog) {
            return false;
        }
    }
    
    // 4. Green house drinks coffee
    for (int i = 0; i < 5; ++i) {
        if (attrs.colors[i] == Color::Green && 
            attrs.drinks[i] != Drink::Coffee) {
            return false;
        }
    }
    
    // 5. Ukrainian drinks tea
    for (int i = 0; i < 5; ++i) {
        if (attrs.nationalities[i] == Nationality::Ukrainian && 
            attrs.drinks[i] != Drink::Tea) {
            return false;
        }
    }
    
    // 6. Green is immediately right of ivory
    bool found = false;
    for (int i = 0; i < 4; ++i) {
        if (attrs.colors[i] == Color::Ivory && attrs.colors[i + 1] == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 7. Snail owner likes dancing
    for (int i = 0; i < 5; ++i) {
        if (attrs.pets[i] == Pet::Snails && 
            attrs.hobbies[i] != Hobby::Dancing) {
            return false;
        }
    }
    
    // 8. Yellow house is painter
    for (int i = 0; i < 5; ++i) {
        if (attrs.colors[i] == Color::Yellow && 
            attrs.hobbies[i] != Hobby::Painting) {
            return false;
        }
    }
    
    // 9. Middle house drinks milk
    if (attrs.drinks[2] != Drink::Milk) return false;
    
    // 10. Norwegian in first house
    if (attrs.nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. Reading next to fox
    int reading_pos = -1;
    int fox_pos = -1;
    for (int i = 0; i < 5; ++i) {
        if (attrs.hobbies[i] == Hobby::Reading) reading_pos = i;
        if (attrs.pets[i] == Pet::Fox) fox_pos = i;
    }
    if ((reading_pos == -1) || (fox_pos == -1) || ((std::abs(reading_pos - fox_pos)) != 1)) return false;
    
    // 12. Painter next to horse
    int painting_pos = -1;
    int horse_pos = -1;
    for (int i = 0; i < 5; ++i) {
        if (attrs.hobbies[i] == Hobby::Painting) painting_pos = i;
        if (attrs.pets[i] == Pet::Horse) horse_pos = i;
    }
    if ((painting_pos == -1) || (horse_pos == -1) || ((std::abs(painting_pos - horse_pos)) != 1)) return false;
    
    // 13. Football drinks orange juice
    for (int i = 0; i < 5; ++i) {
        if (attrs.hobbies[i] == Hobby::Football && 
            attrs.drinks[i] != Drink::OrangeJuice) {
            return false;
        }
    }
    
    // 14. Japanese plays chess
    for (int i = 0; i < 5; ++i) {
        if (attrs.nationalities[i] == Nationality::Japanese && 
            attrs.hobbies[i] != Hobby::Chess) {
            return false;
        }
    }
    
    // 15. Norwegian next to blue
    int norwegian_pos = -1;
    int blue_pos = -1;
    for (int i = 0; i < 5; ++i) {
        if (attrs.nationalities[i] == Nationality::Norwegian) norwegian_pos = i;
        if (attrs.colors[i] == Color::Blue) blue_pos = i;
    }
    if ((norwegian_pos == -1) || (blue_pos == -1) || ((std::abs(norwegian_pos - blue_pos)) != 1)) return false;
    
    return true;
}

Solution solve() {
    // Generate all permutations and check constraints
    Attributes attrs;
    
    // Initialize with ordered values which we'll permute
    // The enums need to be in order for std::next_permutation to work correctly
    std::array<Nationality, 5> nationalities = {
        Nationality::Englishman, Nationality::Japanese, Nationality::Norwegian, 
        Nationality::Spaniard, Nationality::Ukrainian
    };
    std::sort(nationalities.begin(), nationalities.end());
    
    std::array<Color, 5> colors = {
        Color::Blue, Color::Green, Color::Ivory, Color::Red, Color::Yellow
    };
    std::sort(colors.begin(), colors.end());
    
    std::array<Drink, 5> drinks = {
        Drink::Coffee, Drink::Milk, Drink::OrangeJuice, Drink::Tea, Drink::Water
    };
    std::sort(drinks.begin(), drinks.end());
    
    std::array<Pet, 5> pets = {
        Pet::Dog, Pet::Fox, Pet::Horse, Pet::Snails, Pet::Zebra
    };
    std::sort(pets.begin(), pets.end());
    
    std::array<Hobby, 5> hobbies = {
        Hobby::Chess, Hobby::Dancing, Hobby::Football, Hobby::Painting, Hobby::Reading
    };
    std::sort(hobbies.begin(), hobbies.end());
    
    do {
        // Check if Norwegian is in first house (constraint 10)
        // This is an optimization to prune early
        bool norwegian_first = false;
        for (int i = 0; i < 5; ++i) {
            if (nationalities[i] == Nationality::Norwegian && i == 0) {
                norwegian_first = true;
                break;
            }
        }
        if (!norwegian_first) continue;
        
        attrs.nationalities = nationalities;
        do {
            attrs.colors = colors;
            do {
                // Check if middle house drinks milk (constraint 9)
                // This needs to be checked before generating permutations
                // But drinks is not assigned yet, so we need to be careful
                // Let's move this check inside the drinks loop
                attrs.drinks = drinks;
                do {
                    // Check if middle house drinks milk
                    if (attrs.drinks[2] != Drink::Milk) continue;
                    
                    attrs.pets = pets;
                    do {
                        attrs.hobbies = hobbies;
                        do {
                            if (satisfies_constraints(attrs)) {
                                // Find who drinks water and owns zebra
                                Solution solution;
                                for (int i = 0; i < 5; ++i) {
                                    if (attrs.drinks[i] == Drink::Water) {
                                        switch (attrs.nationalities[i]) {
                                            case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                                            case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                                            case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                                            case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                                            case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                                        }
                                    }
                                    if (attrs.pets[i] == Pet::Zebra) {
                                        switch (attrs.nationalities[i]) {
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
                        } while (std::next_permutation(attrs.hobbies.begin(), attrs.hobbies.end()));
                    } while (std::next_permutation(attrs.pets.begin(), attrs.pets.end()));
                } while (std::next_permutation(attrs.drinks.begin(), attrs.drinks.end()));
            } while (std::next_permutation(attrs.colors.begin(), attrs.colors.end()));
        } while (std::next_permutation(attrs.nationalities.begin(), attrs.nationalities.end()));
    } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

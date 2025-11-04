#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

// Define the categories
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

// Helper function to convert enum to string
string nationalityToString(Nationality n) {
    switch (n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
    }
    return "";
}

string petToString(Pet p) {
    switch (p) {
        case Pet::Dog: return "dog";
        case Pet::Snails: return "snails";
        case Pet::Fox: return "fox";
        case Pet::Horse: return "horse";
        case Pet::Zebra: return "zebra";
    }
    return "";
}

bool checkConstraints(const array<Nationality, 5>& nationalities,
                      const array<Color, 5>& colors,
                      const array<Drink, 5>& drinks,
                      const array<Pet, 5>& pets,
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
        if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) {
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
    bool found11 = false;
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i - 1] == Pet::Fox) || (i < 4 && pets[i + 1] == Pet::Fox)) {
                found11 = true;
                break;
            }
        }
    }
    if (!found11) return false;
    // 12. The painter's house is next to the house with the horse.
    bool found12 = false;
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i - 1] == Pet::Horse) || (i < 4 && pets[i + 1] == Pet::Horse)) {
                found12 = true;
                break;
            }
        }
    }
    if (!found12) return false;
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
    bool found15 = false;
    if ((0 > 0 && colors[0 - 1] == Color::Blue) || (0 < 4 && colors[0 + 1] == Color::Blue)) {
        found15 = true;
    }
    if (!found15) return false;
    
    return true;
}

// Helper function to check if a value is used in the assignment up to a certain index
template<typename T>
bool isUsed(const array<T, 5>& assignment, int upTo, T value) {
    for (int i = 0; i < upTo; ++i) {
        if (assignment[i] == value) return true;
    }
    return false;
}

// Backtracking function to find the solution
bool findSolution(array<Nationality, 5>& nationalities,
                  array<Color, 5>& colors,
                  array<Drink, 5>& drinks,
                  array<Pet, 5>& pets,
                  array<Hobby, 5>& hobbies,
                  int house,
                  Solution& result) {
    if (house == 5) {
        // Check all constraints
        if (checkConstraints(nationalities, colors, drinks, pets, hobbies)) {
            // Find who drinks water and owns zebra
            for (int i = 0; i < 5; ++i) {
                if (drinks[i] == Drink::Water) {
                    result.drinksWater = nationalityToString(nationalities[i]);
                }
                if (pets[i] == Pet::Zebra) {
                    result.ownsZebra = nationalityToString(nationalities[i]);
                }
            }
            return true;
        }
        return false;
    }

    // Try all possible values for each category at the current house
    // We need to assign values in a way that satisfies constraints as we go
    // Let's generate all permutations by fixing values for each house in order
    
    // For each category, try all possible values that aren't used yet
    // To optimize, we can fix some values based on known constraints
    for (const auto& nationality : {Nationality::Englishman, Nationality::Spaniard, 
                                    Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese}) {
        if (isUsed(nationalities, house, nationality)) continue;
        // Constraint 10: Norwegian lives in first house
        if (house == 0 && nationality != Nationality::Norwegian) continue;
        nationalities[house] = nationality;
        
        for (const auto& color : {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue}) {
            if (isUsed(colors, house, color)) continue;
            // Constraint 2: Englishman lives in red house
            if (nationalities[house] == Nationality::Englishman && color != Color::Red) continue;
            // Constraint 15: Norwegian lives next to blue house
            if (house == 0 && color != Color::Blue && (1 < 5 && colors[1] != Color::Blue)) continue;
            // Check if green is right of ivory is always satisfied when assigning
            colors[house] = color;
            
            for (const auto& drink : {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water}) {
                if (isUsed(drinks, house, drink)) continue;
                // Constraint 9: Middle house drinks milk
                if (house == 2 && drink != Drink::Milk) continue;
                // Constraint 4: Green house drinks coffee
                if (colors[house] == Color::Green && drink != Drink::Coffee) continue;
                // Constraint 5: Ukrainian drinks tea
                if (nationalities[house] == Nationality::Ukrainian && drink != Drink::Tea) continue;
                drinks[house] = drink;
                
                for (const auto& pet : {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra}) {
                    if (isUsed(pets, house, pet)) continue;
                    // Constraint 3: Spaniard owns the dog
                    if (nationalities[house] == Nationality::Spaniard && pet != Pet::Dog) continue;
                    pets[house] = pet;
                    
                    for (const auto& hobby : {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess}) {
                        if (isUsed(hobbies, house, hobby)) continue;
                        // Constraint 7: Snail owner likes dancing
                        if (pet == Pet::Snails && hobby != Hobby::Dancing) continue;
                        // Constraint 8: Yellow house is painter
                        if (colors[house] == Color::Yellow && hobby != Hobby::Painting) continue;
                        // Constraint 13: Football player drinks orange juice
                        if (hobby == Hobby::Football && drink != Drink::OrangeJuice) continue;
                        // Constraint 14: Japanese plays chess
                        if (nationalities[house] == Nationality::Japanese && hobby != Hobby::Chess) continue;
                        hobbies[house] = hobby;
                        
                        // Recurse to next house
                        if (findSolution(nationalities, colors, drinks, pets, hobbies, house + 1, result)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

Solution solve() {
    Solution result;
    array<Nationality, 5> nationalities;
    array<Color, 5> colors;
    array<Drink, 5> drinks;
    array<Pet, 5> pets;
    array<Hobby, 5> hobbies;
    
    findSolution(nationalities, colors, drinks, pets, hobbies, 0, result);
    return result;
}

}  // namespace zebra_puzzle

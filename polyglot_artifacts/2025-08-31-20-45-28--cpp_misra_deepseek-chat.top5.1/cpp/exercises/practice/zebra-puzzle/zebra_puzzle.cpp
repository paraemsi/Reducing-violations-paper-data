#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <string>

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

struct House {
    Nationality nationality;
    Color color;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

bool satisfiesConstraints(const array<House, 5>& houses) {
    // Check all constraints
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Englishman && houses[i].color != Color::Red) {
            return false;
        }
    }
    
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Spaniard && houses[i].pet != Pet::Dog) {
            return false;
        }
    }
    
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].color == Color::Green && houses[i].drink != Drink::Coffee) {
            return false;
        }
    }
    
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Ukrainian && houses[i].drink != Drink::Tea) {
            return false;
        }
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool foundGreenRightOfIvory = false;
    for (int i = 0; i < 4; ++i) {
        if ((houses[i].color == Color::Ivory) && (houses[i + 1].color == Color::Green)) {
            foundGreenRightOfIvory = true;
            break;
        }
    }
    if (!foundGreenRightOfIvory) {
        return false;
    }
    
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].pet == Pet::Snails && houses[i].hobby != Hobby::Dancing) {
            return false;
        }
    }
    
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].color == Color::Yellow && houses[i].hobby != Hobby::Painting) {
            return false;
        }
    }
    
    // 9. The person in the middle house drinks milk.
    if (houses[2].drink != Drink::Milk) {
        return false;
    }
    
    // 10. The Norwegian lives in the first house.
    if (houses[0].nationality != Nationality::Norwegian) {
        return false;
    }
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    bool found = false;
    for (int i = 0; i < 5; ++i) {
        if (houses[i].hobby == Hobby::Reading) {
            if ((i > 0 && houses[i - 1].pet == Pet::Fox) || (i < 4 && houses[i + 1].pet == Pet::Fox)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 12. The painter's house is next to the house with the horse.
    found = false;
    for (int i = 0; i < 5; ++i) {
        if (houses[i].hobby == Hobby::Painting) {
            if ((i > 0 && houses[i - 1].pet == Pet::Horse) || (i < 4 && houses[i + 1].pet == Pet::Horse)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].hobby == Hobby::Football && houses[i].drink != Drink::OrangeJuice) {
            return false;
        }
    }
    
    // 14. The Japanese person plays chess.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Japanese && houses[i].hobby != Hobby::Chess) {
            return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    // Norwegian is in house 0, so only check house 1
    if (houses[1].color != Color::Blue) {
        return false;
    }
    
    return true;
}

Solution solve() {
    array<Nationality, 5> nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                           Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    array<Color, 5> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Drink, 5> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    array<Pet, 5> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Hobby, 5> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    array<House, 5> houses;
    
    // Sort to start permutations from the beginning
    // They are already in order due to initialization
    
    // Generate all permutations
    do {
        // Check if first house is Norwegian
        if (nationalities[0] != Nationality::Norwegian) {
            continue;
        }
        do {
            // Check if second house is blue (Norwegian lives next to blue house, and Norwegian is in first house)
            // So blue must be in second house (index 1)
            if (colors[1] != Color::Blue) {
                continue;
            }
            do {
                // Check if middle house drinks milk
                if (drinks[2] != Drink::Milk) {
                    continue;
                }
                do {
                    do {
                        // Assign values to houses
                        for (int i = 0; i < 5; ++i) {
                            houses[i] = {nationalities[i], colors[i], drinks[i], pets[i], hobbies[i]};
                        }
                        if (satisfiesConstraints(houses)) {
                            // Find who drinks water and owns zebra
                            string waterDrinker;
                            string zebraOwner;
                            for (int i = 0; i < 5; ++i) {
                                if (houses[i].drink == Drink::Water) {
                                    waterDrinker = nationalityToString(houses[i].nationality);
                                }
                                if (houses[i].pet == Pet::Zebra) {
                                    zebraOwner = nationalityToString(houses[i].nationality);
                                }
                            }
                            return {waterDrinker, zebraOwner};
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                    // Reset hobbies to sorted order for next permutation
                    sort(hobbies.begin(), hobbies.end());
                } while (next_permutation(pets.begin(), pets.end()));
                // Reset pets to sorted order for next permutation
                sort(pets.begin(), pets.end());
            } while (next_permutation(drinks.begin(), drinks.end()));
            // Reset drinks to sorted order for next permutation
            sort(drinks.begin(), drinks.end());
        } while (next_permutation(colors.begin(), colors.end()));
        // Reset colors to sorted order for next permutation
        sort(colors.begin(), colors.end());
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return {"", ""};
}

}  // namespace zebra_puzzle

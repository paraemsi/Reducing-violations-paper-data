#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <functional>
#include <string>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

// Define the categories
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
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

// Generate all permutations
template<typename T>
vector<array<T, 5>> generatePermutations() {
    vector<array<T, 5>> result;
    array<T, 5> items;
    for (int i = 0; i < 5; ++i) {
        items[i] = static_cast<T>(i);
    }
    // Sort to ensure next_permutation works correctly
    // The array is already in order due to the loop above
    do {
        result.push_back(items);
    } while (std::next_permutation(items.begin(), items.end()));
    return result;
}

// Check if the constraint is satisfied
bool satisfiesConstraints(
    const array<Color, 5>& colors,
    const array<Nationality, 5>& nationalities,
    const array<Drink, 5>& drinks,
    const array<Pet, 5>& pets,
    const array<Hobby, 5>& hobbies) {
    
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Englishman) && (colors[i] != Color::Red)) {
            return false;
        }
    }
    
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Spaniard) && (pets[i] != Pet::Dog)) {
            return false;
        }
    }
    
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < 5; ++i) {
        if ((colors[i] == Color::Green) && (drinks[i] != Drink::Coffee)) {
            return false;
        }
    }
    
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Ukrainian) && (drinks[i] != Drink::Tea)) {
            return false;
        }
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 0; i < 4; ++i) {
        if ((colors[i] == Color::Ivory) && (colors[i + 1] == Color::Green)) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; ++i) {
        if ((pets[i] == Pet::Snails) && (hobbies[i] != Hobby::Dancing)) {
            return false;
        }
    }
    
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < 5; ++i) {
        if ((colors[i] == Color::Yellow) && (hobbies[i] != Hobby::Painting)) {
            return false;
        }
    }
    
    // 9. The person in the middle house drinks milk. (index 2)
    if (drinks[2] != Drink::Milk) return false;
    
    // 10. The Norwegian lives in the first house. (index 0)
    if (nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    bool readingNextToFox = false;
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i - 1] == Pet::Fox) || (i < 4 && pets[i + 1] == Pet::Fox)) {
                readingNextToFox = true;
                break;
            }
        }
    }
    if (!readingNextToFox) return false;
    
    // 12. The painter's house is next to the house with the horse.
    bool paintingNextToHorse = false;
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i - 1] == Pet::Horse) || (i < 4 && pets[i + 1] == Pet::Horse)) {
                paintingNextToHorse = true;
                break;
            }
        }
    }
    if (!paintingNextToHorse) return false;
    
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < 5; ++i) {
        if ((hobbies[i] == Hobby::Football) && (drinks[i] != Drink::OrangeJuice)) {
            return false;
        }
    }
    
    // 14. The Japanese person plays chess.
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Japanese) && (hobbies[i] != Hobby::Chess)) {
            return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    // Since Norwegian is at index 0, the blue house must be at index 1
    // Check if any adjacent house to index 0 is blue
    bool norwegianNextToBlue = false;
    // Check right neighbor (index 1)
    if (1 < 5 && colors[1] == Color::Blue) {
        norwegianNextToBlue = true;
    }
    // Check left neighbor (index -1 is invalid)
    // So only check index 1
    if (!norwegianNextToBlue) return false;
    
    return true;
}

Solution solve() {
    // Generate all permutations for each category
    auto colorPerms = generatePermutations<Color>();
    auto nationalityPerms = generatePermutations<Nationality>();
    auto drinkPerms = generatePermutations<Drink>();
    auto petPerms = generatePermutations<Pet>();
    auto hobbyPerms = generatePermutations<Hobby>();
    
    // Fix constraints: Norwegian in first house, milk in middle
    // Filter nationality permutations to have Norwegian at index 0
    vector<array<Nationality, 5>> filteredNationalityPerms;
    for (const auto& perm : nationalityPerms) {
        if (perm[0] == Nationality::Norwegian) {
            filteredNationalityPerms.push_back(perm);
        }
    }
    
    // Filter drink permutations to have milk at index 2
    vector<array<Drink, 5>> filteredDrinkPerms;
    for (const auto& perm : drinkPerms) {
        if (perm[2] == Drink::Milk) {
            filteredDrinkPerms.push_back(perm);
        }
    }
    
    // Check all combinations
    for (const auto& colors : colorPerms) {
        for (const auto& nationalities : filteredNationalityPerms) {
            for (const auto& drinks : filteredDrinkPerms) {
                for (const auto& pets : petPerms) {
                    for (const auto& hobbies : hobbyPerms) {
                        if (satisfiesConstraints(colors, nationalities, drinks, pets, hobbies)) {
                            // Find who drinks water and owns zebra
                            Solution solution;
                            for (int i = 0; i < 5; ++i) {
                                if (drinks[i] == Drink::Water) {
                                    solution.drinksWater = nationalityToString(nationalities[i]);
                                }
                                if (pets[i] == Pet::Zebra) {
                                    solution.ownsZebra = nationalityToString(nationalities[i]);
                                }
                            }
                            return solution;
                        }
                    }
                }
            }
        }
    }
    return Solution{};
}

}  // namespace zebra_puzzle

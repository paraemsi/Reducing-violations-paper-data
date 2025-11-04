#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

bool is_valid(const array<Color, 5>& colors,
              const array<Nationality, 5>& nationalities,
              const array<Drink, 5>& drinks,
              const array<Pet, 5>& pets,
              const array<Hobby, 5>& hobbies) {
    // Check all constraints
    // 2. Englishman lives in the red house
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Englishman) && (colors[i] != Color::Red)) return false;
    }
    // 3. Spaniard owns the dog
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Spaniard) && (pets[i] != Pet::Dog)) return false;
    }
    // 4. Green house drinks coffee
    for (int i = 0; i < 5; ++i) {
        if ((colors[i] == Color::Green) && (drinks[i] != Drink::Coffee)) return false;
    }
    // 5. Ukrainian drinks tea
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Ukrainian) && (drinks[i] != Drink::Tea)) return false;
    }
    // 6. Green is immediately right of ivory
    for (int i = 0; i < 4; ++i) {
        if ((colors[i] == Color::Ivory) && (colors[i + 1] != Color::Green)) return false;
    }
    // 7. Snail owner likes dancing
    for (int i = 0; i < 5; ++i) {
        if ((pets[i] == Pet::Snail) && (hobbies[i] != Hobby::Dancing)) return false;
    }
    // 8. Yellow house is painter
    for (int i = 0; i < 5; ++i) {
        if ((colors[i] == Color::Yellow) && (hobbies[i] != Hobby::Painting)) return false;
    }
    // 9. Middle house drinks milk - fixed
    if (drinks[2] != Drink::Milk) return false;
    // 10. Norwegian in first house - fixed
    if (nationalities[0] != Nationality::Norwegian) return false;
    // 11. Reading next to fox
    // 12. Painter next to horse
    // 13. Football drinks orange juice
    for (int i = 0; i < 5; ++i) {
        if ((hobbies[i] == Hobby::Football) && (drinks[i] != Drink::OrangeJuice)) return false;
    }
    // 14. Japanese plays chess
    for (int i = 0; i < 5; ++i) {
        if ((nationalities[i] == Nationality::Japanese) && (hobbies[i] != Hobby::Chess)) return false;
    }
    // 15. Norwegian next to blue
    if ((colors[1] != Color::Blue)) return false;
    
    // Check adjacency constraints
    // 11. Reading next to fox
    bool found = false;
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if (i > 0 && pets[i-1] == Pet::Fox) found = true;
            if (i < 4 && pets[i+1] == Pet::Fox) found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 12. Painter next to horse
    found = false;
    for (int i = 0; i < 5; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if (i > 0 && pets[i-1] == Pet::Horse) found = true;
            if (i < 4 && pets[i+1] == Pet::Horse) found = true;
            break;
        }
    }
    if (!found) return false;
    
    return true;
}

Solution solve() {
    // Generate all permutations while keeping certain values fixed
    // Nationality: index 0 is always Norwegian
    array<Nationality, 5> nationalities = {
        Nationality::Norwegian, Nationality::Englishman, Nationality::Spaniard, 
        Nationality::Ukrainian, Nationality::Japanese
    };
    
    // Drink: index 2 is always Milk
    array<Drink, 5> drinks = {
        Drink::Coffee, Drink::Tea, Drink::Milk, 
        Drink::OrangeJuice, Drink::Water
    };
    
    // Color: index 1 must be Blue (next to Norwegian at index 0)
    array<Color, 5> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Pet, 5> pets = {Pet::Dog, Pet::Snail, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Hobby, 5> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    // Generate permutations while keeping index 0 of nationalities fixed (always Norwegian)
    // To do this, we can generate permutations of the remaining elements
    do {
        // Ensure index 0 is always Norwegian
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        // Generate drinks permutations while keeping index 2 fixed to Milk
        do {
            if (drinks[2] != Drink::Milk) continue;
            
            // Generate colors permutations while keeping index 1 fixed to Blue
            do {
                if (colors[1] != Color::Blue) continue;
                
                // Generate other permutations
                do {
                    do {
                        if (is_valid(colors, nationalities, drinks, pets, hobbies)) {
                            Solution sol;
                            for (int i = 0; i < 5; ++i) {
                                if (drinks[i] == Drink::Water) {
                                    const char* nationality_names[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                                    sol.drinksWater = nationality_names[static_cast<int>(nationalities[i])];
                                }
                                if (pets[i] == Pet::Zebra) {
                                    const char* nationality_names[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                                    sol.ownsZebra = nationality_names[static_cast<int>(nationalities[i])];
                                }
                            }
                            return sol;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(colors.begin(), colors.end()));
        } while (next_permutation(drinks.begin(), drinks.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

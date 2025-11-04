#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <functional>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Reading, Painting, Football, Chess };

bool is_valid(const array<int, 5>& colors, 
              const array<int, 5>& nationalities,
              const array<int, 5>& pets,
              const array<int, 5>& drinks,
              const array<int, 5>& hobbies) {
    // Check all constraints
    // 2. Englishman in red house
    for (int i = 0; i < 5; i++) {
        if (nationalities[i] == static_cast<int>(Nationality::Englishman) && 
            colors[i] != static_cast<int>(Color::Red)) {
            return false;
        }
    }
    // 3. Spaniard owns dog
    for (int i = 0; i < 5; i++) {
        if (nationalities[i] == static_cast<int>(Nationality::Spaniard) && 
            pets[i] != static_cast<int>(Pet::Dog)) {
            return false;
        }
    }
    // 4. Green house drinks coffee
    for (int i = 0; i < 5; i++) {
        if (colors[i] == static_cast<int>(Color::Green) && 
            drinks[i] != static_cast<int>(Drink::Coffee)) {
            return false;
        }
    }
    // 5. Ukrainian drinks tea
    for (int i = 0; i < 5; i++) {
        if (nationalities[i] == static_cast<int>(Nationality::Ukrainian) && 
            drinks[i] != static_cast<int>(Drink::Tea)) {
            return false;
        }
    }
    // 6. Green is immediately right of ivory
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (colors[i] == static_cast<int>(Color::Ivory) && 
            colors[i + 1] == static_cast<int>(Color::Green)) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    // 7. Snail owner likes dancing
    for (int i = 0; i < 5; i++) {
        if (pets[i] == static_cast<int>(Pet::Snail) && 
            hobbies[i] != static_cast<int>(Hobby::Dancing)) {
            return false;
        }
    }
    // 8. Yellow house is painter
    for (int i = 0; i < 5; i++) {
        if (colors[i] == static_cast<int>(Color::Yellow) && 
            hobbies[i] != static_cast<int>(Hobby::Painting)) {
            return false;
        }
    }
    // 9. Middle house drinks milk
    if (drinks[2] != static_cast<int>(Drink::Milk)) return false;
    // 10. Norwegian in first house
    if (nationalities[0] != static_cast<int>(Nationality::Norwegian)) return false;
    // 11. Reader next to fox owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (hobbies[i] == static_cast<int>(Hobby::Reading)) {
            if (i > 0 && pets[i-1] == static_cast<int>(Pet::Fox)) found = true;
            if (i < 4 && pets[i+1] == static_cast<int>(Pet::Fox)) found = true;
            if (!found) return false;
        }
    }
    // 12. Painter next to horse
    found = false;
    for (int i = 0; i < 5; i++) {
        if (hobbies[i] == static_cast<int>(Hobby::Painting)) {
            if (i > 0 && pets[i-1] == static_cast<int>(Pet::Horse)) found = true;
            if (i < 4 && pets[i+1] == static_cast<int>(Pet::Horse)) found = true;
            if (!found) return false;
        }
    }
    // 13. Football player drinks orange juice
    for (int i = 0; i < 5; i++) {
        if (hobbies[i] == static_cast<int>(Hobby::Football) && 
            drinks[i] != static_cast<int>(Drink::OrangeJuice)) {
            return false;
        }
    }
    // 14. Japanese plays chess
    for (int i = 0; i < 5; i++) {
        if (nationalities[i] == static_cast<int>(Nationality::Japanese) && 
            hobbies[i] != static_cast<int>(Hobby::Chess)) {
            return false;
        }
    }
    // 15. Norwegian next to blue
    int nor_pos = 0; // Norwegian is in first house
    if ((nor_pos > 0 && colors[nor_pos-1] == static_cast<int>(Color::Blue)) ||
        (nor_pos < 4 && colors[nor_pos+1] == static_cast<int>(Color::Blue))) {
        return true;
    }
    return false;
}

Solution solve() {
    array<int, 5> base_perm{0, 1, 2, 3, 4};
    
    // Generate separate permutations for each category
    array<int, 5> colors = base_perm;
    do {
        array<int, 5> nationalities = base_perm;
        do {
            // Constraint 10: Norwegian in first house
            if (nationalities[0] != static_cast<int>(Nationality::Norwegian)) continue;
            
            array<int, 5> pets = base_perm;
            do {
                array<int, 5> drinks = base_perm;
                do {
                    // Constraint 9: Middle house drinks milk
                    if (drinks[2] != static_cast<int>(Drink::Milk)) continue;
                    
                    array<int, 5> hobbies = base_perm;
                    do {
                        if (is_valid(colors, nationalities, pets, drinks, hobbies)) {
                            // Find water drinker and zebra owner
                            int water_drinker_pos = -1;
                            int zebra_owner_pos = -1;
                            for (int i = 0; i < 5; i++) {
                                if (drinks[i] == static_cast<int>(Drink::Water)) {
                                    water_drinker_pos = i;
                                }
                                if (pets[i] == static_cast<int>(Pet::Zebra)) {
                                    zebra_owner_pos = i;
                                }
                            }
                            // Get their nationalities
                            const char* nations[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                            return {
                                nations[nationalities[water_drinker_pos]],
                                nations[nationalities[zebra_owner_pos]]
                            };
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(drinks.begin(), drinks.end()));
            } while (next_permutation(pets.begin(), pets.end()));
        } while (next_permutation(nationalities.begin(), nationalities.end()));
    } while (next_permutation(colors.begin(), colors.end()));
    
    return {"", ""};
}

}  // namespace zebra_puzzle

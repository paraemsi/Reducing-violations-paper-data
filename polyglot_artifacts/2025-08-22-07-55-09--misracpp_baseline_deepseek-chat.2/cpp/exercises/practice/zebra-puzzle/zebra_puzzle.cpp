#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

namespace zebra_puzzle {

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

constexpr int num_houses = 5;

template <typename T>
using Houses = array<T, num_houses>;

bool satisfies_all_constraints(const Houses<Color>& colors,
                              const Houses<Nationality>& nationalities,
                              const Houses<Drink>& drinks,
                              const Houses<Pet>& pets,
                              const Houses<Hobby>& hobbies) {
    // Check all constraints
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red)
            return false;
    }
    
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog)
            return false;
    }
    
    // 4. Coffee is drunk in the green house.
    for (int i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee)
            return false;
    }
    
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea)
            return false;
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 1; i < num_houses; ++i) {
        if (colors[i] == Color::Green && colors[i-1] == Color::Ivory) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 7. The snail owner is a dancer.
    for (int i = 0; i < num_houses; ++i) {
        if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing)
            return false;
    }
    
    // 8. The yellow house resident is a painter.
    for (int i = 0; i < num_houses; ++i) {
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting)
            return false;
    }
    
    // 9. Milk is drunk in the middle house.
    if (drinks[2] != Drink::Milk) return false;
    
    // 10. The Norwegian lives in the first house.
    if (nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. The reader lives next to the fox owner.
    found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Reading) {
            if ((i > 0 && pets[i-1] == Pet::Fox) || (i < num_houses-1 && pets[i+1] == Pet::Fox)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 12. The painter's house is next to the house with the horse.
    found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Painting) {
            if ((i > 0 && pets[i-1] == Pet::Horse) || (i < num_houses-1 && pets[i+1] == Pet::Horse)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 13. The footballer drinks orange juice.
    for (int i = 0; i < num_houses; ++i) {
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice)
            return false;
    }
    
    // 14. The Japanese is a chess player.
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess)
            return false;
    }
    
    // 15. The Norwegian lives next to the blue house.
    if (!((0 > 0 && colors[0] == Color::Blue) || (0 < num_houses-1 && colors[1] == Color::Blue))) {
        if (colors[1] != Color::Blue) return false;
    }
    
    return true;
}

Solution solve() {
    Houses<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    Houses<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    Houses<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    Houses<Pet> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    Houses<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    do {
        // Constraint 10: Norwegian in first house
        if (nationalities[0] != Nationality::Norwegian) continue;
        do {
            // Constraint 9: Milk in middle house
            if (drinks[2] != Drink::Milk) continue;
            do {
                do {
                    do {
                        if (satisfies_all_constraints(colors, nationalities, drinks, pets, hobbies)) {
                            Solution solution;
                            for (int i = 0; i < num_houses; ++i) {
                                if (drinks[i] == Drink::Water) {
                                    const string nationalities_str[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                                    solution.drinksWater = nationalities_str[static_cast<int>(nationalities[i])];
                                }
                                if (pets[i] == Pet::Zebra) {
                                    const string nationalities_str[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                                    solution.ownsZebra = nationalities_str[static_cast<int>(nationalities[i])];
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(nationalities.begin(), nationalities.end()));
    } while (next_permutation(colors.begin(), colors.end()));
    
    return Solution();
}

}  // namespace zebra_puzzle

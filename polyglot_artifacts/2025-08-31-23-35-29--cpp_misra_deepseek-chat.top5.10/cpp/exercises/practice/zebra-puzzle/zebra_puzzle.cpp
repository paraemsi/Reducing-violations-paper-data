#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>
#include <optional>
#include <vector>

namespace zebra_puzzle {

namespace {

using namespace std;

constexpr int num_houses = 5;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Reading, Dancing, Painting, Football, Chess };

array<Color, num_houses> colors;
array<Nationality, num_houses> nationalities;
array<Pet, num_houses> pets;
array<Drink, num_houses> drinks;
array<Hobby, num_houses> hobbies;

Solution solution;

bool checkConstraints() {
    // Check all constraints
    for (int i = 0; i < num_houses; ++i) {
        // 2. The Englishman lives in the red house.
        if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) return false;
        // 3. The Spaniard owns the dog.
        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) return false;
        // 4. The person in the green house drinks coffee.
        if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) return false;
        // 5. The Ukrainian drinks tea.
        if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) return false;
        // 8. The person in the yellow house is a painter.
        if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && drinks[i] != Drink::Milk) return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && nationalities[i] != Nationality::Norwegian) return false;
        // 13. The person who plays football drinks orange juice.
        if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) return false;
        // 14. The Japanese person plays chess.
        if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) return false;
        // 7. The snail owner likes to go dancing.
        if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) return false;
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
    
    // 15. The Norwegian lives next to the blue house.
    int norwegian_index = -1;
    for (int i = 0; i < num_houses; ++i) {
        if (nationalities[i] == Nationality::Norwegian) {
            norwegian_index = i;
            break;
        }
    }
    if (norwegian_index == -1) return false;
    if (!((norwegian_index > 0 && colors[norwegian_index-1] == Color::Blue) || 
          (norwegian_index < num_houses-1 && colors[norwegian_index+1] == Color::Blue))) {
        return false;
    }
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
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
    
    return true;
}

template<typename T>
void generatePermutations(array<T, num_houses>& arr, int index, const array<T, num_houses>& elements, 
                         array<bool, num_houses>& used, function<void()> callback) {
    if (index == num_houses) {
        callback();
        return;
    }
    for (int i = 0; i < num_houses; ++i) {
        if (!used[i]) {
            used[i] = true;
            arr[index] = elements[i];
            generatePermutations(arr, index + 1, elements, used, callback);
            used[i] = false;
        }
    }
}

}  // namespace

Solution solve() {
    // Fix known values
    nationalities[0] = Nationality::Norwegian;
    drinks[2] = Drink::Milk;
    
    // Define all possible values
    const array<Color, num_houses> all_colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    const array<Nationality, num_houses> all_nationalities = {
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
        Nationality::Norwegian, Nationality::Japanese
    };
    const array<Pet, num_houses> all_pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    const array<Drink, num_houses> all_drinks = {
        Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water
    };
    const array<Hobby, num_houses> all_hobbies = {
        Hobby::Reading, Hobby::Dancing, Hobby::Painting, Hobby::Football, Hobby::Chess
    };
    
    // Generate all permutations for each category, skipping fixed values
    array<bool, num_houses> used{};
    // Generate permutations for colors
    generatePermutations(colors, 0, all_colors, used, [&]() {
        // Generate nationalities (first is fixed)
        array<bool, num_houses> used_nat{};
        used_nat[3] = true; // Norwegian is at index 3 in all_nationalities
        nationalities[0] = Nationality::Norwegian;
        generatePermutations(nationalities, 1, all_nationalities, used_nat, [&]() {
            // Generate drinks (middle is fixed)
            array<bool, num_houses> used_drink{};
            used_drink[2] = true; // Milk is at index 2 in all_drinks
            drinks[2] = Drink::Milk;
            generatePermutations(drinks, 0, all_drinks, used_drink, [&]() {
                // Generate pets
                array<bool, num_houses> used_pet{};
                generatePermutations(pets, 0, all_pets, used_pet, [&]() {
                    // Generate hobbies
                    array<bool, num_houses> used_hobby{};
                    generatePermutations(hobbies, 0, all_hobbies, used_hobby, [&]() {
                        if (checkConstraints()) {
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
                        }
                    });
                });
            });
        });
    });
    
    return solution;
}

}  // namespace zebra_puzzle

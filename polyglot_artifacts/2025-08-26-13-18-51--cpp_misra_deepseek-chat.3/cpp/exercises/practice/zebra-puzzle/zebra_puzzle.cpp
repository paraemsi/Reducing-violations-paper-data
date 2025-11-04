#include "zebra_puzzle.h"
#include <array>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iostream>

namespace zebra_puzzle {

using namespace std;

Solution solve() {
    // Define indices for easier access
    constexpr int32_t num_houses = 5;
    
    // Define all possible values
    enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum class Color { Red, Green, Ivory, Yellow, Blue };
    enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum class Pet { Dog, Snails, Fox, Horse, Zebra };
    enum class Hobby { Dancing, Painting, Reading, Football, Chess };
    
    // We'll generate all permutations and check constraints
    vector<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
                                         Nationality::Norwegian, Nationality::Japanese};
    vector<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    vector<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    vector<Pet> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    vector<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    // Track the solution
    array<Nationality, num_houses> sol_nat;
    array<Color, num_houses> sol_col;
    array<Drink, num_houses> sol_drink;
    array<Pet, num_houses> sol_pet;
    array<Hobby, num_houses> sol_hobby;
    
    // Generate all permutations and check constraints
    do {
        // Norwegian in first house
        if (nationalities[0] != Nationality::Norwegian) continue;
        do {
            // Milk in middle house (index 2)
            if (drinks[2] != Drink::Milk) continue;
            do {
                do {
                    do {
                        // Check all constraints
                        // Check each house
                        bool valid = true;
                        for (int i = 0; i < num_houses; i++) {
                            // Constraint 2
                            if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) valid = false;
                            // Constraint 3
                            if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) valid = false;
                            // Constraint 4
                            if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) valid = false;
                            // Constraint 5
                            if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) valid = false;
                            // Constraint 6
                            if (i > 0 && colors[i] == Color::Green && colors[i-1] != Color::Ivory) valid = false;
                            // Constraint 7
                            if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) valid = false;
                            // Constraint 8
                            if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) valid = false;
                            // Constraint 13
                            if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) valid = false;
                            // Constraint 14
                            if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) valid = false;
                        }
                        // Constraint 15: Norwegian next to blue house
                        // Find Norwegian's index
                        int norwegian_idx = -1;
                        for (int i = 0; i < num_houses; i++) {
                            if (nationalities[i] == Nationality::Norwegian) norwegian_idx = i;
                        }
                        if (norwegian_idx != -1) {
                            bool next_to_blue = false;
                            if (norwegian_idx > 0 && colors[norwegian_idx-1] == Color::Blue) next_to_blue = true;
                            if (norwegian_idx < num_houses-1 && colors[norwegian_idx+1] == Color::Blue) next_to_blue = true;
                            if (!next_to_blue) valid = false;
                        }
                        // Add other between-house constraints here
                        if (valid) {
                            // Found valid solution
                            Solution solution;
                            // Find water drinker and zebra owner
                            for (int i = 0; i < num_houses; i++) {
                                if (drinks[i] == Drink::Water) {
                                    const char* nationalities_str[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                                    solution.drinksWater = nationalities_str[static_cast<int>(nationalities[i])];
                                }
                                if (pets[i] == Pet::Zebra) {
                                    const char* nationalities_str[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                                    solution.ownsZebra = nationalities_str[static_cast<int>(nationalities[i])];
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(colors.begin(), colors.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    // Should not reach here
    return Solution();
}

}  // namespace zebra_puzzle

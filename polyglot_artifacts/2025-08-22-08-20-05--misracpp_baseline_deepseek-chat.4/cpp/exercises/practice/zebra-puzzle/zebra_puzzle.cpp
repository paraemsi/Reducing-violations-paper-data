#include "zebra_puzzle.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <array>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace zebra_puzzle {

// Define all possible values
const vector<string> colors = {"red", "green", "ivory", "yellow", "blue"};
const vector<string> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const vector<string> pets = {"dog", "snails", "fox", "horse", "zebra"};
const vector<string> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
const vector<string> hobbies = {"dancing", "painting", "reading", "football", "chess"};

// Check if all constraints are satisfied
bool satisfies_constraints(const array<int, 5>& color_idx, 
                          const array<int, 5>& nationality_idx, 
                          const array<int, 5>& pet_idx, 
                          const array<int, 5>& drink_idx, 
                          const array<int, 5>& hobby_idx) {
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < 5; i++) {
        if (nationalities[nationality_idx[i]] == "Englishman" && colors[color_idx[i]] != "red") {
            return false;
        }
    }
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < 5; i++) {
        if (nationalities[nationality_idx[i]] == "Spaniard" && pets[pet_idx[i]] != "dog") {
            return false;
        }
    }
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < 5; i++) {
        if (colors[color_idx[i]] == "green" && drinks[drink_idx[i]] != "coffee") {
            return false;
        }
    }
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < 5; i++) {
        if (nationalities[nationality_idx[i]] == "Ukrainian" && drinks[drink_idx[i]] != "tea") {
            return false;
        }
    }
    // 6. The green house is immediately to the right of the ivory house.
    bool found_green_right_of_ivory = false;
    for (int i = 0; i < 4; i++) {
        if (colors[color_idx[i]] == "ivory" && colors[color_idx[i + 1]] == "green") {
            found_green_right_of_ivory = true;
            break;
        }
    }
    if (!found_green_right_of_ivory) return false;
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; i++) {
        if (pets[pet_idx[i]] == "snails" && hobbies[hobby_idx[i]] != "dancing") {
            return false;
        }
    }
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < 5; i++) {
        if (colors[color_idx[i]] == "yellow" && hobbies[hobby_idx[i]] != "painting") {
            return false;
        }
    }
    // 9. The person in the middle house drinks milk.
    if (drinks[drink_idx[2]] != "milk") return false;
    // 10. The Norwegian lives in the first house.
    if (nationalities[nationality_idx[0]] != "Norwegian") return false;
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    for (int i = 0; i < 5; i++) {
        if (hobbies[hobby_idx[i]] == "reading") {
            bool found = false;
            if (i > 0 && pets[pet_idx[i - 1]] == "fox") found = true;
            if (i < 4 && pets[pet_idx[i + 1]] == "fox") found = true;
            if (!found) return false;
        }
    }
    // 12. The painter's house is next to the house with the horse.
    for (int i = 0; i < 5; i++) {
        if (hobbies[hobby_idx[i]] == "painting") {
            bool found = false;
            if (i > 0 && pets[pet_idx[i - 1]] == "horse") found = true;
            if (i < 4 && pets[pet_idx[i + 1]] == "horse") found = true;
            if (!found) return false;
        }
    }
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < 5; i++) {
        if (hobbies[hobby_idx[i]] == "football" && drinks[drink_idx[i]] != "orange juice") {
            return false;
        }
    }
    // 14. The Japanese person plays chess.
    for (int i = 0; i < 5; i++) {
        if (nationalities[nationality_idx[i]] == "Japanese" && hobbies[hobby_idx[i]] != "chess") {
            return false;
        }
    }
    // 15. The Norwegian lives next to the blue house.
    // Since Norwegian is in first house (index 0), check if blue house is next to it (index 1)
    // Check if the second house is blue
    if (colors[color_idx[1]] != "blue") return false;
    
    return true;
}

Solution solve() {
    // Generate all permutations for each attribute
    // We need to find the combination that satisfies all constraints
    array<int, 5> indices = {0, 1, 2, 3, 4};
    
    do { // color permutations
        auto color = indices;
        do { // nationality permutations
            auto nationality = indices;
            // Apply fixed constraints early to prune
            if (nationalities[nationality[0]] != "Norwegian") continue;
            do { // pet permutations
                auto pet = indices;
                do { // drink permutations
                    auto drink = indices;
                    // The person in the middle house drinks milk
                    if (drinks[drink[2]] != "milk") continue;
                    do { // hobby permutations
                        auto hobby = indices;
                        if (satisfies_constraints(color, nationality, pet, drink, hobby)) {
                            // Find which resident drinks water and owns zebra
                            Solution solution;
                            for (int i = 0; i < 5; i++) {
                                if (drinks[drink[i]] == "water") {
                                    solution.drinksWater = nationalities[nationality[i]];
                                }
                                if (pets[pet[i]] == "zebra") {
                                    solution.ownsZebra = nationalities[nationality[i]];
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobby.begin(), hobby.end()));
                } while (next_permutation(drink.begin(), drink.end()));
            } while (next_permutation(pet.begin(), pet.end()));
        } while (next_permutation(nationality.begin(), nationality.end()));
    } while (next_permutation(color.begin(), color.end()));
    
    throw runtime_error("No solution found");
}

}  // namespace zebra_puzzle

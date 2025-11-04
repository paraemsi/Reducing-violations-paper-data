#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace zebra_puzzle {

using namespace std;

// Define all possible values
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

bool satisfies_constraints(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        
        // 2. Englishman in red house
        if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
        // 3. Spaniard owns dog
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
        // 4. Green house drinks coffee
        if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
        // 5. Ukrainian drinks tea
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
        // 7. Snail owner likes dancing
        if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
        // 8. Yellow house is painter
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
        // 13. Football player drinks orange juice
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
        // 14. Japanese plays chess
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
    }
    
    // 6. Green is immediately to the right of ivory
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == Color::Ivory && houses[i + 1].color == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 9. Middle house drinks milk
    if (houses[2].drink != Drink::Milk) return false;
    
    // 10. Norwegian lives in first house
    if (houses[0].nationality != Nationality::Norwegian) return false;
    
    // 11. Reader next to fox owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            if (i > 0 && houses[i - 1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i + 1].pet == Pet::Fox) found = true;
            if (found) break;
        }
    }
    if (!found) return false;
    
    // 12. Painter next to horse owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Painting) {
            if (i > 0 && houses[i - 1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i + 1].pet == Pet::Horse) found = true;
            if (found) break;
        }
    }
    if (!found) return false;
    
    // 15. Norwegian lives next to blue house
    found = false;
    int norwegian_idx = -1;
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == Nationality::Norwegian) {
            norwegian_idx = i;
            break;
        }
    }
    if (norwegian_idx > 0 && houses[norwegian_idx - 1].color == Color::Blue) found = true;
    if (norwegian_idx < 4 && houses[norwegian_idx + 1].color == Color::Blue) found = true;
    if (!found) return false;
    
    return true;
}

template<typename T>
void generate_permutations(vector<vector<T>>& result, vector<T> current, vector<bool> used) {
    if (current.size() == 5) {
        result.push_back(current);
        return;
    }
    for (int i = 0; i < 5; i++) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(static_cast<T>(i));
            generate_permutations(result, current, used);
            current.pop_back();
            used[i] = false;
        }
    }
}

Solution solve() {
    // Generate all permutations for each attribute
    vector<vector<Color>> color_perms;
    vector<vector<Nationality>> nationality_perms;
    vector<vector<Pet>> pet_perms;
    vector<vector<Drink>> drink_perms;
    vector<vector<Hobby>> hobby_perms;
    
    generate_permutations(color_perms, vector<Color>{}, vector<bool>(5, false));
    generate_permutations(nationality_perms, vector<Nationality>{}, vector<bool>(5, false));
    generate_permutations(pet_perms, vector<Pet>{}, vector<bool>(5, false));
    generate_permutations(drink_perms, vector<Drink>{}, vector<bool>(5, false));
    generate_permutations(hobby_perms, vector<Hobby>{}, vector<bool>(5, false));
    
    // Pre-filter nationalities to have Norwegian in first house
    vector<vector<Nationality>> filtered_nationality_perms;
    for (const auto& perm : nationality_perms) {
        if (perm[0] == Nationality::Norwegian) {
            filtered_nationality_perms.push_back(perm);
        }
    }
    
    // Pre-filter drinks to have milk in middle house
    vector<vector<Drink>> filtered_drink_perms;
    for (const auto& perm : drink_perms) {
        if (perm[2] == Drink::Milk) {
            filtered_drink_perms.push_back(perm);
        }
    }
    
    // Try all combinations
    for (const auto& colors : color_perms) {
        // Check if green is immediately to the right of ivory
        bool green_right_of_ivory = false;
        for (int i = 0; i < 4; i++) {
            if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                green_right_of_ivory = true;
                break;
            }
        }
        if (!green_right_of_ivory) continue;
        
        for (const auto& nationalities : filtered_nationality_perms) {
            // Check if Norwegian is next to blue house
            int norwegian_idx = -1;
            for (int i = 0; i < 5; i++) {
                if (nationalities[i] == Nationality::Norwegian) {
                    norwegian_idx = i;
                    break;
                }
            }
            bool norwegian_next_to_blue = false;
            if (norwegian_idx > 0 && colors[norwegian_idx - 1] == Color::Blue) norwegian_next_to_blue = true;
            if (norwegian_idx < 4 && colors[norwegian_idx + 1] == Color::Blue) norwegian_next_to_blue = true;
            if (!norwegian_next_to_blue) continue;
            
            for (const auto& drinks : filtered_drink_perms) {
                for (const auto& pets : pet_perms) {
                    for (const auto& hobbies : hobby_perms) {
                        // Build houses
                        array<House, 5> houses;
                        for (int i = 0; i < 5; i++) {
                            houses[i] = {
                                colors[i],
                                nationalities[i],
                                pets[i],
                                drinks[i],
                                hobbies[i]
                            };
                        }
                        
                        // Check all constraints
                        if (satisfies_constraints(houses)) {
                            // Found valid configuration
                            Solution result;
                            
                            // Find who drinks water
                            for (int i = 0; i < 5; i++) {
                                if (houses[i].drink == Drink::Water) {
                                    switch (houses[i].nationality) {
                                        case Nationality::Englishman: result.drinksWater = "Englishman"; break;
                                        case Nationality::Spaniard: result.drinksWater = "Spaniard"; break;
                                        case Nationality::Ukrainian: result.drinksWater = "Ukrainian"; break;
                                        case Nationality::Norwegian: result.drinksWater = "Norwegian"; break;
                                        case Nationality::Japanese: result.drinksWater = "Japanese"; break;
                                    }
                                    break;
                                }
                            }
                            
                            // Find who owns zebra
                            for (int i = 0; i < 5; i++) {
                                if (houses[i].pet == Pet::Zebra) {
                                    switch (houses[i].nationality) {
                                        case Nationality::Englishman: result.ownsZebra = "Englishman"; break;
                                        case Nationality::Spaniard: result.ownsZebra = "Spaniard"; break;
                                        case Nationality::Ukrainian: result.ownsZebra = "Ukrainian"; break;
                                        case Nationality::Norwegian: result.ownsZebra = "Norwegian"; break;
                                        case Nationality::Japanese: result.ownsZebra = "Japanese"; break;
                                    }
                                    break;
                                }
                            }
                            return result;
                        }
                    }
                }
            }
        }
    }
    
    // Should not reach here if puzzle is valid
    throw runtime_error("No solution found");
}

}  // namespace zebra_puzzle

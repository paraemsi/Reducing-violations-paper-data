#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <optional>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Reading, Dancing, Painting, Football, Chess };

constexpr int num_houses = 5;

struct Assignment {
    array<Color, num_houses> colors;
    array<Nationality, num_houses> nationalities;
    array<Pet, num_houses> pets;
    array<Drink, num_houses> drinks;
    array<Hobby, num_houses> hobbies;
};

bool check_constraints(const Assignment& assignment) {
    // Check all constraints
    for (int i = 0; i < num_houses; ++i) {
        // 2. Englishman in red house
        if (assignment.nationalities[i] == Nationality::Englishman && 
            assignment.colors[i] != Color::Red) {
            return false;
        }
        // 3. Spaniard owns dog
        if (assignment.nationalities[i] == Nationality::Spaniard && 
            assignment.pets[i] != Pet::Dog) {
            return false;
        }
        // 4. Green house drinks coffee
        if (assignment.colors[i] == Color::Green && 
            assignment.drinks[i] != Drink::Coffee) {
            return false;
        }
        // 5. Ukrainian drinks tea
        if (assignment.nationalities[i] == Nationality::Ukrainian && 
            assignment.drinks[i] != Drink::Tea) {
            return false;
        }
        // 7. Snail owner likes dancing
        if (assignment.pets[i] == Pet::Snails && 
            assignment.hobbies[i] != Hobby::Dancing) {
            return false;
        }
        // 8. Yellow house is painter
        if (assignment.colors[i] == Color::Yellow && 
            assignment.hobbies[i] != Hobby::Painting) {
            return false;
        }
        // 13. Football player drinks orange juice
        if (assignment.hobbies[i] == Hobby::Football && 
            assignment.drinks[i] != Drink::OrangeJuice) {
            return false;
        }
        // 14. Japanese plays chess
        if (assignment.nationalities[i] == Nationality::Japanese && 
            assignment.hobbies[i] != Hobby::Chess) {
            return false;
        }
    }
    
    // 6. Green is immediately right of ivory
    bool found = false;
    for (int i = 0; i < num_houses - 1; ++i) {
        if (assignment.colors[i] == Color::Ivory && 
            assignment.colors[i + 1] == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 9. Middle house drinks milk
    if (assignment.drinks[2] != Drink::Milk) return false;
    
    // 10. Norwegian in first house
    if (assignment.nationalities[0] != Nationality::Norwegian) return false;
    
    // 11. Reader next to fox owner
    found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (assignment.hobbies[i] == Hobby::Reading) {
            if (i > 0 && assignment.pets[i - 1] == Pet::Fox) found = true;
            if (i < num_houses - 1 && assignment.pets[i + 1] == Pet::Fox) found = true;
            if (found) break;
        }
    }
    if (!found) return false;
    
    // 12. Painter next to horse owner
    found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (assignment.hobbies[i] == Hobby::Painting) {
            if (i > 0 && assignment.pets[i - 1] == Pet::Horse) found = true;
            if (i < num_houses - 1 && assignment.pets[i + 1] == Pet::Horse) found = true;
            if (found) break;
        }
    }
    if (!found) return false;
    
    // 15. Norwegian next to blue house
    found = false;
    for (int i = 0; i < num_houses; ++i) {
        if (assignment.nationalities[i] == Nationality::Norwegian) {
            if (i > 0 && assignment.colors[i - 1] == Color::Blue) found = true;
            if (i < num_houses - 1 && assignment.colors[i + 1] == Color::Blue) found = true;
            if (found) break;
        }
    }
    if (!found) return false;
    
    return true;
}

optional<Assignment> find_solution(int house, Assignment& assignment, 
                                array<bool, num_houses>& used_colors,
                                array<bool, num_houses>& used_nationalities,
                                array<bool, num_houses>& used_pets,
                                array<bool, num_houses>& used_drinks,
                                array<bool, num_houses>& used_hobbies) {
    if (house == num_houses) {
        return solution;
    }
    
    // Try all possible assignments for the current house
    for (int color = 0; color < num_houses; ++color) {
        if (used_colors[color]) continue;
        // Check constraints that involve color
        solution.colors[house] = static_cast<Color>(color);
        used_colors[color] = true;
        
        for (int nationality = 0; nationality < num_houses; ++nationality) {
            if (used_nationalities[nationality]) continue;
            solution.nationalities[house] = static_cast<Nationality>(nationality);
            used_nationalities[nationality] = true;
            
            // Constraint 2: Englishman in red house
            if (nationality == static_cast<int>(Nationality::Englishman) && 
                color != static_cast<int>(Color::Red)) {
                used_nationalities[nationality] = false;
                continue;
            }
            // Constraint 10: Norwegian in first house
            if (house == 0 && nationality != static_cast<int>(Nationality::Norwegian)) {
                used_nationalities[nationality] = false;
                continue;
            }
            // Constraint 15: Norwegian next to blue house
            // This is tricky to check during assignment
            
            for (int pet = 0; pet < num_houses; ++pet) {
                if (used_pets[pet]) continue;
                solution.pets[house] = static_cast<Pet>(pet);
                used_pets[pet] = true;
                
                // Constraint 3: Spaniard owns dog
                if (nationality == static_cast<int>(Nationality::Spaniard) && 
                    pet != static_cast<int>(Pet::Dog)) {
                    used_pets[pet] = false;
                    continue;
                }
                
                for (int drink = 0; drink < num_houses; ++drink) {
                    if (used_drinks[drink]) continue;
                    solution.drinks[house] = static_cast<Drink>(drink);
                    used_drinks[drink] = true;
                    
                    // Constraint 4: Green house drinks coffee
                    if (color == static_cast<int>(Color::Green) && 
                        drink != static_cast<int>(Drink::Coffee)) {
                        used_drinks[drink] = false;
                        continue;
                    }
                    // Constraint 5: Ukrainian drinks tea
                    if (nationality == static_cast<int>(Nationality::Ukrainian) && 
                        drink != static_cast<int>(Drink::Tea)) {
                        used_drinks[drink] = false;
                        continue;
                    }
                    // Constraint 9: Middle house drinks milk
                    if (house == 2 && drink != static_cast<int>(Drink::Milk)) {
                        used_drinks[drink] = false;
                        continue;
                    }
                    
                    for (int hobby = 0; hobby < num_houses; ++hobby) {
                        if (used_hobbies[hobby]) continue;
                        solution.hobbies[house] = static_cast<Hobby>(hobby);
                        used_hobbies[hobby] = true;
                        
                        // Check remaining constraints
                        // Recursively move to next house
                        auto result = find_solution(house + 1, solution, used_colors, used_nationalities,
                                                  used_pets, used_drinks, used_hobbies);
                        if (result) {
                            return result;
                        }
                        
                        used_hobbies[hobby] = false;
                    }
                    used_drinks[drink] = false;
                }
                used_pets[pet] = false;
            }
            used_nationalities[nationality] = false;
        }
        used_colors[color] = false;
    }
    return nullopt;
}

Solution solve() {
    Assignment assignment{};
    array<bool, num_houses> used_colors{};
    array<bool, num_houses> used_nationalities{};
    array<bool, num_houses> used_pets{};
    array<bool, num_houses> used_drinks{};
    array<bool, num_houses> used_hobbies{};
    
    auto result = find_solution(0, assignment, used_colors, used_nationalities,
                               used_pets, used_drinks, used_hobbies);
    
    // Extract the answer
    if (result) {
        // Check all constraints at the end to be sure
        if (check_constraints(*result)) {
            // Find who drinks water and owns zebra
            string water_drinker;
            string zebra_owner;
            for (int i = 0; i < num_houses; ++i) {
                if (result->drinks[i] == Drink::Water) {
                    switch (result->nationalities[i]) {
                        case Nationality::Englishman: water_drinker = "Englishman"; break;
                        case Nationality::Spaniard: water_drinker = "Spaniard"; break;
                        case Nationality::Ukrainian: water_drinker = "Ukrainian"; break;
                        case Nationality::Norwegian: water_drinker = "Norwegian"; break;
                        case Nationality::Japanese: water_drinker = "Japanese"; break;
                    }
                }
                if (result->pets[i] == Pet::Zebra) {
                    switch (result->nationalities[i]) {
                        case Nationality::Englishman: zebra_owner = "Englishman"; break;
                        case Nationality::Spaniard: zebra_owner = "Spaniard"; break;
                        case Nationality::Ukrainian: zebra_owner = "Ukrainian"; break;
                        case Nationality::Norwegian: zebra_owner = "Norwegian"; break;
                        case Nationality::Japanese: zebra_owner = "Japanese"; break;
                    }
                }
            }
            return Solution{water_drinker, zebra_owner};
        }
    }
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

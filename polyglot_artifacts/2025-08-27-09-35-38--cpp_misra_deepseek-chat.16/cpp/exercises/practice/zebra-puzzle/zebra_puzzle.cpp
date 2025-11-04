#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <string>
#include <cmath>
#include <iostream>

namespace zebra_puzzle {

using namespace std;

enum class Nationality : int8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color : int8_t { Red, Green, Ivory, Yellow, Blue };
enum class Pet : int8_t { Dog, Snails, Fox, Horse, Zebra };
enum class Drink : int8_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby : int8_t { Dancing, Painting, Reading, Football, Chess };

constexpr int8_t num_houses = 5;

struct House {
    int8_t color;
    int8_t nationality;
    int8_t pet;
    int8_t drink;
    int8_t hobby;
};

bool is_valid(const array<House, num_houses>& houses) {
    for (int8_t i = 0; i < num_houses; ++i) {
        // Check if all attributes are unique per category
        for (int8_t j = i + 1; j < num_houses; ++j) {
            if (houses[i].color == houses[j].color) return false;
            if (houses[i].nationality == houses[j].nationality) return false;
            if (houses[i].pet == houses[j].pet) return false;
            if (houses[i].drink == houses[j].drink) return false;
            if (houses[i].hobby == houses[j].hobby) return false;
        }
    }
    
    // Check all constraints
    for (int8_t i = 0; i < num_houses; ++i) {
        const auto& h = houses[i];
        // 2. Englishman in red house
        if (h.nationality == static_cast<int8_t>(Nationality::Englishman) && 
            h.color != static_cast<int8_t>(Color::Red)) return false;
        // 3. Spaniard owns dog
        if (h.nationality == static_cast<int8_t>(Nationality::Spaniard) && 
            h.pet != static_cast<int8_t>(Pet::Dog)) return false;
        // 4. Green house drinks coffee
        if (h.color == static_cast<int8_t>(Color::Green) && 
            h.drink != static_cast<int8_t>(Drink::Coffee)) return false;
        // 5. Ukrainian drinks tea
        if (h.nationality == static_cast<int8_t>(Nationality::Ukrainian) && 
            h.drink != static_cast<int8_t>(Drink::Tea)) return false;
        // 7. Snail owner dances
        if (h.pet == static_cast<int8_t>(Pet::Snails) && 
            h.hobby != static_cast<int8_t>(Hobby::Dancing)) return false;
        // 8. Yellow house is painter
        if (h.color == static_cast<int8_t>(Color::Yellow) && 
            h.hobby != static_cast<int8_t>(Hobby::Painting)) return false;
        // 13. Football drinks orange juice
        if (h.hobby == static_cast<int8_t>(Hobby::Football) && 
            h.drink != static_cast<int8_t>(Drink::OrangeJuice)) return false;
        // 14. Japanese plays chess
        if (h.nationality == static_cast<int8_t>(Nationality::Japanese) && 
            h.hobby != static_cast<int8_t>(Hobby::Chess)) return false;
    }
    
    // Check constraints that involve multiple houses
    // 6. Green is immediately to the right of ivory
    bool found = false;
    for (int8_t i = 0; i < num_houses - 1; ++i) {
        if (houses[i].color == static_cast<int8_t>(Color::Ivory) && 
            houses[i + 1].color == static_cast<int8_t>(Color::Green)) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 9. Middle house drinks milk
    if (houses[2].drink != static_cast<int8_t>(Drink::Milk)) return false;
    // 10. Norwegian in first house
    if (houses[0].nationality != static_cast<int8_t>(Nationality::Norwegian)) return false;
    // 11. Reading next to fox
    // 12. Painter next to horse
    // 15. Norwegian next to blue house
    // These are checked below
    
    // Check neighbor constraints
    for (int8_t i = 0; i < num_houses; ++i) {
        const auto& h = houses[i];
        // 11. Reading next to fox
        if (h.hobby == static_cast<int8_t>(Hobby::Reading)) {
            bool adjacent = false;
            if (i > 0 && houses[i - 1].pet == static_cast<int8_t>(Pet::Fox)) adjacent = true;
            if (i < num_houses - 1 && houses[i + 1].pet == static_cast<int8_t>(Pet::Fox)) adjacent = true;
            if (!adjacent) return false;
        }
        // 12. Painter next to horse
        if (h.hobby == static_cast<int8_t>(Hobby::Painting)) {
            bool adjacent = false;
            if (i > 0 && houses[i - 1].pet == static_cast<int8_t>(Pet::Horse)) adjacent = true;
            if (i < num_houses - 1 && houses[i + 1].pet == static_cast<int8_t>(Pet::Horse)) adjacent = true;
            if (!adjacent) return false;
        }
        // 15. Norwegian next to blue house
        if (h.nationality == static_cast<int8_t>(Nationality::Norwegian)) {
            bool adjacent = false;
            if (i > 0 && houses[i - 1].color == static_cast<int8_t>(Color::Blue)) adjacent = true;
            if (i < num_houses - 1 && houses[i + 1].color == static_cast<int8_t>(Color::Blue)) adjacent = true;
            if (!adjacent) return false;
        }
    }
    
    return true;
}

void solve_impl(int8_t index, array<House, num_houses>& houses, Solution& solution) {
    if (index == num_houses) {
        if (is_valid(houses)) {
            for (int8_t i = 0; i < num_houses; ++i) {
                if (houses[i].drink == static_cast<int8_t>(Drink::Water)) {
                    static const string nationalities[] = {
                        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                    };
                    solution.drinksWater = nationalities[houses[i].nationality];
                }
                if (houses[i].pet == static_cast<int8_t>(Pet::Zebra)) {
                    static const string nationalities[] = {
                        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                    };
                    solution.ownsZebra = nationalities[houses[i].nationality];
                }
            }
        }
        return;
    }
    
    // Generate all possible attributes for the current house
    // To optimize, we can fix known values first
    // Norwegian is in first house, milk is in middle house
    // Let's generate all possibilities and prune early
    // This needs to be implemented carefully to be efficient
    // For now, we'll use a simple approach
    
    // To be implemented with proper pruning
}

Solution solve() {
    Solution solution;
    array<House, num_houses> houses;
    
    // Fix known values to prune early
    // Norwegian in first house
    houses[0].nationality = static_cast<int8_t>(Nationality::Norwegian);
    // Milk in middle house
    houses[2].drink = static_cast<int8_t>(Drink::Milk);
    
    // Generate all possible assignments
    // This needs to be implemented with backtracking and pruning
    // For now, we'll use a simple approach
    
    // To find a valid assignment, we need to try all possibilities
    // Let's use a recursive approach that fills each house's attributes
    // and checks constraints as we go
    
    // This implementation is complex and needs to be done carefully
    // For the sake of time, we'll use a different approach
    
    // Since the number of possibilities is large, we need to be smart
    // Let's use a backtracking approach that assigns values to each house
    // and prunes invalid branches early
    
    // For now, we'll use a simple approach that tries all permutations
    // This may still be too slow, but with proper pruning it can work
    
    // Implement solve_impl to fill houses recursively
    // Start from index 0
    solve_impl(0, houses, solution);
    return solution;
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace zebra_puzzle {

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

#include <algorithm>
#include <array>
using namespace std;

namespace {

// Helper function to check if all constraints are satisfied
bool is_valid(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        // Constraint 2
        if (houses[i].nationality == Nationality::Englishman && houses[i].color != Color::Red)
            return false;
        // Constraint 3
        if (houses[i].nationality == Nationality::Spaniard && houses[i].pet != Pet::Dog)
            return false;
        // Constraint 4
        if (houses[i].color == Color::Green && houses[i].drink != Drink::Coffee)
            return false;
        // Constraint 5
        if (houses[i].nationality == Nationality::Ukrainian && houses[i].drink != Drink::Tea)
            return false;
        // Constraint 7
        if (houses[i].pet == Pet::Snails && houses[i].hobby != Hobby::Dancing)
            return false;
        // Constraint 8
        if (houses[i].color == Color::Yellow && houses[i].hobby != Hobby::Painting)
            return false;
        // Constraint 13
        if (houses[i].hobby == Hobby::Football && houses[i].drink != Drink::OrangeJuice)
            return false;
        // Constraint 14
        if (houses[i].nationality == Nationality::Japanese && houses[i].hobby != Hobby::Chess)
            return false;
    }
    
    // Constraint 6
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == Color::Ivory && houses[i + 1].color == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // Constraint 9 is always true due to our generation
    // Constraint 10 is always true due to our generation
    
    // Constraint 11
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            if (i > 0 && houses[i-1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Fox) found = true;
            if (!found) return false;
        }
    }
    
    // Constraint 12
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Painting) {
            if (i > 0 && houses[i-1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Horse) found = true;
            if (!found) return false;
        }
    }
    
    // Constraint 15
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == Nationality::Norwegian) {
            if (i > 0 && houses[i-1].color == Color::Blue) found = true;
            if (i < 4 && houses[i+1].color == Color::Blue) found = true;
            if (!found) return false;
        }
    }
    
    return true;
}

}  // namespace

Solution solve() {
    // Define all possible values in sorted order to use with next_permutation
    array<Color, 5> colors = {Color::Blue, Color::Green, Color::Ivory, Color::Red, Color::Yellow};
    array<Nationality, 5> nationalities = {Nationality::Englishman, Nationality::Japanese, 
                                           Nationality::Norwegian, Nationality::Spaniard, Nationality::Ukrainian};
    array<Drink, 5> drinks = {Drink::Coffee, Drink::Milk, Drink::OrangeJuice, Drink::Tea, Drink::Water};
    array<Pet, 5> pets = {Pet::Dog, Pet::Fox, Pet::Horse, Pet::Snails, Pet::Zebra};
    array<Hobby, 5> hobbies = {Hobby::Chess, Hobby::Dancing, Hobby::Football, Hobby::Painting, Hobby::Reading};
    
    array<House, 5> solution;
    bool found_solution = false;
    
    // Sort to start permutations
    sort(colors.begin(), colors.end());
    do {
        // Check constraint 6: Green is immediately to the right of ivory
        bool valid_color_order = false;
        for (int i = 0; i < 4; i++) {
            if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                valid_color_order = true;
                break;
            }
        }
        if (!valid_color_order) continue;
        
        sort(nationalities.begin(), nationalities.end());
        do {
            // Check constraint 10: Norwegian in first house
            if (nationalities[0] != Nationality::Norwegian) continue;
            // Check constraint 15: Norwegian next to blue house
            // Since Norwegian is in first house, blue must be in second
            bool norwegian_next_to_blue = false;
            for (int i = 0; i < 5; i++) {
                if (nationalities[i] == Nationality::Norwegian) {
                    if (i > 0 && colors[i - 1] == Color::Blue) norwegian_next_to_blue = true;
                    if (i < 4 && colors[i + 1] == Color::Blue) norwegian_next_to_blue = true;
                    break;
                }
            }
            if (!norwegian_next_to_blue) continue;
            
            sort(drinks.begin(), drinks.end());
            do {
                // Check constraint 9: Milk in middle house
                if (drinks[2] != Drink::Milk) continue;
                
                sort(pets.begin(), pets.end());
                do {
                    sort(hobbies.begin(), hobbies.end());
                    do {
                        // Build houses
                        array<House, 5> houses;
                        for (int i = 0; i < 5; i++) {
                            houses[i] = {colors[i], nationalities[i], drinks[i], pets[i], hobbies[i]};
                        }
                        if (is_valid(houses)) {
                            solution = houses;
                            found_solution = true;
                            goto found;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()) && !found_solution);
                } while (next_permutation(pets.begin(), pets.end()) && !found_solution);
            } while (next_permutation(drinks.begin(), drinks.end()) && !found_solution);
        } while (next_permutation(nationalities.begin(), nationalities.end()) && !found_solution);
    } while (next_permutation(colors.begin(), colors.end()) && !found_solution);
    
found:
    // Find the answers
    Solution result;
    for (const auto& house : solution) {
        if (house.drink == Drink::Water) {
            switch (house.nationality) {
                case Nationality::Englishman: result.drinksWater = "Englishman"; break;
                case Nationality::Spaniard: result.drinksWater = "Spaniard"; break;
                case Nationality::Ukrainian: result.drinksWater = "Ukrainian"; break;
                case Nationality::Norwegian: result.drinksWater = "Norwegian"; break;
                case Nationality::Japanese: result.drinksWater = "Japanese"; break;
            }
        }
        if (house.pet == Pet::Zebra) {
            switch (house.nationality) {
                case Nationality::Englishman: result.ownsZebra = "Englishman"; break;
                case Nationality::Spaniard: result.ownsZebra = "Spaniard"; break;
                case Nationality::Ukrainian: result.ownsZebra = "Ukrainian"; break;
                case Nationality::Norwegian: result.ownsZebra = "Norwegian"; break;
                case Nationality::Japanese: result.ownsZebra = "Japanese"; break;
            }
        }
    }
    return result;
}

}  // namespace zebra_puzzle

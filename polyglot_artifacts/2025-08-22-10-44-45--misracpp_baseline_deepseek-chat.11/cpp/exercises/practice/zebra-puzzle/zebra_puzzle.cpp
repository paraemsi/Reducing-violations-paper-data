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

bool satisfies_constraints(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        
        // 2. The Englishman lives in the red house.
        if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
        // 3. The Spaniard owns the dog.
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
        // 4. The person in the green house drinks coffee.
        if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
        // 5. The Ukrainian drinks tea.
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
        // 7. The snail owner likes to go dancing.
        if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
        // 8. The person in the yellow house is a painter.
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && h.drink != Drink::Milk) return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && h.nationality != Nationality::Norwegian) return false;
        // 13. The person who plays football drinks orange juice.
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
        // 14. The Japanese person plays chess.
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
    }
    
    // Check neighbor constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        // 6. The green house is immediately to the right of the ivory house.
        if (h.color == Color::Green && (i == 0 || houses[i-1].color != Color::Ivory)) return false;
        // 11. The person who enjoys reading lives in the house next to the person with the fox.
        if (h.hobby == Hobby::Reading) {
            bool found = false;
            if (i > 0 && houses[i-1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Fox) found = true;
            if (!found) return false;
        }
        // 12. The painter's house is next to the house with the horse.
        if (h.hobby == Hobby::Painting) {
            bool found = false;
            if (i > 0 && houses[i-1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Horse) found = true;
            if (!found) return false;
        }
        // 15. The Norwegian lives next to the blue house.
        if (h.nationality == Nationality::Norwegian) {
            bool found = false;
            if (i > 0 && houses[i-1].color == Color::Blue) found = true;
            if (i < 4 && houses[i+1].color == Color::Blue) found = true;
            if (!found) return false;
        }
    }
    return true;
}

// Helper function to convert enums to strings
string nationalityToString(Nationality n) {
    switch (n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
        default: throw runtime_error("Invalid nationality");
    }
}

string drinkToString(Drink d) {
    switch (d) {
        case Drink::Coffee: return "coffee";
        case Drink::Tea: return "tea";
        case Drink::Milk: return "milk";
        case Drink::OrangeJuice: return "orange juice";
        case Drink::Water: return "water";
        default: throw runtime_error("Invalid drink");
    }
}

string petToString(Pet p) {
    switch (p) {
        case Pet::Dog: return "dog";
        case Pet::Snails: return "snails";
        case Pet::Fox: return "fox";
        case Pet::Horse: return "horse";
        case Pet::Zebra: return "zebra";
        default: throw runtime_error("Invalid pet");
    }
}

bool is_valid(const array<House, 5>& houses, int up_to) {
    for (int i = 0; i <= up_to; i++) {
        const auto& h = houses[i];
        // Check all constraints that can be checked with the assigned houses
        // 2. The Englishman lives in the red house.
        if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
        // 3. The Spaniard owns the dog.
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
        // 4. The person in the green house drinks coffee.
        if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
        // 5. The Ukrainian drinks tea.
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
        // 7. The snail owner likes to go dancing.
        if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
        // 8. The person in the yellow house is a painter.
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && h.drink != Drink::Milk) return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && h.nationality != Nationality::Norwegian) return false;
        // 13. The person who plays football drinks orange juice.
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
        // 14. The Japanese person plays chess.
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
    }
    
    // Check neighbor constraints that can be checked
    for (int i = 0; i <= up_to; i++) {
        const auto& h = houses[i];
        // 6. The green house is immediately to the right of the ivory house.
        if (h.color == Color::Green) {
            if (i == 0) return false;
            if (houses[i-1].color != Color::Ivory) return false;
        }
        // 15. The Norwegian lives next to the blue house.
        if (h.nationality == Nationality::Norwegian) {
            bool valid = false;
            if (i > 0 && houses[i-1].color == Color::Blue) valid = true;
            if (i < up_to && houses[i+1].color == Color::Blue) valid = true;
            if (!valid && up_to == 4) return false;
        }
    }
    return true;
}

void solve_impl(array<House, 5>& houses, int index, 
                vector<Color>& colors, vector<Nationality>& nationalities,
                vector<Drink>& drinks, vector<Pet>& pets, vector<Hobby>& hobbies,
                bool& found, Solution& solution) {
    if (found) return;
    if (index == 5) {
        if (satisfies_constraints(houses)) {
            found = true;
            // Find who drinks water and owns zebra
            for (const auto& house : houses) {
                if (house.drink == Drink::Water) {
                    solution.drinksWater = nationalityToString(house.nationality);
                }
                if (house.pet == Pet::Zebra) {
                    solution.ownsZebra = nationalityToString(house.nationality);
                }
            }
        }
        return;
    }
    
    // Generate all possible assignments for the current index
    // To optimize, we can generate permutations outside and pass them in
    // For now, we'll use a simple approach
    // This is a placeholder - in reality, we need to track used values per category
    // Let's pregenerate all permutations and try them in order
}

Solution solve() {
    // Generate all possible values
    vector<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    vector<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                        Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    vector<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    vector<Pet> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    vector<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    array<House, 5> houses;
    Solution solution;
    
    // Sort to use next_permutation properly
    sort(colors.begin(), colors.end());
    sort(nationalities.begin(), nationalities.end());
    sort(drinks.begin(), drinks.end());
    sort(pets.begin(), pets.end());
    sort(hobbies.begin(), hobbies.end());
    
    do {
        // Check if Norwegian is in first house (constraint 10)
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        do {
            // Check if milk is in middle house (constraint 9)
            if (drinks[2] != Drink::Milk) continue;
            
            do {
                do {
                    do {
                        // Assign to houses
                        for (int i = 0; i < 5; i++) {
                            houses[i] = House{colors[i], nationalities[i], drinks[i], pets[i], hobbies[i]};
                        }
                        // Check if valid
                        if (satisfies_constraints(houses)) {
                            for (const auto& house : houses) {
                                if (house.drink == Drink::Water) {
                                    solution.drinksWater = nationalityToString(house.nationality);
                                }
                                if (house.pet == Pet::Zebra) {
                                    solution.ownsZebra = nationalityToString(house.nationality);
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(nationalities.begin(), nationalities.end()));
    } while (next_permutation(colors.begin(), colors.end()));
    
    return solution;
}

}  // namespace zebra_puzzle

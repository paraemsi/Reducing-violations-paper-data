#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
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
        // 2. The Englishman lives in the red house.
        if (houses[i].nationality == Nationality::Englishman && houses[i].color != Color::Red)
            return false;
        // 3. The Spaniard owns the dog.
        if (houses[i].nationality == Nationality::Spaniard && houses[i].pet != Pet::Dog)
            return false;
        // 4. Coffee is drunk in the green house.
        if (houses[i].color == Color::Green && houses[i].drink != Drink::Coffee)
            return false;
        // 5. The Ukrainian drinks tea.
        if (houses[i].nationality == Nationality::Ukrainian && houses[i].drink != Drink::Tea)
            return false;
        // 7. The snail owner is a dancer.
        if (houses[i].pet == Pet::Snails && houses[i].hobby != Hobby::Dancing)
            return false;
        // 8. The yellow house's owner is a painter.
        if (houses[i].color == Color::Yellow && houses[i].hobby != Hobby::Painting)
            return false;
        // 13. The footballer drinks orange juice.
        if (houses[i].hobby == Hobby::Football && houses[i].drink != Drink::OrangeJuice)
            return false;
        // 14. The Japanese is a chess player.
        if (houses[i].nationality == Nationality::Japanese && houses[i].hobby != Hobby::Chess)
            return false;
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == Color::Ivory && houses[i+1].color == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 9. Milk is drunk in the middle house.
    if (houses[2].drink != Drink::Milk) return false;
    
    // 10. The Norwegian lives in the first house.
    if (houses[0].nationality != Nationality::Norwegian) return false;
    
    // 11. The reader lives next to the fox owner.
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            if (i > 0 && houses[i-1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Fox) found = true;
        }
    }
    if (!found) return false;
    
    // 12. The painter lives next to the horse owner.
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Painting) {
            if (i > 0 && houses[i-1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Horse) found = true;
        }
    }
    if (!found) return false;
    
    // 15. The Norwegian lives next to the blue house.
    found = false;
    int norwegian_index = -1;
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == Nationality::Norwegian) {
            norwegian_index = i;
            break;
        }
    }
    if (norwegian_index > 0 && houses[norwegian_index-1].color == Color::Blue) found = true;
    if (norwegian_index < 4 && houses[norwegian_index+1].color == Color::Blue) found = true;
    if (!found) return false;
    
    return true;
}

bool is_valid_so_far(const array<House, 5>& houses, int index) {
    // Check constraints that can be validated with the houses filled up to index
    for (int i = 0; i <= index; i++) {
        // 2. The Englishman lives in the red house.
        if (houses[i].nationality == Nationality::Englishman && houses[i].color != Color::Red)
            return false;
        // 3. The Spaniard owns the dog.
        if (houses[i].nationality == Nationality::Spaniard && houses[i].pet != Pet::Dog)
            return false;
        // 4. Coffee is drunk in the green house.
        if (houses[i].color == Color::Green && houses[i].drink != Drink::Coffee)
            return false;
        // 5. The Ukrainian drinks tea.
        if (houses[i].nationality == Nationality::Ukrainian && houses[i].drink != Drink::Tea)
            return false;
        // 7. The snail owner is a dancer.
        if (houses[i].pet == Pet::Snails && houses[i].hobby != Hobby::Dancing)
            return false;
        // 8. The yellow house's owner is a painter.
        if (houses[i].color == Color::Yellow && houses[i].hobby != Hobby::Painting)
            return false;
        // 13. The footballer drinks orange juice.
        if (houses[i].hobby == Hobby::Football && houses[i].drink != Drink::OrangeJuice)
            return false;
        // 14. The Japanese is a chess player.
        if (houses[i].nationality == Nationality::Japanese && houses[i].hobby != Hobby::Chess)
            return false;
    }
    
    // Check constraints that involve multiple houses
    // 9. Milk is drunk in the middle house.
    if (index >= 2 && houses[2].drink != Drink::Milk) return false;
    
    // 10. The Norwegian lives in the first house.
    if (index >= 0 && houses[0].nationality != Nationality::Norwegian) return false;
    
    // 15. The Norwegian lives next to the blue house.
    if (index >= 1) {
        if (houses[0].nationality == Nationality::Norwegian) {
            if (houses[1].color != Color::Blue) return false;
        }
    }
    
    // Check for uniqueness in assigned houses
    for (int i = 0; i <= index; i++) {
        for (int j = i + 1; j <= index; j++) {
            if (houses[i].color == houses[j].color) return false;
            if (houses[i].nationality == houses[j].nationality) return false;
            if (houses[i].drink == houses[j].drink) return false;
            if (houses[i].pet == houses[j].pet) return false;
            if (houses[i].hobby == houses[j].hobby) return false;
        }
    }
    
    return true;
}

void solve_impl(array<House, 5>& houses, int index, bool& found, array<House, 5>& solution) {
    if (found) return;
    if (index == 5) {
        if (satisfies_constraints(houses)) {
            solution = houses;
            found = true;
        }
        return;
    }
    
    // Generate all possible values for each attribute
    vector<Color> all_colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    vector<Nationality> all_nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                            Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    vector<Drink> all_drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    vector<Pet> all_pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    vector<Hobby> all_hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    // Try all possible assignments for the current index
    for (const auto& color : all_colors) {
        houses[index].color = color;
        for (const auto& nationality : all_nationalities) {
            houses[index].nationality = nationality;
            for (const auto& drink : all_drinks) {
                houses[index].drink = drink;
                for (const auto& pet : all_pets) {
                    houses[index].pet = pet;
                    for (const auto& hobby : all_hobbies) {
                        houses[index].hobby = hobby;
                        if (is_valid_so_far(houses, index)) {
                            solve_impl(houses, index + 1, found, solution);
                            if (found) return;
                        }
                    }
                }
            }
        }
    }
}

Solution solve() {
    array<House, 5> houses;
    bool found = false;
    array<House, 5> solution;
    
    solve_impl(houses, 0, found, solution);
    
    // Find who drinks water and owns the zebra
    string water_drinker, zebra_owner;
    for (int i = 0; i < 5; i++) {
        if (solution[i].drink == Drink::Water) {
            switch (solution[i].nationality) {
                case Nationality::Englishman: water_drinker = "Englishman"; break;
                case Nationality::Spaniard: water_drinker = "Spaniard"; break;
                case Nationality::Ukrainian: water_drinker = "Ukrainian"; break;
                case Nationality::Norwegian: water_drinker = "Norwegian"; break;
                case Nationality::Japanese: water_drinker = "Japanese"; break;
            }
        }
        if (solution[i].pet == Pet::Zebra) {
            switch (solution[i].nationality) {
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

}  // namespace zebra_puzzle

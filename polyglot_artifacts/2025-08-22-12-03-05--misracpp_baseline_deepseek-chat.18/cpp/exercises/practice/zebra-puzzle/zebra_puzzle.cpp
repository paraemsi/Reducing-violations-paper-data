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

struct House {
    int color;
    int nationality;
    int drink;
    int pet;
    int hobby;
};

const vector<string> color_names = {"red", "green", "ivory", "yellow", "blue"};
const vector<string> nationality_names = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const vector<string> drink_names = {"coffee", "tea", "milk", "orange juice", "water"};
const vector<string> pet_names = {"dog", "snails", "fox", "horse", "zebra"};
const vector<string> hobby_names = {"reading", "dancing", "painting", "football", "chess"};

array<House, 5> solution;

bool check_constraints(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        // 2. The Englishman lives in the red house.
        if (h.nationality == 0 && h.color != 0) return false;
        // 3. The Spaniard owns the dog.
        if (h.nationality == 1 && h.pet != 0) return false;
        // 4. The person in the green house drinks coffee.
        if (h.color == 1 && h.drink != 0) return false;
        // 5. The Ukrainian drinks tea.
        if (h.nationality == 2 && h.drink != 1) return false;
        // 8. The person in the yellow house is a painter.
        if (h.color == 4 && h.hobby != 2) return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && h.drink != 2) return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && h.nationality != 3) return false;
        // 13. The person who plays football drinks orange juice.
        if (h.hobby == 3 && h.drink != 3) return false;
        // 14. The Japanese person plays chess.
        if (h.nationality == 4 && h.hobby != 4) return false;
        // 7. The snail owner likes to go dancing.
        if (h.pet == 1 && h.hobby != 1) return false;
    }
    
    // Check adjacent constraints
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == 2 && houses[i + 1].color == 1) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 15. The Norwegian lives next to the blue house.
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == 3) {
            if (i > 0 && houses[i - 1].color == 4) found = true;
            if (i < 4 && houses[i + 1].color == 4) found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    // 12. The painter's house is next to the house with the horse.
    // These need to be checked by finding indices
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == 0) { // reading
            found = false;
            if (i > 0 && houses[i - 1].pet == 2) found = true;
            if (i < 4 && houses[i + 1].pet == 2) found = true;
            if (!found) return false;
        }
        if (houses[i].hobby == 2) { // painting
            found = false;
            if (i > 0 && houses[i - 1].pet == 3) found = true;
            if (i < 4 && houses[i + 1].pet == 3) found = true;
            if (!found) return false;
        }
    }
    
    return true;
}

void solve_impl(array<House, 5>& houses, int house_index, 
                vector<bool>& used_color, vector<bool>& used_nationality,
                vector<bool>& used_drink, vector<bool>& used_pet,
                vector<bool>& used_hobby, bool& found) {
    if (found) return;
    if (house_index == 5) {
        if (check_constraints(houses)) {
            solution = houses;
            found = true;
        }
        return;
    }
    
    // Try all possible assignments for the current house
    for (int c = 0; c < 5; c++) {
        if (used_color[c]) continue;
        used_color[c] = true;
        houses[house_index].color = c;
        
        for (int n = 0; n < 5; n++) {
            if (used_nationality[n]) continue;
            used_nationality[n] = true;
            houses[house_index].nationality = n;
            
            for (int d = 0; d < 5; d++) {
                if (used_drink[d]) continue;
                used_drink[d] = true;
                houses[house_index].drink = d;
                
                for (int p = 0; p < 5; p++) {
                    if (used_pet[p]) continue;
                    used_pet[p] = true;
                    houses[house_index].pet = p;
                    
                    for (int h = 0; h < 5; h++) {
                        if (used_hobby[h]) continue;
                        used_hobby[h] = true;
                        houses[house_index].hobby = h;
                        
                        solve_impl(houses, house_index + 1, used_color, used_nationality, used_drink, used_pet, used_hobby, found);
                        if (found) return;
                        
                        used_hobby[h] = false;
                    }
                    used_pet[p] = false;
                }
                used_drink[d] = false;
            }
            used_nationality[n] = false;
        }
        used_color[c] = false;
    }
}

Solution solve() {
    array<House, 5> houses;
    vector<bool> used_color(5, false), used_nationality(5, false), used_drink(5, false), used_pet(5, false), used_hobby(5, false);
    bool found = false;
    solve_impl(houses, 0, used_color, used_nationality, used_drink, used_pet, used_hobby, found);
    
    // Find water drinker and zebra owner
    string water_drinker, zebra_owner;
    for (const auto& house : solution) {
        if (house.drink == 4) {
            water_drinker = nationality_names[house.nationality];
        }
        if (house.pet == 4) {
            zebra_owner = nationality_names[house.nationality];
        }
    }
    return Solution{water_drinker, zebra_owner};
}

}  // namespace zebra_puzzle

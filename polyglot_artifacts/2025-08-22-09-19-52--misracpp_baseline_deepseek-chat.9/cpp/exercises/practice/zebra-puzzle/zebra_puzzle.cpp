#include "zebra_puzzle.h"
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <array>
using namespace std;

namespace zebra_puzzle {

struct House {
    int color;
    int nationality;
    int pet;
    int drink;
    int hobby;
};

// Define indices for easier access
constexpr int RED = 0, GREEN = 1, IVORY = 2, YELLOW = 3, BLUE = 4;
constexpr int ENGLISHMAN = 0, SPANIARD = 1, UKRAINIAN = 2, NORWEGIAN = 3, JAPANESE = 4;
constexpr int DOG = 0, SNAILS = 1, FOX = 2, HORSE = 3, ZEBRA = 4;
constexpr int COFFEE = 0, TEA = 1, MILK = 2, ORANGE_JUICE = 3, WATER = 4;
constexpr int DANCING = 0, PAINTING = 1, READING = 2, FOOTBALL = 3, CHESS = 4;

vector<string> color_names{"red", "green", "ivory", "yellow", "blue"};
vector<string> nationality_names{"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
vector<string> pet_names{"dog", "snails", "fox", "horse", "zebra"};
vector<string> drink_names{"coffee", "tea", "milk", "orange juice", "water"};
vector<string> hobby_names{"dancing", "painting", "reading", "football", "chess"};

vector<House> solution;

bool check_constraints(const vector<House>& houses) {
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        // Check fixed constraints
        if (h.nationality == ENGLISHMAN && h.color != RED) return false;
        if (h.nationality == SPANIARD && h.pet != DOG) return false;
        if (h.color == GREEN && h.drink != COFFEE) return false;
        if (h.nationality == UKRAINIAN && h.drink != TEA) return false;
        if (h.pet == SNAILS && h.hobby != DANCING) return false;
        if (h.color == YELLOW && h.hobby != PAINTING) return false;
        if (i == 2 && h.drink != MILK) return false;
        if (i == 0 && h.nationality != NORWEGIAN) return false;
        if (h.hobby == FOOTBALL && h.drink != ORANGE_JUICE) return false;
        if (h.nationality == JAPANESE && h.hobby != CHESS) return false;
    }
    
    // Check adjacency constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        // Green is immediately to the right of ivory
        if (h.color == IVORY) {
            if (i == 4 || houses[i + 1].color != GREEN) return false;
        }
        if (h.color == GREEN) {
            if (i == 0 || houses[i - 1].color != IVORY) return false;
        }
        
        // Reading next to fox
        if (h.hobby == READING) {
            if ((i > 0 && houses[i - 1].pet == FOX) || (i < 4 && houses[i + 1].pet == FOX)) {}
            else return false;
        }
        // Painter next to horse
        if (h.hobby == PAINTING) {
            if ((i > 0 && houses[i - 1].pet == HORSE) || (i < 4 && houses[i + 1].pet == HORSE)) {}
            else return false;
        }
        // Norwegian next to blue
        if (h.nationality == NORWEGIAN) {
            if ((i > 0 && houses[i - 1].color == BLUE) || (i < 4 && houses[i + 1].color == BLUE)) {}
            else return false;
        }
    }
    return true;
}

void backtrack(vector<House>& houses, int index, 
               vector<bool>& used_color, vector<bool>& used_nationality,
               vector<bool>& used_pet, vector<bool>& used_drink, 
               vector<bool>& used_hobby) {
    // If we found a solution, return early
    if (!solution.empty()) return;
    
    if (index == 5) {
        if (check_constraints(houses)) {
            solution = houses;
        }
        return;
    }
    
    // For each index, assign all possible values to each attribute
    // But check partial constraints after each assignment to prune early
    for (int c = 0; c < 5; c++) {
        if (used_color[c]) continue;
        houses[index].color = c;
        used_color[c] = true;
        
        // Check if the current partial assignment is valid
        if (!check_constraints(houses)) {
            used_color[c] = false;
            continue;
        }
        
        for (int n = 0; n < 5; n++) {
            if (used_nationality[n]) continue;
            houses[index].nationality = n;
            used_nationality[n] = true;
            
            if (!check_constraints(houses)) {
                used_nationality[n] = false;
                continue;
            }
            
            for (int p = 0; p < 5; p++) {
                if (used_pet[p]) continue;
                houses[index].pet = p;
                used_pet[p] = true;
                
                if (!check_constraints(houses)) {
                    used_pet[p] = false;
                    continue;
                }
                
                for (int d = 0; d < 5; d++) {
                    if (used_drink[d]) continue;
                    houses[index].drink = d;
                    used_drink[d] = true;
                    
                    if (!check_constraints(houses)) {
                        used_drink[d] = false;
                        continue;
                    }
                    
                    for (int h = 0; h < 5; h++) {
                        if (used_hobby[h]) continue;
                        houses[index].hobby = h;
                        used_hobby[h] = true;
                        
                        if (check_constraints(houses)) {
                            backtrack(houses, index + 1, used_color, used_nationality, used_pet, used_drink, used_hobby);
                        }
                        
                        used_hobby[h] = false;
                        if (!solution.empty()) return;
                    }
                    used_drink[d] = false;
                    if (!solution.empty()) return;
                }
                used_pet[p] = false;
                if (!solution.empty()) return;
            }
            used_nationality[n] = false;
            if (!solution.empty()) return;
        }
        used_color[c] = false;
        if (!solution.empty()) return;
    }
}

Solution solve() {
    vector<House> houses(5);
    vector<bool> used_color(5, false);
    vector<bool> used_nationality(5, false);
    vector<bool> used_pet(5, false);
    vector<bool> used_drink(5, false);
    vector<bool> used_hobby(5, false);
    
    // Fix known values upfront to reduce search space
    // Norwegian is in first house
    houses[0].nationality = NORWEGIAN;
    used_nationality[NORWEGIAN] = true;
    
    // Middle house drinks milk
    houses[2].drink = MILK;
    used_drink[MILK] = true;
    
    // Start from index 0
    backtrack(houses, 0, used_color, used_nationality, used_pet, used_drink, used_hobby);
    
    // Find who drinks water and owns zebra
    Solution s;
    for (const auto& house : solution) {
        if (house.drink == WATER) {
            s.drinksWater = nationality_names[house.nationality];
        }
        if (house.pet == ZEBRA) {
            s.ownsZebra = nationality_names[house.nationality];
        }
    }
    return s;
}

}  // namespace zebra_puzzle

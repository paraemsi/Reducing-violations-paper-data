#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <optional>

using namespace std;

namespace zebra_puzzle {

struct House {
    int color;
    int nationality;
    int pet;
    int drink;
    int hobby;
};

bool is_valid(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        
        // 2. Englishman in red house
        if (h.nationality == 0 && h.color != 0) return false;
        // 3. Spaniard owns dog
        if (h.nationality == 1 && h.pet != 0) return false;
        // 4. Coffee in green house
        if (h.drink == 0 && h.color != 1) return false;
        // 5. Ukrainian drinks tea
        if (h.nationality == 2 && h.drink != 3) return false;
        // 7. Snail owner dances
        if (h.pet == 1 && h.hobby != 1) return false;
        // 8. Yellow house painter
        if (h.color == 4 && h.hobby != 2) return false;
        // 9. Middle house drinks milk
        if (i == 2 && h.drink != 2) return false;
        // 10. Norwegian in first house
        if (i == 0 && h.nationality != 3) return false;
        // 13. Football player drinks orange juice
        if (h.hobby == 3 && h.drink != 1) return false;
        // 14. Japanese plays chess
        if (h.nationality == 4 && h.hobby != 4) return false;
    }
    
    // Check adjacency constraints
    // 6. Green right of ivory
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == 2 && houses[i + 1].color == 1) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 11. Reader next to fox owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == 0) {
            if ((i > 0 && houses[i - 1].pet == 2) || (i < 4 && houses[i + 1].pet == 2)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 12. Painter next to horse owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == 2) {
            if ((i > 0 && houses[i - 1].pet == 3) || (i < 4 && houses[i + 1].pet == 3)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 15. Norwegian next to blue house
    found = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == 3) {
            if ((i > 0 && houses[i - 1].color == 3) || (i < 4 && houses[i + 1].color == 3)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    return true;
}

bool is_partial_valid(const array<House, 5>& houses, int up_to) {
    for (int i = 0; i <= up_to; i++) {
        const auto& h = houses[i];
        
        // Check constraints that can be validated with current information
        // 2. Englishman in red house
        if (h.nationality != -1 && h.color != -1) {
            if ((h.nationality == 0) != (h.color == 0)) return false;
        }
        // 3. Spaniard owns dog
        if (h.nationality != -1 && h.pet != -1) {
            if ((h.nationality == 1) != (h.pet == 0)) return false;
        }
        // 4. Coffee in green house
        if (h.drink != -1 && h.color != -1) {
            if ((h.drink == 0) != (h.color == 1)) return false;
        }
        // 5. Ukrainian drinks tea
        if (h.nationality != -1 && h.drink != -1) {
            if ((h.nationality == 2) != (h.drink == 3)) return false;
        }
        // 7. Snail owner dances
        if (h.pet != -1 && h.hobby != -1) {
            if ((h.pet == 1) != (h.hobby == 1)) return false;
        }
        // 8. Yellow house painter
        if (h.color != -1 && h.hobby != -1) {
            if ((h.color == 4) != (h.hobby == 2)) return false;
        }
        // 9. Middle house drinks milk
        if (i == 2 && h.drink != -1 && h.drink != 2) return false;
        // 10. Norwegian in first house
        if (i == 0 && h.nationality != -1 && h.nationality != 3) return false;
        // 13. Football player drinks orange juice
        if (h.hobby != -1 && h.drink != -1) {
            if ((h.hobby == 3) != (h.drink == 1)) return false;
        }
        // 14. Japanese plays chess
        if (h.nationality != -1 && h.hobby != -1) {
            if ((h.nationality == 4) != (h.hobby == 4)) return false;
        }
    }
    
    // Check adjacency constraints that can be partially validated
    // 6. Green right of ivory
    // Check if any house up to up_to-1 has ivory and the next isn't green
    for (int i = 0; i < up_to; i++) {
        if (houses[i].color == 2) {
            if (i + 1 > up_to || houses[i + 1].color != 1) return false;
        }
    }
    // 15. Norwegian next to blue house
    for (int i = 0; i <= up_to; i++) {
        if (houses[i].nationality == 3) {
            bool valid = false;
            if (i > 0 && houses[i - 1].color == 3) valid = true;
            if (i < up_to && houses[i + 1].color == 3) valid = true;
            if (i > 0 && houses[i - 1].color == -1) valid = true; // Not yet assigned
            if (i < 4 && houses[i + 1].color == -1) valid = true; // Not yet assigned
            if (!valid) return false;
        }
    }
    
    return true;
}

void solve_impl(array<House, 5>& houses, int house_idx, 
                array<bool, 5>& used_color, array<bool, 5>& used_nationality,
                array<bool, 5>& used_pet, array<bool, 5>& used_drink,
                array<bool, 5>& used_hobby, Solution& solution) {
    if (house_idx == 5) {
        // Find who drinks water and owns zebra
        for (int i = 0; i < 5; i++) {
            if (houses[i].drink == 4) {
                const array<string, 5> nationalities{"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                solution.drinksWater = nationalities[houses[i].nationality];
            }
            if (houses[i].pet == 4) {
                const array<string, 5> nationalities{"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
                solution.ownsZebra = nationalities[houses[i].nationality];
            }
        }
        return;
    }
    
    // For each attribute, try all possibilities, checking validity after each assignment
    // Let's assign in a fixed order: color, nationality, pet, drink, hobby
    for (int c = 0; c < 5; c++) {
        if (used_color[c]) continue;
        used_color[c] = true;
        houses[house_idx].color = c;
        if (!is_partial_valid(houses, house_idx)) {
            used_color[c] = false;
            continue;
        }
        
        for (int n = 0; n < 5; n++) {
            if (used_nationality[n]) continue;
            used_nationality[n] = true;
            houses[house_idx].nationality = n;
            if (!is_partial_valid(houses, house_idx)) {
                used_nationality[n] = false;
                continue;
            }
            
            for (int p = 0; p < 5; p++) {
                if (used_pet[p]) continue;
                used_pet[p] = true;
                houses[house_idx].pet = p;
                if (!is_partial_valid(houses, house_idx)) {
                    used_pet[p] = false;
                    continue;
                }
                
                for (int d = 0; d < 5; d++) {
                    if (used_drink[d]) continue;
                    used_drink[d] = true;
                    houses[house_idx].drink = d;
                    if (!is_partial_valid(houses, house_idx)) {
                        used_drink[d] = false;
                        continue;
                    }
                    
                    for (int h = 0; h < 5; h++) {
                        if (used_hobby[h]) continue;
                        used_hobby[h] = true;
                        houses[house_idx].hobby = h;
                        if (is_partial_valid(houses, house_idx)) {
                            solve_impl(houses, house_idx + 1, used_color, used_nationality, 
                                      used_pet, used_drink, used_hobby, solution);
                        }
                        used_hobby[h] = false;
                    }
                    used_drink[d] = false;
                }
                used_pet[p] = false;
            }
            used_nationality[n] = false;
        }
        used_color[c] = false;
    }
}

Solution solve() {
    array<House, 5> houses;
    // Initialize with -1 to indicate unassigned
    for (auto& house : houses) {
        house.color = house.nationality = house.pet = house.drink = house.hobby = -1;
    }
    array<bool, 5> used_color{};
    array<bool, 5> used_nationality{};
    array<bool, 5> used_pet{};
    array<bool, 5> used_drink{};
    array<bool, 5> used_hobby{};
    
    Solution solution;
    solve_impl(houses, 0, used_color, used_nationality, used_pet, used_drink, used_hobby, solution);
    return solution;
}

}  // namespace zebra_puzzle

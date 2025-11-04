#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

namespace zebra_puzzle {

namespace {

enum class Attribute { Color, Nationality, Pet, Drink, Hobby };

const array<array<string, 5>, 5> attributes{{
    {"red", "green", "ivory", "yellow", "blue"},
    {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"},
    {"dog", "snails", "fox", "horse", "zebra"},
    {"coffee", "tea", "milk", "orange juice", "water"},
    {"dancing", "painting", "reading", "football", "chess"}
}};

array<array<int, 5>, 5> solution;
bool found = false;

bool is_valid() {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        // 2. The Englishman lives in the red house.
        if (solution[static_cast<int>(Attribute::Nationality)][i] == 0 && 
            solution[static_cast<int>(Attribute::Color)][i] != 0) return false;
        // 3. The Spaniard owns the dog.
        if (solution[static_cast<int>(Attribute::Nationality)][i] == 1 && 
            solution[static_cast<int>(Attribute::Pet)][i] != 0) return false;
        // 4. Coffee is drunk in the green house.
        if (solution[static_cast<int>(Attribute::Color)][i] == 1 && 
            solution[static_cast<int>(Attribute::Drink)][i] != 0) return false;
        // 5. The Ukrainian drinks tea.
        if (solution[static_cast<int>(Attribute::Nationality)][i] == 2 && 
            solution[static_cast<int>(Attribute::Drink)][i] != 1) return false;
        // 7. The snail owner is a dancer.
        if (solution[static_cast<int>(Attribute::Pet)][i] == 1 && 
            solution[static_cast<int>(Attribute::Hobby)][i] != 0) return false;
        // 8. The yellow house resident is a painter.
        if (solution[static_cast<int>(Attribute::Color)][i] == 3 && 
            solution[static_cast<int>(Attribute::Hobby)][i] != 1) return false;
        // 13. The football player drinks orange juice.
        if (solution[static_cast<int>(Attribute::Hobby)][i] == 3 && 
            solution[static_cast<int>(Attribute::Drink)][i] != 3) return false;
        // 14. The Japanese plays chess.
        if (solution[static_cast<int>(Attribute::Nationality)][i] == 4 && 
            solution[static_cast<int>(Attribute::Hobby)][i] != 4) return false;
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    for (int i = 0; i < 4; i++) {
        if (solution[static_cast<int>(Attribute::Color)][i] == 2 && 
            solution[static_cast<int>(Attribute::Color)][i + 1] == 1) break;
        if (i == 3) return false;
    }
    
    // 9. Milk is drunk in the middle house.
    if (solution[static_cast<int>(Attribute::Drink)][2] != 2) return false;
    
    // 10. The Norwegian lives in the first house.
    if (solution[static_cast<int>(Attribute::Nationality)][0] != 3) return false;
    
    // 11. The reader lives next to the fox owner.
    for (int i = 0; i < 5; i++) {
        if (solution[static_cast<int>(Attribute::Hobby)][i] == 2) {
            bool adjacent = false;
            if (i > 0 && solution[static_cast<int>(Attribute::Pet)][i - 1] == 2) adjacent = true;
            if (i < 4 && solution[static_cast<int>(Attribute::Pet)][i + 1] == 2) adjacent = true;
            if (!adjacent) return false;
        }
    }
    
    // 12. The painter lives next to the horse owner.
    for (int i = 0; i < 5; i++) {
        if (solution[static_cast<int>(Attribute::Hobby)][i] == 1) {
            bool adjacent = false;
            if (i > 0 && solution[static_cast<int>(Attribute::Pet)][i - 1] == 3) adjacent = true;
            if (i < 4 && solution[static_cast<int>(Attribute::Pet)][i + 1] == 3) adjacent = true;
            if (!adjacent) return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    int norwegian_pos = -1;
    for (int i = 0; i < 5; i++) {
        if (solution[static_cast<int>(Attribute::Nationality)][i] == 3) {
            norwegian_pos = i;
            break;
        }
    }
    bool adjacent = false;
    if (norwegian_pos > 0 && solution[static_cast<int>(Attribute::Color)][norwegian_pos - 1] == 4) adjacent = true;
    if (norwegian_pos < 4 && solution[static_cast<int>(Attribute::Color)][norwegian_pos + 1] == 4) adjacent = true;
    if (!adjacent) return false;
    
    return true;
}

void backtrack(int attribute, vector<vector<bool>>& used, Solution& result) {
    if (found) return;
    if (attribute == 5) {
        if (is_valid()) {
            found = true;
            for (int i = 0; i < 5; i++) {
                if (solution[static_cast<int>(Attribute::Drink)][i] == 4) {
                    result.drinksWater = attributes[static_cast<int>(Attribute::Nationality)][solution[static_cast<int>(Attribute::Nationality)][i]];
                }
                if (solution[static_cast<int>(Attribute::Pet)][i] == 4) {
                    result.ownsZebra = attributes[static_cast<int>(Attribute::Nationality)][solution[static_cast<int>(Attribute::Nationality)][i]];
                }
            }
        }
        return;
    }
    
    // Generate all permutations for the current attribute
    do {
        if (is_valid()) {
            backtrack(attribute + 1, used, result);
        }
    } while (next_permutation(solution[attribute].begin(), solution[attribute].end()));
}

}  // namespace

Solution solve() {
    Solution result;
    found = false;
    
    // Initialize solution with identity permutations
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            solution[i][j] = j;
        }
    }
    
    vector<vector<bool>> used(5, vector<bool>(5, false));
    backtrack(0, used, result);
    return result;
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <array>
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

namespace zebra_puzzle {

bool is_valid(const array<array<int, 5>, 5>& assignments) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        // Englishman in red house
        if (assignments[1][i] == 0 && assignments[0][i] != 0) return false;
        // Spaniard owns dog
        if (assignments[1][i] == 1 && assignments[2][i] != 0) return false;
        // Coffee in green house
        if (assignments[0][i] == 1 && assignments[3][i] != 0) return false;
        // Ukrainian drinks tea
        if (assignments[1][i] == 2 && assignments[3][i] != 1) return false;
        // Snail owner likes dancing
        if (assignments[2][i] == 1 && assignments[4][i] != 1) return false;
        // Yellow house is painter
        if (assignments[0][i] == 3 && assignments[4][i] != 0) return false;
        // Football drinks orange juice
        if (assignments[4][i] == 3 && assignments[3][i] != 3) return false;
        // Japanese plays chess
        if (assignments[1][i] == 4 && assignments[4][i] != 4) return false;
    }
    
    // Check position-based constraints
    // Norwegian in first house
    if (assignments[1][0] != 3) return false;
    // Milk in middle house
    if (assignments[3][2] != 2) return false;
    
    // Green is immediately to the right of ivory
    for (int i = 0; i < 4; i++) {
        if (assignments[0][i] == 2 && assignments[0][i + 1] == 1) break;
        if (i == 3) return false;
    }
    
    // Norwegian next to blue
    bool found = false;
    for (int i = 0; i < 5; i++) {
        if (assignments[0][i] == 4) {
            if ((i > 0 && assignments[1][i - 1] == 3) || 
                (i < 4 && assignments[1][i + 1] == 3)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // Reading next to fox
    found = false;
    for (int i = 0; i < 5; i++) {
        if (assignments[4][i] == 2) {
            if ((i > 0 && assignments[2][i - 1] == 2) || 
                (i < 4 && assignments[2][i + 1] == 2)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // Painter next to horse
    found = false;
    for (int i = 0; i < 5; i++) {
        if (assignments[4][i] == 0) {
            if ((i > 0 && assignments[2][i - 1] == 4) || 
                (i < 4 && assignments[2][i + 1] == 4)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    return true;
}

void generate_permutations(int category, array<array<int, 5>, 5>& assignments, 
                          array<vector<bool>, 5>& used, Solution& solution) {
    if (category == 5) {
        if (is_valid(assignments)) {
            for (int i = 0; i < 5; i++) {
                if (assignments[3][i] == 4) {
                    solution.drinksWater = nationalities[assignments[1][i]];
                }
                if (assignments[2][i] == 4) {
                    solution.ownsZebra = nationalities[assignments[1][i]];
                }
            }
        }
        return;
    }
    
    // Generate all permutations for the current category
    for (int i = 0; i < 5; i++) {
        if (!used[category][i]) {
            used[category][i] = true;
            for (int j = 0; j < 5; j++) {
                assignments[category][j] = i;
            }
            generate_permutations(category + 1, assignments, used, solution);
            used[category][i] = false;
        }
    }
}

// Define all possible values
const vector<string> colors = {"red", "green", "ivory", "yellow", "blue"};
const vector<string> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const vector<string> pets = {"dog", "snail", "fox", "horse", "zebra"};
const vector<string> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
const vector<string> hobbies = {"painter", "dancing", "reading", "football", "chess"};

Solution solve() {
    array<array<int, 5>, 5> assignments;
    array<vector<bool>, 5> used;
    for (int i = 0; i < 5; i++) {
        used[i] = vector<bool>(5, false);
    }
    Solution solution;
    generate_permutations(0, assignments, used, solution);
    return solution;
}

}  // namespace zebra_puzzle

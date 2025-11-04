#include "zebra_puzzle.h"
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <array>
using namespace std;

namespace zebra_puzzle {

// Define all possible values
const vector<string> colors = {"red", "green", "ivory", "yellow", "blue"};
const vector<string> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const vector<string> pets = {"dog", "snails", "fox", "horse", "zebra"};
const vector<string> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
const vector<string> hobbies = {"dancing", "reading", "painting", "football", "chess"};

struct Assignment {
    array<int, 5> color;
    array<int, 5> nationality;
    array<int, 5> pet;
    array<int, 5> drink;
    array<int, 5> hobby;
};

bool is_valid(const Assignment& a) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        // 2. Englishman in red house
        if (a.nationality[i] == 0 && a.color[i] != 0) return false;
        // 3. Spaniard owns dog
        if (a.nationality[i] == 1 && a.pet[i] != 0) return false;
        // 4. Green house drinks coffee
        if (a.color[i] == 1 && a.drink[i] != 0) return false;
        // 5. Ukrainian drinks tea
        if (a.nationality[i] == 2 && a.drink[i] != 1) return false;
        // 7. Snail owner likes dancing
        if (a.pet[i] == 1 && a.hobby[i] != 0) return false;
        // 8. Yellow house is painter
        if (a.color[i] == 3 && a.hobby[i] != 2) return false;
        // 13. Football player drinks orange juice
        if (a.hobby[i] == 3 && a.drink[i] != 3) return false;
        // 14. Japanese plays chess
        if (a.nationality[i] == 4 && a.hobby[i] != 4) return false;
    }
    
    // 6. Green is immediately right of ivory
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (a.color[i] == 2 && a.color[i + 1] == 1) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 9. Middle house drinks milk
    if (a.drink[2] != 2) return false;
    
    // 10. Norwegian in first house
    if (a.nationality[0] != 3) return false;
    
    // 11. Reader next to fox owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (a.hobby[i] == 1) {
            if ((i > 0 && a.pet[i - 1] == 2) || (i < 4 && a.pet[i + 1] == 2)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 12. Painter next to horse owner
    found = false;
    for (int i = 0; i < 5; i++) {
        if (a.hobby[i] == 2) {
            if ((i > 0 && a.pet[i - 1] == 3) || (i < 4 && a.pet[i + 1] == 3)) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;
    
    // 15. Norwegian next to blue house
    found = false;
    int norwegian_pos = -1;
    for (int i = 0; i < 5; i++) {
        if (a.nationality[i] == 3) {
            norwegian_pos = i;
            break;
        }
    }
    if ((norwegian_pos > 0 && a.color[norwegian_pos - 1] == 4) || 
        (norwegian_pos < 4 && a.color[norwegian_pos + 1] == 4)) {
        found = true;
    }
    if (!found) return false;
    
    return true;
}

void generate_permutations(int category, Assignment& a, vector<Solution>& solutions) {
    if (category == 5) {
        if (is_valid(a)) {
            // Find who drinks water and owns zebra
            for (int i = 0; i < 5; i++) {
                if (a.drink[i] == 4) {
                    for (int j = 0; j < 5; j++) {
                        if (a.pet[j] == 4) {
                            solutions.push_back({
                                nationalities[a.nationality[i]],
                                nationalities[a.nationality[j]]
                            });
                            return;
                        }
                    }
                }
            }
        }
        return;
    }
    
    // Generate all permutations for the current category
    vector<int> indices = {0, 1, 2, 3, 4};
    do {
        switch (category) {
            case 0: a.color = {indices[0], indices[1], indices[2], indices[3], indices[4]}; break;
            case 1: a.nationality = {indices[0], indices[1], indices[2], indices[3], indices[4]}; break;
            case 2: a.pet = {indices[0], indices[1], indices[2], indices[3], indices[4]}; break;
            case 3: a.drink = {indices[0], indices[1], indices[2], indices[3], indices[4]}; break;
            case 4: a.hobby = {indices[0], indices[1], indices[2], indices[3], indices[4]}; break;
        }
        generate_permutations(category + 1, a, solutions);
    } while (next_permutation(indices.begin(), indices.end()));
}

Solution solve() {
    vector<Solution> solutions;
    Assignment a;
    generate_permutations(0, a, solutions);
    return solutions[0];
}

}  // namespace zebra_puzzle

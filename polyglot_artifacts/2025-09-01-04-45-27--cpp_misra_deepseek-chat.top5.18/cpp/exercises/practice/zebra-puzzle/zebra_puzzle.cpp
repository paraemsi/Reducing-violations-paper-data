#include "zebra_puzzle.h"
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

namespace {

const vector<string> colors = {"red", "green", "ivory", "yellow", "blue"};
const vector<string> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const vector<string> pets = {"dog", "snails", "fox", "horse", "zebra"};
const vector<string> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
const vector<string> hobbies = {"dancing", "reading", "painting", "football", "chess"};

bool check_constraints(const vector<int32_t>& color, const vector<int32_t>& nationality,
                       const vector<int32_t>& pet, const vector<int32_t>& drink,
                       const vector<int32_t>& hobby) {
    // Check all constraints
    for (int32_t i = 0; i < 5; ++i) {
        // 2. Englishman in red house
        if (nationality[i] == 0 && color[i] != 0) return false;
        // 3. Spaniard owns dog
        if (nationality[i] == 1 && pet[i] != 0) return false;
        // 4. Coffee in green house
        if (drink[i] == 0 && color[i] != 1) return false;
        // 5. Ukrainian drinks tea
        if (nationality[i] == 2 && drink[i] != 1) return false;
        // 7. Snails owner likes dancing
        if (pet[i] == 1 && hobby[i] != 0) return false;
        // 8. Yellow house is painter
        if (color[i] == 3 && hobby[i] != 2) return false;
        // 13. Football player drinks orange juice
        if (hobby[i] == 3 && drink[i] != 3) return false;
        // 14. Japanese plays chess
        if (nationality[i] == 4 && hobby[i] != 4) return false;
    }
    
    // 6. Green is immediately to the right of ivory
    bool green_right_of_ivory = false;
    for (int32_t i = 0; i < 4; ++i) {
        if (color[i] == 2 && color[i + 1] == 1) {
            green_right_of_ivory = true;
            break;
        }
    }
    if (!green_right_of_ivory) return false;
    
    // 9. Middle house drinks milk
    if (drink[2] != 2) return false;
    
    // 10. Norwegian in first house
    if (nationality[0] != 3) return false;
    
    // 11. Reader next to fox owner
    bool reader_next_to_fox = false;
    for (int32_t i = 0; i < 5; ++i) {
        if (hobby[i] == 1) {
            if ((i > 0 && pet[i - 1] == 2) || (i < 4 && pet[i + 1] == 2)) {
                reader_next_to_fox = true;
                break;
            }
        }
    }
    if (!reader_next_to_fox) return false;
    
    // 12. Painter next to horse owner
    bool painter_next_to_horse = false;
    for (int32_t i = 0; i < 5; ++i) {
        if (hobby[i] == 2) {
            if ((i > 0 && pet[i - 1] == 3) || (i < 4 && pet[i + 1] == 3)) {
                painter_next_to_horse = true;
                break;
            }
        }
    }
    if (!painter_next_to_horse) return false;
    
    // 15. Norwegian next to blue house
    bool norwegian_next_to_blue = false;
    if (0 > 0 && color[0 - 1] == 4) norwegian_next_to_blue = true;
    if (0 < 4 && color[0 + 1] == 4) norwegian_next_to_blue = true;
    if (!norwegian_next_to_blue) return false;
    
    return true;
}

}  // namespace

Solution solve() {
    // Generate permutations while fixing constraints
    vector<int32_t> color = {0, 1, 2, 3, 4};
    do {
        vector<int32_t> nationality = {0, 1, 2, 3, 4};
        do {
            // Norwegian is in first house (index 3)
            if (nationality[0] != 3) continue;
            // Norwegian next to blue house
            bool norwegian_next_to_blue = false;
            if (color[1] == 4) norwegian_next_to_blue = true;
            if (!norwegian_next_to_blue) continue;
            
            vector<int32_t> drink = {0, 1, 2, 3, 4};
            do {
                // Middle house drinks milk (index 2)
                if (drink[2] != 2) continue;
                
                vector<int32_t> pet = {0, 1, 2, 3, 4};
                do {
                    vector<int32_t> hobby = {0, 1, 2, 3, 4};
                    do {
                        if (check_constraints(color, nationality, pet, drink, hobby)) {
                            Solution solution;
                            // Find water drinker
                            for (int32_t i = 0; i < 5; ++i) {
                                if (drink[i] == 4) {
                                    solution.drinksWater = nationalities[nationality[i]];
                                    break;
                                }
                            }
                            // Find zebra owner
                            for (int32_t i = 0; i < 5; ++i) {
                                if (pet[i] == 4) {
                                    solution.ownsZebra = nationalities[nationality[i]];
                                    break;
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobby.begin(), hobby.end()));
                } while (next_permutation(pet.begin(), pet.end()));
            } while (next_permutation(drink.begin(), drink.end()));
        } while (next_permutation(nationality.begin(), nationality.end()));
    } while (next_permutation(color.begin(), color.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <string>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

Solution solve() {
    const array<string, 5> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
    const array<string, 5> colors = {"red", "green", "ivory", "yellow", "blue"};
    const array<string, 5> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
    const array<string, 5> pets = {"dog", "snail", "fox", "horse", "zebra"};
    const array<string, 5> hobbies = {"dancing", "painting", "reading", "football", "chess"};

    // Generate all possible permutations for each category
    vector<vector<int32_t>> all_permutations;
    vector<int32_t> indices = {0, 1, 2, 3, 4};
    do {
        all_permutations.push_back(indices);
    } while (next_permutation(indices.begin(), indices.end()));

    // Check each combination
    for (const auto& nat : all_permutations) {
        // Norwegian lives in the first house (index 0)
        if (nat[0] != 3) continue;
        
        for (const auto& col : all_permutations) {
            // Green is immediately to the right of ivory
            bool valid_green_ivory = false;
            for (int32_t i = 0; i < 4; i++) {
                if ((col[i] == 2) && (col[i + 1] == 1)) {
                    valid_green_ivory = true;
                    break;
                }
            }
            if (!valid_green_ivory) continue;
            
            // Norwegian lives next to the blue house
            int32_t norwegian_house = 0;
            int32_t blue_house = -1;
            for (int32_t i = 0; i < 5; i++) {
                if (col[i] == 4) blue_house = i;
            }
            if ((blue_house != (norwegian_house - 1)) && (blue_house != (norwegian_house + 1))) continue;
            
            // Englishman lives in the red house
            bool englishman_in_red = true;
            for (int32_t i = 0; i < 5; i++) {
                if (nat[i] == 0 && col[i] != 0) {
                    englishman_in_red = false;
                    break;
                }
            }
            if (!englishman_in_red) continue;
            
            for (const auto& drk : all_permutations) {
                // Middle house drinks milk
                if (drk[2] != 2) continue;
                
                // Ukrainian drinks tea
                bool ukrainian_drinks_tea = true;
                for (int32_t i = 0; i < 5; i++) {
                    if (nat[i] == 2 && drk[i] != 1) {
                        ukrainian_drinks_tea = false;
                        break;
                    }
                }
                if (!ukrainian_drinks_tea) continue;
                
                // Coffee is drunk in the green house
                bool coffee_in_green = true;
                for (int32_t i = 0; i < 5; i++) {
                    if (col[i] == 1 && drk[i] != 0) {
                        coffee_in_green = false;
                        break;
                    }
                }
                if (!coffee_in_green) continue;
                
                for (const auto& pet : all_permutations) {
                    // Spaniard owns the dog
                    bool spaniard_owns_dog = true;
                    for (int32_t i = 0; i < 5; i++) {
                        if (nat[i] == 1 && pet[i] != 0) {
                            spaniard_owns_dog = false;
                            break;
                        }
                    }
                    if (!spaniard_owns_dog) continue;
                    
                    for (const auto& hob : all_permutations) {
                        // Check all remaining constraints
                        // 7. Snail owner likes dancing
                        bool snail_dancing = true;
                        for (int32_t i = 0; i < 5; i++) {
                            if (pet[i] == 1 && hob[i] != 0) {
                                snail_dancing = false;
                                break;
                            }
                        }
                        if (!snail_dancing) continue;
                        
                        // 8. Yellow house is painter
                        bool yellow_painter = true;
                        for (int32_t i = 0; i < 5; i++) {
                            if (col[i] == 3 && hob[i] != 1) {
                                yellow_painter = false;
                                break;
                            }
                        }
                        if (!yellow_painter) continue;
                        
                        // 13. Football drinks orange juice
                        bool football_orange_juice = true;
                        for (int32_t i = 0; i < 5; i++) {
                            if (hob[i] == 3 && drk[i] != 3) {
                                football_orange_juice = false;
                                break;
                            }
                        }
                        if (!football_orange_juice) continue;
                        
                        // 14. Japanese plays chess
                        bool japanese_chess = true;
                        for (int32_t i = 0; i < 5; i++) {
                            if (nat[i] == 4 && hob[i] != 4) {
                                japanese_chess = false;
                                break;
                            }
                        }
                        if (!japanese_chess) continue;
                        
                        // 11. Reader next to fox
                        bool reader_next_to_fox = false;
                        for (int32_t i = 0; i < 5; i++) {
                            if (hob[i] == 2) {
                                if ((i > 0 && pet[i - 1] == 2) || (i < 4 && pet[i + 1] == 2)) {
                                    reader_next_to_fox = true;
                                    break;
                                }
                            }
                        }
                        if (!reader_next_to_fox) continue;
                        
                        // 12. Painter next to horse
                        bool painter_next_to_horse = false;
                        for (int32_t i = 0; i < 5; i++) {
                            if (hob[i] == 1) {
                                if ((i > 0 && pet[i - 1] == 3) || (i < 4 && pet[i + 1] == 3)) {
                                    painter_next_to_horse = true;
                                    break;
                                }
                            }
                        }
                        if (!painter_next_to_horse) continue;
                        
                        // All constraints satisfied, find the answers
                        Solution solution;
                        for (int32_t i = 0; i < 5; i++) {
                            if (drk[i] == 4) { // water is at index 4
                                solution.drinksWater = nationalities[nat[i]];
                            }
                            if (pet[i] == 4) { // zebra is at index 4
                                solution.ownsZebra = nationalities[nat[i]];
                            }
                        }
                        return solution;
                    }
                }
            }
        }
    }
    
    // For now, return a dummy solution
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

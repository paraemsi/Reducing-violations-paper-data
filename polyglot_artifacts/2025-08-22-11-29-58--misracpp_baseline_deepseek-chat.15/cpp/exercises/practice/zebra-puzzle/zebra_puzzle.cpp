#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <functional>
#include <string>
#include <vector>
using namespace std;

namespace zebra_puzzle {

// Helper function to check if a value is to the right of another
bool is_right_of(int a, int b) {
    return a == b + 1;
}

// Helper function to check if two values are adjacent
bool is_adjacent(int a, int b) {
    return abs(a - b) == 1;
}

Solution solve() {
    // Define all possible values
    const vector<string> colors = {"red", "green", "ivory", "yellow", "blue"};
    const vector<string> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
    const vector<string> pets = {"dog", "snails", "fox", "horse", "zebra"};
    const vector<string> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
    const vector<string> hobbies = {"dancing", "painting", "reading", "football", "chess"};
    
    // Generate all permutations for each category
    vector<vector<int>> color_perms;
    vector<int> color_temp = {0, 1, 2, 3, 4};
    do {
        color_perms.push_back(color_temp);
    } while (next_permutation(color_temp.begin(), color_temp.end()));
    
    // We'll generate other permutations on the fly to save memory
    
    // Try all combinations
    for (const auto& color : color_perms) {
        // Check constraint 6: green is immediately right of ivory
        int green_idx = find(colors.begin(), colors.end(), "green") - colors.begin();
        int ivory_idx = find(colors.begin(), colors.end(), "ivory") - colors.begin();
        if (!is_right_of(color[green_idx], color[ivory_idx])) continue;
        
        for (const auto& nationality : color_perms) {
            // Check constraint 2: Englishman in red house
            int englishman_idx = find(nationalities.begin(), nationalities.end(), "Englishman") - nationalities.begin();
            int red_idx = find(colors.begin(), colors.end(), "red") - colors.begin();
            if (nationality[englishman_idx] != color[red_idx]) continue;
            
            // Check constraint 10: Norwegian in first house
            int norwegian_idx = find(nationalities.begin(), nationalities.end(), "Norwegian") - nationalities.begin();
            if (nationality[norwegian_idx] != 0) continue;
            
            // Check constraint 15: Norwegian next to blue house
            int blue_idx = find(colors.begin(), colors.end(), "blue") - colors.begin();
            if (!is_adjacent(nationality[norwegian_idx], color[blue_idx])) continue;
            
            for (const auto& drink : color_perms) {
                // Check constraint 4: coffee in green house
                int coffee_idx = find(drinks.begin(), drinks.end(), "coffee") - drinks.begin();
                if (drink[coffee_idx] != color[green_idx]) continue;
                
                // Check constraint 5: Ukrainian drinks tea
                int ukrainian_idx = find(nationalities.begin(), nationalities.end(), "Ukrainian") - nationalities.begin();
                int tea_idx = find(drinks.begin(), drinks.end(), "tea") - drinks.begin();
                if (drink[tea_idx] != nationality[ukrainian_idx]) continue;
                
                // Check constraint 9: milk in middle house
                int milk_idx = find(drinks.begin(), drinks.end(), "milk") - drinks.begin();
                if (drink[milk_idx] != 2) continue;
                
                for (const auto& pet : color_perms) {
                    // Check constraint 3: Spaniard owns dog
                    int spaniard_idx = find(nationalities.begin(), nationalities.end(), "Spaniard") - nationalities.begin();
                    int dog_idx = find(pets.begin(), pets.end(), "dog") - pets.begin();
                    if (pet[dog_idx] != nationality[spaniard_idx]) continue;
                    
                    for (const auto& hobby : color_perms) {
                        // Check remaining constraints
                        // Constraint 7: snail owner likes dancing
                        int snails_idx = find(pets.begin(), pets.end(), "snails") - pets.begin();
                        int dancing_idx = find(hobbies.begin(), hobbies.end(), "dancing") - hobbies.begin();
                        if (hobby[dancing_idx] != pet[snails_idx]) continue;
                        
                        // Constraint 8: yellow house is painter
                        int yellow_idx = find(colors.begin(), colors.end(), "yellow") - colors.begin();
                        int painting_idx = find(hobbies.begin(), hobbies.end(), "painting") - hobbies.begin();
                        if (hobby[painting_idx] != color[yellow_idx]) continue;
                        
                        // Constraint 11: reading next to fox
                        int reading_idx = find(hobbies.begin(), hobbies.end(), "reading") - hobbies.begin();
                        int fox_idx = find(pets.begin(), pets.end(), "fox") - pets.begin();
                        if (!is_adjacent(hobby[reading_idx], pet[fox_idx])) continue;
                        
                        // Constraint 12: painter next to horse
                        int horse_idx = find(pets.begin(), pets.end(), "horse") - pets.begin();
                        if (!is_adjacent(hobby[painting_idx], pet[horse_idx])) continue;
                        
                        // Constraint 13: football drinks orange juice
                        int football_idx = find(hobbies.begin(), hobbies.end(), "football") - hobbies.begin();
                        int orange_juice_idx = find(drinks.begin(), drinks.end(), "orange juice") - drinks.begin();
                        if (hobby[football_idx] != drink[orange_juice_idx]) continue;
                        
                        // Constraint 14: Japanese plays chess
                        int japanese_idx = find(nationalities.begin(), nationalities.end(), "Japanese") - nationalities.begin();
                        int chess_idx = find(hobbies.begin(), hobbies.end(), "chess") - hobbies.begin();
                        if (hobby[chess_idx] != nationality[japanese_idx]) continue;
                        
                        // Found valid assignment
                        int water_idx = find(drinks.begin(), drinks.end(), "water") - drinks.begin();
                        int zebra_idx = find(pets.begin(), pets.end(), "zebra") - pets.begin();
                        
                        return Solution{
                            nationalities[nationality[drink[water_idx]]],
                            nationalities[nationality[pet[zebra_idx]]]
                        };
                    }
                }
            }
        }
    }
    
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

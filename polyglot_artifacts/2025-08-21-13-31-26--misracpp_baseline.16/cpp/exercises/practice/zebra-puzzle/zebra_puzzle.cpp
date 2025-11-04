#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

using std::array;
using std::string;
using std::vector;

// Helper function to check if two houses are neighbors
bool are_neighbors(int a, int b) {
    return std::abs(a - b) == 1;
}

Solution solve() {
    // All possible values for each attribute
    const array<string, 5> colors   = {"red", "green", "ivory", "yellow", "blue"};
    const array<string, 5> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
    const array<string, 5> pets     = {"dog", "snails", "fox", "horse", "zebra"};
    const array<string, 5> drinks   = {"coffee", "tea", "milk", "orange juice", "water"};
    const array<string, 5> hobbies  = {"dancing", "painter", "reading", "football", "chess"};

    array<int, 5> idx = {0, 1, 2, 3, 4};

    // Try all permutations for each attribute, but use constraints to prune search
    // To make it tractable, we permute in a nested way, applying constraints as early as possible

    // 1. The Norwegian lives in the first house (index 0)
    array<int, 5> color_idx = idx;
    do {
        // 2. The green house is immediately to the right of the ivory house
        int green_pos = std::find(color_idx.begin(), color_idx.end(), 1) - color_idx.begin();
        int ivory_pos = std::find(color_idx.begin(), color_idx.end(), 2) - color_idx.begin();
        if (green_pos != ivory_pos + 1) continue;

        // 3. The Norwegian lives next to the blue house
        int blue_pos = std::find(color_idx.begin(), color_idx.end(), 4) - color_idx.begin();

        array<int, 5> nat_idx = idx;
        do {
            if (nat_idx[0] != 3) continue; // Norwegian
            if (!are_neighbors(blue_pos, 0)) continue; // Norwegian lives next to blue house

            // 4. The Englishman lives in the red house
            if (std::find(nat_idx.begin(), nat_idx.end(), 0) - nat_idx.begin() != std::find(color_idx.begin(), color_idx.end(), 0) - color_idx.begin()) continue; // Englishman/red

            // 5. The Japanese person plays chess
            // (defer to hobby loop)

            // 6. The Spaniard owns the dog
            // (defer to pet loop)

            // 7. The Ukrainian drinks tea
            // (defer to drink loop)

            // 8. The person in the middle house drinks milk (index 2)
            array<int, 5> drink_idx = idx;
            do {
                if (drink_idx[2] != 2) continue; // milk

                // 9. The person in the green house drinks coffee
                if (green_pos != std::find(drink_idx.begin(), drink_idx.end(), 0) - drink_idx.begin()) continue; // coffee

                // 10. The Ukrainian drinks tea
                if (std::find(nat_idx.begin(), nat_idx.end(), 2) - nat_idx.begin() != std::find(drink_idx.begin(), drink_idx.end(), 1) - drink_idx.begin()) continue; // Ukrainian/tea

                // 11. The person who plays football drinks orange juice
                // (defer to hobby loop)

                array<int, 5> hobby_idx = idx;
                do {
                    // 12. The person in the yellow house is a painter
                    if (std::find(color_idx.begin(), color_idx.end(), 3) - color_idx.begin() != std::find(hobby_idx.begin(), hobby_idx.end(), 1) - hobby_idx.begin()) continue; // yellow/painter

                    // 13. The Japanese person plays chess
                    if (std::find(nat_idx.begin(), nat_idx.end(), 4) - nat_idx.begin() != std::find(hobby_idx.begin(), hobby_idx.end(), 4) - hobby_idx.begin()) continue; // Japanese/chess

                    // 14. The person who plays football drinks orange juice
                    if (std::find(hobby_idx.begin(), hobby_idx.end(), 3) - hobby_idx.begin() != std::find(drink_idx.begin(), drink_idx.end(), 3) - drink_idx.begin()) continue; // football/orange juice

                    array<int, 5> pet_idx = idx;
                    do {
                        // 15. The Spaniard owns the dog
                        if (std::find(nat_idx.begin(), nat_idx.end(), 1) - nat_idx.begin() != std::find(pet_idx.begin(), pet_idx.end(), 0) - pet_idx.begin()) continue; // Spaniard/dog

                        // 16. The snail owner likes to go dancing
                        if (std::find(pet_idx.begin(), pet_idx.end(), 1) - pet_idx.begin() != std::find(hobby_idx.begin(), hobby_idx.end(), 0) - hobby_idx.begin()) continue; // snails/dancing

                        // 17. The person who enjoys reading lives in the house next to the person with the fox
                        int reading_pos = std::find(hobby_idx.begin(), hobby_idx.end(), 2) - hobby_idx.begin();
                        int fox_pos = std::find(pet_idx.begin(), pet_idx.end(), 2) - pet_idx.begin();
                        if (!are_neighbors(reading_pos, fox_pos)) continue;

                        // 18. The painter's house is next to the house with the horse
                        int painter_pos = std::find(hobby_idx.begin(), hobby_idx.end(), 1) - hobby_idx.begin();
                        int horse_pos = std::find(pet_idx.begin(), pet_idx.end(), 3) - pet_idx.begin();
                        if (!are_neighbors(painter_pos, horse_pos)) continue;

                        // 19. The person in the house next to the horse drinks water
                        int water_pos = std::find(drink_idx.begin(), drink_idx.end(), 4) - drink_idx.begin();
                        if (!are_neighbors(horse_pos, water_pos)) continue;

                        // All constraints satisfied, return the solution
                        Solution sol;
                        sol.drinksWater = nationalities[ nat_idx[water_pos] ];
                        int zebra_pos = std::find(pet_idx.begin(), pet_idx.end(), 4) - pet_idx.begin();
                        sol.ownsZebra = nationalities[ nat_idx[zebra_pos] ];
                        return sol;

                    } while (std::next_permutation(pet_idx.begin(), pet_idx.end()));
                } while (std::next_permutation(hobby_idx.begin(), hobby_idx.end()));
            } while (std::next_permutation(drink_idx.begin(), drink_idx.end()));
        } while (std::next_permutation(nat_idx.begin(), nat_idx.end()));
    } while (std::next_permutation(color_idx.begin(), color_idx.end()));

    // If no solution found (should not happen)
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

using std::string;
using std::array;
using std::vector;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using house_t = std::uint8_t;

// All possible values for each attribute
constexpr array<const char*, 5U> COLORS = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<const char*, 5U> NATIONALITIES = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<const char*, 5U> PETS = { "dog", "snails", "fox", "horse", "zebra" };
constexpr array<const char*, 5U> DRINKS = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<const char*, 5U> HOBBIES = { "dancing", "painter", "reading", "football", "chess" };

// Helper function to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

Solution solve()
{
    // All permutations of 5 elements
    array<index_t, 5U> idx = { 0U, 1U, 2U, 3U, 4U };
    array<index_t, 5U> colors;
    array<index_t, 5U> nationalities;
    array<index_t, 5U> pets;
    array<index_t, 5U> drinks;
    array<index_t, 5U> hobbies;

    // For performance, fix some clues early:
    // - Norwegian lives in the first house (index 0)
    // - Milk is drunk in the middle house (index 2)
    // - Green is immediately right of ivory (so green cannot be first)
    // - Norwegian lives next to blue house

    // Generate all color permutations with green right of ivory
    vector<array<index_t, 5U>> color_perms;
    do {
        for(index_t i = 0U; i < 4U; ++i) {
            if((idx[i] == 2U) && (idx[i + 1U] == 1U)) { // ivory=2, green=1
                color_perms.push_back(idx);
            }
        }
    } while(std::next_permutation(idx.begin(), idx.end()));

    // Generate all nationality permutations with Norwegian in first house
    idx = { 0U, 1U, 2U, 3U, 4U };
    vector<array<index_t, 5U>> nat_perms;
    do {
        if(idx[0U] == 3U) { // Norwegian=3
            nat_perms.push_back(idx);
        }
    } while(std::next_permutation(idx.begin(), idx.end()));

    // Generate all drink permutations with milk in the middle house
    idx = { 0U, 1U, 2U, 3U, 4U };
    vector<array<index_t, 5U>> drink_perms;
    do {
        if(idx[2U] == 2U) { // milk=2
            drink_perms.push_back(idx);
        }
    } while(std::next_permutation(idx.begin(), idx.end()));

    // Now brute-force all combinations
    for(const auto& colors : color_perms) {
        for(const auto& nationalities : nat_perms) {
            // 15. Norwegian lives next to blue house
            index_t norwegian_house = 0U;
            index_t blue_house = 0U;
            for(index_t i = 0U; i < 5U; ++i) {
                if(nationalities[i] == 3U) { norwegian_house = i; }
                if(colors[i] == 4U) { blue_house = i; }
            }
            if(!is_neighbor(norwegian_house, blue_house)) {
                continue;
            }

            // 2. Englishman lives in red house
            for(index_t i = 0U; i < 5U; ++i) {
                if((nationalities[i] == 0U) && (colors[i] != 0U)) {
                    goto next_nat;
                }
            }

            for(const auto& drinks : drink_perms) {
                // 4. Green house drinks coffee
                for(index_t i = 0U; i < 5U; ++i) {
                    if((colors[i] == 1U) && (drinks[i] != 0U)) {
                        goto next_drink;
                    }
                }
                // 5. Ukrainian drinks tea
                for(index_t i = 0U; i < 5U; ++i) {
                    if((nationalities[i] == 2U) && (drinks[i] != 1U)) {
                        goto next_drink;
                    }
                }
                // 9. Middle house drinks milk (already enforced)
                // 6. Green is immediately right of ivory (already enforced in color_perms)
                // 13. Football drinks orange juice
                // 3. Spaniard owns dog (pets not assigned yet)
                // 7. Snail owner likes dancing (pets/hobbies not assigned yet)
                // 8. Yellow house is painter (hobbies not assigned yet)
                // 10. Norwegian in first house (already enforced)
                // 11. Reading next to fox (pets/hobbies not assigned yet)
                // 12. Painter next to horse (pets/hobbies not assigned yet)
                // 14. Japanese plays chess (hobbies not assigned yet)

                // Try all pet permutations
                idx = { 0U, 1U, 2U, 3U, 4U };
                do {
                    // 3. Spaniard owns dog
                    for(index_t i = 0U; i < 5U; ++i) {
                        if((nationalities[i] == 1U) && (idx[i] != 0U)) {
                            goto next_pet;
                        }
                    }
                    // 11. Reading next to fox (hobbies not assigned yet)
                    // 12. Painter next to horse (hobbies not assigned yet)
                    // 7. Snail owner likes dancing (hobbies not assigned yet)
                    // 8. Yellow house is painter (hobbies not assigned yet)

                    // Try all hobby permutations
                    array<index_t, 5U> hobbies_idx = { 0U, 1U, 2U, 3U, 4U };
                    do {
                        // 7. Snail owner likes dancing
                        for(index_t i = 0U; i < 5U; ++i) {
                            if((idx[i] == 1U) && (hobbies_idx[i] != 0U)) {
                                goto next_hobby;
                            }
                        }
                        // 8. Yellow house is painter
                        for(index_t i = 0U; i < 5U; ++i) {
                            if((colors[i] == 3U) && (hobbies_idx[i] != 1U)) {
                                goto next_hobby;
                            }
                        }
                        // 13. Football drinks orange juice
                        for(index_t i = 0U; i < 5U; ++i) {
                            if((hobbies_idx[i] == 3U) && (drinks[i] != 3U)) {
                                goto next_hobby;
                            }
                        }
                        // 14. Japanese plays chess
                        for(index_t i = 0U; i < 5U; ++i) {
                            if((nationalities[i] == 4U) && (hobbies_idx[i] != 4U)) {
                                goto next_hobby;
                            }
                        }
                        // 11. Reading next to fox
                        for(index_t i = 0U; i < 5U; ++i) {
                            if((hobbies_idx[i] == 2U)) {
                                bool found = false;
                                if((i > 0U) && (idx[i - 1U] == 2U)) { found = true; }
                                if((i < 4U) && (idx[i + 1U] == 2U)) { found = true; }
                                if(!found) { goto next_hobby; }
                            }
                        }
                        // 12. Painter next to horse
                        for(index_t i = 0U; i < 5U; ++i) {
                            if((hobbies_idx[i] == 1U)) {
                                bool found = false;
                                if((i > 0U) && (idx[i - 1U] == 3U)) { found = true; }
                                if((i < 4U) && (idx[i + 1U] == 3U)) { found = true; }
                                if(!found) { goto next_hobby; }
                            }
                        }

                        // All constraints satisfied, build solution
                        Solution sol;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(drinks[i] == 4U) { sol.drinksWater = NATIONALITIES[nationalities[i]]; }
                            if(idx[i] == 4U) { sol.ownsZebra = NATIONALITIES[nationalities[i]]; }
                        }
                        return sol;

                    next_hobby:;
                    } while(std::next_permutation(hobbies_idx.begin(), hobbies_idx.end()));

                next_pet:;
                } while(std::next_permutation(idx.begin(), idx.end()));

            next_drink:;
            }
        next_nat:;
        }
    }

    // If no solution found, return empty
    return Solution{};
}

}  // namespace zebra_puzzle

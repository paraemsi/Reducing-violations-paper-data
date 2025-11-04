#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using House = std::array<std::string, 5U>;
using Arrangement = std::array<index_t, 5U>;

// All possible values for each attribute
static const std::array<std::string, 5U> colors = { "red", "green", "ivory", "yellow", "blue" };
static const std::array<std::string, 5U> nationalities = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
static const std::array<std::string, 5U> pets = { "dog", "snails", "fox", "horse", "zebra" };
static const std::array<std::string, 5U> drinks = { "coffee", "tea", "milk", "orange juice", "water" };
static const std::array<std::string, 5U> hobbies = { "dancing", "painter", "reading", "football", "chess" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

Solution solve()
{
    // All permutations of 5 elements
    std::array<index_t, 5U> base = { 0U, 1U, 2U, 3U, 4U };
    std::array<index_t, 5U> color, nation, pet, drink, hobby;

    // For performance, only permute as needed and prune early
    // 1. The Norwegian lives in the first house (index 0)
    // 2. The milk is drunk in the middle house (index 2)
    // 3. The green house is immediately to the right of the ivory house

    // Generate all permutations for each attribute, applying constraints as early as possible
    std::vector<Arrangement> nation_perms;
    do {
        if (base[3U] == 0U) { // Norwegian in first house
            nation_perms.push_back(base);
        }
    } while (std::next_permutation(base.begin(), base.end()));

    base = { 0U, 1U, 2U, 3U, 4U };
    std::vector<Arrangement> drink_perms;
    do {
        if (base[2U] == 2U) { // Milk in middle house
            drink_perms.push_back(base);
        }
    } while (std::next_permutation(base.begin(), base.end()));

    base = { 0U, 1U, 2U, 3U, 4U };
    std::vector<Arrangement> color_perms;
    do {
        // Green is immediately right of ivory
        for (index_t i = 0U; i < 4U; ++i) {
            if ((base[i] == 2U) && (base[i + 1U] == 1U)) { // ivory=2, green=1
                color_perms.push_back(base);
                break;
            }
        }
    } while (std::next_permutation(base.begin(), base.end()));

    base = { 0U, 1U, 2U, 3U, 4U };
    std::vector<Arrangement> pet_perms;
    do {
        pet_perms.push_back(base);
    } while (std::next_permutation(base.begin(), base.end()));

    base = { 0U, 1U, 2U, 3U, 4U };
    std::vector<Arrangement> hobby_perms;
    do {
        hobby_perms.push_back(base);
    } while (std::next_permutation(base.begin(), base.end()));

    // Now brute-force search with pruning
    for (const Arrangement& nation : nation_perms) {
        for (const Arrangement& color : color_perms) {
            // 2. The Englishman lives in the red house.
            if (nation[0U] != color[0U]) { continue; }
            // 15. The Norwegian lives next to the blue house.
            if (!is_neighbor(nation[3U], color[4U])) { continue; }

            for (const Arrangement& drink : drink_perms) {
                // 4. The person in the green house drinks coffee.
                if (color[1U] != drink[0U]) { continue; }
                // 5. The Ukrainian drinks tea.
                if (nation[2U] != drink[1U]) { continue; }

                for (const Arrangement& pet : pet_perms) {
                    // 3. The Spaniard owns the dog.
                    if (nation[1U] != pet[0U]) { continue; }

                    for (const Arrangement& hobby : hobby_perms) {
                        // 7. The snail owner likes to go dancing.
                        if (pet[1U] != hobby[0U]) { continue; }
                        // 8. The person in the yellow house is a painter.
                        if (color[3U] != hobby[1U]) { continue; }
                        // 13. The person who plays football drinks orange juice.
                        if (hobby[3U] != drink[3U]) { continue; }
                        // 14. The Japanese person plays chess.
                        if (nation[4U] != hobby[4U]) { continue; }

                        // 6. The green house is immediately to the right of the ivory house.
                        index_t green_idx = 0U, ivory_idx = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (color[i] == 1U) { green_idx = i; }
                            if (color[i] == 2U) { ivory_idx = i; }
                        }
                        if (green_idx != (ivory_idx + 1U)) { continue; }

                        // 9. The person in the middle house drinks milk.
                        if (drink[2U] != 2U) { continue; }

                        // 10. The Norwegian lives in the first house.
                        if (nation[3U] != 0U) { continue; }

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        if (!is_neighbor(hobby[2U], pet[2U])) { continue; }

                        // 12. The painter's house is next to the house with the horse.
                        if (!is_neighbor(hobby[1U], pet[3U])) { continue; }

                        // All constraints satisfied, extract solution
                        std::string water_drinker, zebra_owner;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (drink[i] == 4U) { water_drinker = nationalities[nation[i]]; }
                            if (pet[i] == 4U) { zebra_owner = nationalities[nation[i]]; }
                        }
                        Solution sol;
                        sol.drinksWater = water_drinker;
                        sol.ownsZebra = zebra_owner;
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

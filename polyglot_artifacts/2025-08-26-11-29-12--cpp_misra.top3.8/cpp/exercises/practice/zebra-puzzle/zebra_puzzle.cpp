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
    return (a > b) ? ((a - b) == static_cast<index_t>(1)) : ((b - a) == static_cast<index_t>(1));
}

Solution solve()
{
    Arrangement color_perm = {0U, 1U, 2U, 3U, 4U};
    Arrangement nat_perm = {0U, 1U, 2U, 3U, 4U};
    Arrangement pet_perm = {0U, 1U, 2U, 3U, 4U};
    Arrangement drink_perm = {0U, 1U, 2U, 3U, 4U};
    Arrangement hobby_perm = {0U, 1U, 2U, 3U, 4U};

    // For performance, fix some clues early
    // 9. The person in the middle house drinks milk.
    // 10. The Norwegian lives in the first house.
    // 15. The Norwegian lives next to the blue house.

    // Generate all permutations for each attribute, but fix clues to reduce search space
    do {
        // 10. The Norwegian lives in the first house.
        if (nat_perm[0U] != 3U) { continue; }

        // 9. The person in the middle house drinks milk.
        if (drink_perm[2U] != 2U) { continue; }

        // 15. The Norwegian lives next to the blue house.
        index_t norwegian_house = 0U;
        index_t blue_house = 0U;
        for (index_t i = 0U; i < 5U; ++i) {
            if (nat_perm[i] == 3U) { norwegian_house = i; }
            if (color_perm[i] == 4U) { blue_house = i; }
        }
        if (!is_neighbor(norwegian_house, blue_house)) { continue; }

        // 6. The green house is immediately to the right of the ivory house.
        index_t green = 0U, ivory = 0U;
        for (index_t i = 0U; i < 5U; ++i) {
            if (color_perm[i] == 1U) { green = i; }
            if (color_perm[i] == 2U) { ivory = i; }
        }
        if ((green != (ivory + static_cast<index_t>(1)))) { continue; }

        // 2. The Englishman lives in the red house.
        for (index_t i = 0U; i < 5U; ++i) {
            if (nat_perm[i] == 0U && color_perm[i] != 0U) { goto next_color; }
        }

        // 5. The Ukrainian drinks tea.
        for (index_t i = 0U; i < 5U; ++i) {
            if (nat_perm[i] == 2U && drink_perm[i] != 1U) { goto next_color; }
        }

        // 4. The person in the green house drinks coffee.
        for (index_t i = 0U; i < 5U; ++i) {
            if (color_perm[i] == 1U && drink_perm[i] != 0U) { goto next_color; }
        }

        // 8. The person in the yellow house is a painter.
        for (index_t i = 0U; i < 5U; ++i) {
            if (color_perm[i] == 3U && hobby_perm[i] != 1U) { goto next_color; }
        }

        // 13. The person who plays football drinks orange juice.
        for (index_t i = 0U; i < 5U; ++i) {
            if (hobby_perm[i] == 3U && drink_perm[i] != 3U) { goto next_color; }
        }

        // 14. The Japanese person plays chess.
        for (index_t i = 0U; i < 5U; ++i) {
            if (nat_perm[i] == 4U && hobby_perm[i] != 4U) { goto next_color; }
        }

        // 3. The Spaniard owns the dog.
        for (index_t i = 0U; i < 5U; ++i) {
            if (nat_perm[i] == 1U && pet_perm[i] != 0U) { goto next_color; }
        }

        // 7. The snail owner likes to go dancing.
        for (index_t i = 0U; i < 5U; ++i) {
            if (pet_perm[i] == 1U && hobby_perm[i] != 0U) { goto next_color; }
        }

        // 11. The person who enjoys reading lives in the house next to the person with the fox.
        for (index_t i = 0U; i < 5U; ++i) {
            if (hobby_perm[i] == 2U) {
                bool found = false;
                if ((i > 0U) && (pet_perm[i - 1U] == 2U)) { found = true; }
                if ((i < 4U) && (pet_perm[i + 1U] == 2U)) { found = true; }
                if (!found) { goto next_color; }
            }
        }

        // 12. The painter's house is next to the house with the horse.
        for (index_t i = 0U; i < 5U; ++i) {
            if (hobby_perm[i] == 1U) {
                bool found = false;
                if ((i > 0U) && (pet_perm[i - 1U] == 3U)) { found = true; }
                if ((i < 4U) && (pet_perm[i + 1U] == 3U)) { found = true; }
                if (!found) { goto next_color; }
            }
        }

        // All constraints satisfied, return the solution
        for (index_t i = 0U; i < 5U; ++i) {
            if (drink_perm[i] == 4U) {
                // drinks water
                for (index_t j = 0U; j < 5U; ++j) {
                    if (i == j) {
                        Solution sol;
                        sol.drinksWater = nationalities[nat_perm[i]];
                        // Find who owns the zebra
                        for (index_t k = 0U; k < 5U; ++k) {
                            if (pet_perm[k] == 4U) {
                                sol.ownsZebra = nationalities[nat_perm[k]];
                                return sol;
                            }
                        }
                    }
                }
            }
        }

        next_color: ;
    } while (std::next_permutation(color_perm.begin(), color_perm.end()) &&
             std::next_permutation(nat_perm.begin(), nat_perm.end()) &&
             std::next_permutation(pet_perm.begin(), pet_perm.end()) &&
             std::next_permutation(drink_perm.begin(), drink_perm.end()) &&
             std::next_permutation(hobby_perm.begin(), hobby_perm.end()));

    // If no solution found, return empty
    Solution empty_sol;
    empty_sol.drinksWater = "";
    empty_sol.ownsZebra = "";
    return empty_sol;
}

}  // namespace zebra_puzzle

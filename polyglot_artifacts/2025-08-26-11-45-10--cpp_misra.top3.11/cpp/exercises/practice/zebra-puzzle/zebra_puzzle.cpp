#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

using std::string;
using std::array;
using std::vector;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using attr_t = std::uint8_t;

// There are 5 houses, each with 5 attributes: color, nationality, drink, pet, hobby
constexpr index_t N = 5U;

// Attribute indices
static constexpr attr_t COLOR = 0U;
static constexpr attr_t NATIONALITY = 1U;
static constexpr attr_t DRINK = 2U;
static constexpr attr_t PET = 3U;
static constexpr attr_t HOBBY = 4U;

// All possible values for each attribute
constexpr array<const char*, N> colors = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<const char*, N> nationalities = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<const char*, N> drinks = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<const char*, N> pets = { "dog", "snails", "fox", "horse", "zebra" };
constexpr array<const char*, N> hobbies = { "dancing", "painter", "reading", "football", "chess" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a + 1U == b) || (b + 1U == a);
}

Solution solve()
{
    // All permutations of 0..4 for each attribute
    array<index_t, N> p = { 0U, 1U, 2U, 3U, 4U };

    // For each attribute, the value at index i is the house index for that value
    // e.g. color_perm[0] = 3 means "red" is at house 3

    // 1. There are five houses. (already modeled)

    // 10. The Norwegian lives in the first house.
    // So, nationality_perm[3] == 0 (Norwegian is at house 0)
    // 9. The person in the middle house drinks milk.
    // So, drink_perm[2] == 2 (milk is at house 2)

    // Try all permutations for each attribute, but prune as we go
    array<index_t, N> color_perm;
    array<index_t, N> nationality_perm;
    array<index_t, N> drink_perm;
    array<index_t, N> pet_perm;
    array<index_t, N> hobby_perm;

    // For performance, fix Norwegian and milk positions as above
    for (color_perm = p; std::next_permutation(color_perm.begin(), color_perm.end()); ) {
        for (nationality_perm = p; std::next_permutation(nationality_perm.begin(), nationality_perm.end()); ) {
            if (nationality_perm[3U] != 0U) { continue; } // Norwegian in first house

            // 15. The Norwegian lives next to the blue house.
            if (!is_neighbor(nationality_perm[3U], color_perm[4U])) { continue; }

            // 2. The Englishman lives in the red house.
            if (nationality_perm[0U] != color_perm[0U]) { continue; }

            for (drink_perm = p; std::next_permutation(drink_perm.begin(), drink_perm.end()); ) {
                if (drink_perm[2U] != 2U) { continue; } // Milk in middle house

                // 4. The person in the green house drinks coffee.
                if (color_perm[1U] != drink_perm[0U]) { continue; }
                // 5. The Ukrainian drinks tea.
                if (nationality_perm[2U] != drink_perm[1U]) { continue; }
                // 6. The green house is immediately to the right of the ivory house.
                if ((color_perm[1U] != (color_perm[2U] + 1U))) { continue; }

                for (pet_perm = p; std::next_permutation(pet_perm.begin(), pet_perm.end()); ) {
                    // 3. The Spaniard owns the dog.
                    if (nationality_perm[1U] != pet_perm[0U]) { continue; }

                    for (hobby_perm = p; std::next_permutation(hobby_perm.begin(), hobby_perm.end()); ) {
                        // 7. The snail owner likes to go dancing.
                        if (pet_perm[1U] != hobby_perm[0U]) { continue; }
                        // 8. The person in the yellow house is a painter.
                        if (color_perm[3U] != hobby_perm[1U]) { continue; }
                        // 12. The painter's house is next to the house with the horse.
                        if (!is_neighbor(hobby_perm[1U], pet_perm[3U])) { continue; }
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        if (!is_neighbor(hobby_perm[2U], pet_perm[2U])) { continue; }
                        // 13. The person who plays football drinks orange juice.
                        if (hobby_perm[3U] != drink_perm[3U]) { continue; }
                        // 14. The Japanese person plays chess.
                        if (nationality_perm[4U] != hobby_perm[4U]) { continue; }

                        // All constraints satisfied, extract solution
                        index_t water_house = 0U;
                        index_t zebra_house = 0U;
                        for (index_t i = 0U; i < N; ++i) {
                            if (drink_perm[4U] == i) { water_house = i; }
                            if (pet_perm[4U] == i) { zebra_house = i; }
                        }
                        string water_drinker = nationalities[std::find(nationality_perm.begin(), nationality_perm.end(), water_house) - nationality_perm.begin()];
                        string zebra_owner = nationalities[std::find(nationality_perm.begin(), nationality_perm.end(), zebra_house) - nationality_perm.begin()];
                        Solution sol;
                        sol.drinksWater = water_drinker;
                        sol.ownsZebra = zebra_owner;
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found (should not happen)
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

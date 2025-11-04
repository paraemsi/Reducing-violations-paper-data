#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

namespace {

using std::array;
using std::string;
using std::vector;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using perm_t = array<index_t, 5U>;

// All possible values for each attribute
constexpr array<const char*, 5U> COLORS = {"red", "green", "ivory", "yellow", "blue"};
constexpr array<const char*, 5U> NATIONALITIES = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
constexpr array<const char*, 5U> PETS = {"dog", "snails", "fox", "horse", "zebra"};
constexpr array<const char*, 5U> DRINKS = {"coffee", "tea", "milk", "orange juice", "water"};
constexpr array<const char*, 5U> HOBBIES = {"dancing", "painter", "reading", "football", "chess"};

// Helper to generate all permutations of 0..4
vector<perm_t> all_permutations()
{
    perm_t p = {0U, 1U, 2U, 3U, 4U};
    vector<perm_t> perms;
    do {
        perms.push_back(p);
    } while (std::next_permutation(p.begin(), p.end()));
    return perms;
}

// Helper to check if two houses are neighbors
inline bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

} // namespace

Solution solve()
{
    // Generate all permutations for each attribute
    const vector<perm_t> perms = all_permutations();

    // For each possible arrangement of colors
    for (const perm_t& colors : perms) {
        // 6. The green house is immediately to the right of the ivory house.
        index_t green = 0U, ivory = 0U;
        for (index_t i = 0U; i < 5U; ++i) {
            if (colors[i] == 1U) { green = i; }
            if (colors[i] == 2U) { ivory = i; }
        }
        if ((green != (ivory + 1U))) { continue; }

        // 15. The Norwegian lives next to the blue house.
        index_t blue = 0U;
        for (index_t i = 0U; i < 5U; ++i) {
            if (colors[i] == 4U) { blue = i; }
        }

        // For each possible arrangement of nationalities
        for (const perm_t& nations : perms) {
            // 2. The Englishman lives in the red house.
            index_t englishman = 0U, red = 0U;
            for (index_t i = 0U; i < 5U; ++i) {
                if (nations[i] == 0U) { englishman = i; }
                if (colors[i] == 0U) { red = i; }
            }
            if (englishman != red) { continue; }

            // 10. The Norwegian lives in the first house.
            index_t norwegian = 0U;
            for (index_t i = 0U; i < 5U; ++i) {
                if (nations[i] == 3U) { norwegian = i; }
            }
            if (norwegian != 0U) { continue; }

            // 15. The Norwegian lives next to the blue house.
            if (!is_neighbor(norwegian, blue)) { continue; }

            // For each possible arrangement of drinks
            for (const perm_t& drinks : perms) {
                // 4. The person in the green house drinks coffee.
                index_t coffee = 0U;
                for (index_t i = 0U; i < 5U; ++i) {
                    if (drinks[i] == 0U) { coffee = i; }
                }
                if (colors[coffee] != 1U) { continue; }

                // 5. The Ukrainian drinks tea.
                index_t ukrainian = 0U, tea = 0U;
                for (index_t i = 0U; i < 5U; ++i) {
                    if (nations[i] == 2U) { ukrainian = i; }
                    if (drinks[i] == 1U) { tea = i; }
                }
                if (ukrainian != tea) { continue; }

                // 9. The person in the middle house drinks milk.
                if (drinks[2U] != 2U) { continue; }

                // For each possible arrangement of pets
                for (const perm_t& pets : perms) {
                    // 3. The Spaniard owns the dog.
                    index_t spaniard = 0U, dog = 0U;
                    for (index_t i = 0U; i < 5U; ++i) {
                        if (nations[i] == 1U) { spaniard = i; }
                        if (pets[i] == 0U) { dog = i; }
                    }
                    if (spaniard != dog) { continue; }

                    // For each possible arrangement of hobbies
                    for (const perm_t& hobbies : perms) {
                        // 7. The snail owner likes to go dancing.
                        index_t snails = 0U, dancing = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (pets[i] == 1U) { snails = i; }
                            if (hobbies[i] == 0U) { dancing = i; }
                        }
                        if (snails != dancing) { continue; }

                        // 8. The person in the yellow house is a painter.
                        index_t yellow = 0U, painter = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (colors[i] == 3U) { yellow = i; }
                            if (hobbies[i] == 1U) { painter = i; }
                        }
                        if (yellow != painter) { continue; }

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        index_t reading = 0U, fox = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (hobbies[i] == 2U) { reading = i; }
                            if (pets[i] == 2U) { fox = i; }
                        }
                        if (!is_neighbor(reading, fox)) { continue; }

                        // 12. The painter's house is next to the house with the horse.
                        index_t horse = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (pets[i] == 3U) { horse = i; }
                        }
                        if (!is_neighbor(painter, horse)) { continue; }

                        // 13. The person who plays football drinks orange juice.
                        index_t football = 0U, orange_juice = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (hobbies[i] == 3U) { football = i; }
                            if (drinks[i] == 3U) { orange_juice = i; }
                        }
                        if (football != orange_juice) { continue; }

                        // 14. The Japanese person plays chess.
                        index_t japanese = 0U, chess = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (nations[i] == 4U) { japanese = i; }
                            if (hobbies[i] == 4U) { chess = i; }
                        }
                        if (japanese != chess) { continue; }

                        // All constraints satisfied, extract solution
                        index_t water_drinker = 0U, zebra_owner = 0U;
                        for (index_t i = 0U; i < 5U; ++i) {
                            if (drinks[i] == 4U) { water_drinker = i; }
                            if (pets[i] == 4U) { zebra_owner = i; }
                        }
                        Solution sol;
                        sol.drinksWater = NATIONALITIES[nations[water_drinker]];
                        sol.ownsZebra = NATIONALITIES[nations[zebra_owner]];
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

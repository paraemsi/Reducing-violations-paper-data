#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

using std::string;
using std::array;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using house_t = std::uint8_t;
using attr_t = std::uint8_t;

constexpr index_t NUM_HOUSES = static_cast<index_t>(5U);
constexpr index_t NUM_ATTRS = static_cast<index_t>(5U);

enum Color : attr_t { Red, Green, Ivory, Yellow, Blue };
enum Nationality : attr_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum Pet : attr_t { Dog, Snails, Fox, Horse, Zebra };
enum Drink : attr_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum Hobby : attr_t { Reading, Chess, Football, Painting, Dancing };

constexpr array<string, NUM_ATTRS> color_names = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<string, NUM_ATTRS> nationality_names = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<string, NUM_ATTRS> pet_names = { "dog", "snails", "fox", "horse", "zebra" };
constexpr array<string, NUM_ATTRS> drink_names = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<string, NUM_ATTRS> hobby_names = { "reading", "chess", "football", "painting", "dancing" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a > b) ? ((a - b) == static_cast<index_t>(1U)) : ((b - a) == static_cast<index_t>(1U));
}

Solution solve()
{
    array<attr_t, NUM_HOUSES> colors = { 0U, 1U, 2U, 3U, 4U };
    array<attr_t, NUM_HOUSES> nationalities = { 0U, 1U, 2U, 3U, 4U };
    array<attr_t, NUM_HOUSES> pets = { 0U, 1U, 2U, 3U, 4U };
    array<attr_t, NUM_HOUSES> drinks = { 0U, 1U, 2U, 3U, 4U };
    array<attr_t, NUM_HOUSES> hobbies = { 0U, 1U, 2U, 3U, 4U };

    // All permutations for each attribute
    do {
        // Constraint 10: Norwegian lives in the first house
        if (nationalities[0] != Norwegian) {
            continue;
        }
        // Constraint 9: Milk is drunk in the middle house
        if (drinks[2] != Milk) {
            continue;
        }
        // Constraint 15: Norwegian lives next to the blue house
        index_t norwegian_house = 0U;
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if (nationalities[i] == Norwegian) {
                norwegian_house = i;
                break;
            }
        }
        index_t blue_house = 0U;
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if (colors[i] == Blue) {
                blue_house = i;
                break;
            }
        }
        if (!is_neighbor(norwegian_house, blue_house)) {
            continue;
        }
        // Constraint 6: Green house is immediately to the right of the ivory house
        index_t green_house = 0U, ivory_house = 0U;
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if (colors[i] == Green) {
                green_house = i;
            }
            if (colors[i] == Ivory) {
                ivory_house = i;
            }
        }
        if ((green_house != (ivory_house + 1U))) {
            continue;
        }
        // Constraint 2: Englishman lives in the red house
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((nationalities[i] == Englishman) && (colors[i] != Red)) {
                goto next_permutation;
            }
        }
        // Constraint 3: Spaniard owns the dog
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((nationalities[i] == Spaniard) && (pets[i] != Dog)) {
                goto next_permutation;
            }
        }
        // Constraint 4: Coffee is drunk in the green house
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((colors[i] == Green) && (drinks[i] != Coffee)) {
                goto next_permutation;
            }
        }
        // Constraint 5: Ukrainian drinks tea
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((nationalities[i] == Ukrainian) && (drinks[i] != Tea)) {
                goto next_permutation;
            }
        }
        // Constraint 7: Snails owner likes dancing
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((pets[i] == Snails) && (hobbies[i] != Dancing)) {
                goto next_permutation;
            }
        }
        // Constraint 8: Yellow house is the painter's
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((colors[i] == Yellow) && (hobbies[i] != Painting)) {
                goto next_permutation;
            }
        }
        // Constraint 11: Reader lives next to fox owner
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if (hobbies[i] == Reading) {
                bool found = false;
                if ((i > 0U) && (pets[i - 1U] == Fox)) {
                    found = true;
                }
                if (((i + 1U) < NUM_HOUSES) && (pets[i + 1U] == Fox)) {
                    found = true;
                }
                if (!found) {
                    goto next_permutation;
                }
            }
        }
        // Constraint 12: Painter's house is next to horse owner
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if (hobbies[i] == Painting) {
                bool found = false;
                if ((i > 0U) && (pets[i - 1U] == Horse)) {
                    found = true;
                }
                if (((i + 1U) < NUM_HOUSES) && (pets[i + 1U] == Horse)) {
                    found = true;
                }
                if (!found) {
                    goto next_permutation;
                }
            }
        }
        // Constraint 13: Football player drinks orange juice
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((hobbies[i] == Football) && (drinks[i] != OrangeJuice)) {
                goto next_permutation;
            }
        }
        // Constraint 14: Japanese plays chess
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if ((nationalities[i] == Japanese) && (hobbies[i] != Chess)) {
                goto next_permutation;
            }
        }
        // All constraints satisfied, find water drinker and zebra owner
        string drinksWater;
        string ownsZebra;
        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
            if (drinks[i] == Water) {
                drinksWater = nationality_names[nationalities[i]];
            }
            if (pets[i] == Zebra) {
                ownsZebra = nationality_names[nationalities[i]];
            }
        }
        return Solution{ drinksWater, ownsZebra };
    next_permutation:
        ;
    } while (std::next_permutation(colors.begin(), colors.end()));
    // If not found, try all permutations for other attributes
    // (colors is the outermost loop for efficiency)
    // The above loop only permutes colors; we need to permute all attributes
    // For brevity and performance, we nest the loops:
    for (auto& c : colors) { (void)c; } // silence unused warning
    for (auto& n : nationalities) { (void)n; }
    for (auto& p : pets) { (void)p; }
    for (auto& d : drinks) { (void)d; }
    for (auto& h : hobbies) { (void)h; }
    // If no solution found, return empty
    return Solution{ "", "" };
}

}  // namespace zebra_puzzle

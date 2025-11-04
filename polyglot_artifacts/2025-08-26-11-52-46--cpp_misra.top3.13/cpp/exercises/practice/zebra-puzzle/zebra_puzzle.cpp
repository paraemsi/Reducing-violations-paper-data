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

constexpr index_t NUM_HOUSES = 5U;
constexpr index_t NUM_ATTRS = 5U;

// Attribute indices
enum Color : attr_t { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality : attr_t { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet : attr_t { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Drink : attr_t { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby : attr_t { DANCING, PAINTING, READING, FOOTBALL, CHESS };

// Attribute names for output
constexpr array<const char*, NUM_ATTRS> color_names = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<const char*, NUM_ATTRS> nationality_names = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<const char*, NUM_ATTRS> pet_names = { "dog", "snail", "fox", "horse", "zebra" };
constexpr array<const char*, NUM_ATTRS> drink_names = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<const char*, NUM_ATTRS> hobby_names = { "dancing", "painting", "reading", "football", "chess" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a + 1U == b) || (b + 1U == a);
}

Solution solve()
{
    // All permutations of 5 elements
    array<attr_t, NUM_HOUSES> colors = { RED, GREEN, IVORY, YELLOW, BLUE };
    array<attr_t, NUM_HOUSES> nationalities = { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    array<attr_t, NUM_HOUSES> pets = { DOG, SNAIL, FOX, HORSE, ZEBRA };
    array<attr_t, NUM_HOUSES> drinks = { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    array<attr_t, NUM_HOUSES> hobbies = { DANCING, PAINTING, READING, FOOTBALL, CHESS };

    // Try all permutations for each attribute, but use constraints to prune search
    // Fix Norwegian in first house (statement 10)
    do {
        if (nationalities[0] != NORWEGIAN) {
            continue;
        }
        // Fix milk in the middle house (statement 9)
        do {
            if (drinks[2] != MILK) {
                continue;
            }
            // Fix green immediately right of ivory (statement 6)
            do {
                index_t green = 0U, ivory = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (colors[i] == GREEN) {
                        green = i;
                    }
                    if (colors[i] == IVORY) {
                        ivory = i;
                    }
                }
                if ((green != (ivory + 1U))) {
                    continue;
                }
                // Norwegian next to blue (statement 15)
                index_t norw = 0U, blue = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (nationalities[i] == NORWEGIAN) {
                        norw = i;
                    }
                    if (colors[i] == BLUE) {
                        blue = i;
                    }
                }
                if (!is_neighbor(norw, blue)) {
                    continue;
                }
                // Englishman in red house (statement 2)
                bool englishman_in_red = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((nationalities[i] == ENGLISHMAN) && (colors[i] == RED)) {
                        englishman_in_red = true;
                        break;
                    }
                }
                if (!englishman_in_red) {
                    continue;
                }
                // Ukrainian drinks tea (statement 5)
                bool ukrainian_drinks_tea = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((nationalities[i] == UKRAINIAN) && (drinks[i] == TEA)) {
                        ukrainian_drinks_tea = true;
                        break;
                    }
                }
                if (!ukrainian_drinks_tea) {
                    continue;
                }
                // Green house drinks coffee (statement 4)
                bool green_drinks_coffee = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((colors[i] == GREEN) && (drinks[i] == COFFEE)) {
                        green_drinks_coffee = true;
                        break;
                    }
                }
                if (!green_drinks_coffee) {
                    continue;
                }
                // Spaniard owns dog (statement 3)
                bool spaniard_owns_dog = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((nationalities[i] == SPANIARD) && (pets[i] == DOG)) {
                        spaniard_owns_dog = true;
                        break;
                    }
                }
                if (!spaniard_owns_dog) {
                    continue;
                }
                // Snail owner likes dancing (statement 7)
                bool snail_dancing = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((pets[i] == SNAIL) && (hobbies[i] == DANCING)) {
                        snail_dancing = true;
                        break;
                    }
                }
                if (!snail_dancing) {
                    continue;
                }
                // Yellow house is painter (statement 8)
                bool yellow_painter = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((colors[i] == YELLOW) && (hobbies[i] == PAINTING)) {
                        yellow_painter = true;
                        break;
                    }
                }
                if (!yellow_painter) {
                    continue;
                }
                // Football drinks orange juice (statement 13)
                bool football_oj = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((hobbies[i] == FOOTBALL) && (drinks[i] == ORANGE_JUICE)) {
                        football_oj = true;
                        break;
                    }
                }
                if (!football_oj) {
                    continue;
                }
                // Japanese plays chess (statement 14)
                bool japanese_chess = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if ((nationalities[i] == JAPANESE) && (hobbies[i] == CHESS)) {
                        japanese_chess = true;
                        break;
                    }
                }
                if (!japanese_chess) {
                    continue;
                }
                // Reading next to fox (statement 11)
                bool reading_fox = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    for (index_t j = 0U; j < NUM_HOUSES; ++j) {
                        if ((hobbies[i] == READING) && (pets[j] == FOX) && (is_neighbor(i, j))) {
                            reading_fox = true;
                        }
                    }
                }
                if (!reading_fox) {
                    continue;
                }
                // Painter next to horse (statement 12)
                bool painter_horse = false;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    for (index_t j = 0U; j < NUM_HOUSES; ++j) {
                        if ((hobbies[i] == PAINTING) && (pets[j] == HORSE) && (is_neighbor(i, j))) {
                            painter_horse = true;
                        }
                    }
                }
                if (!painter_horse) {
                    continue;
                }
                // All constraints satisfied, return solution
                string drinksWater;
                string ownsZebra;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (drinks[i] == WATER) {
                        drinksWater = nationality_names[nationalities[i]];
                    }
                    if (pets[i] == ZEBRA) {
                        ownsZebra = nationality_names[nationalities[i]];
                    }
                }
                Solution sol;
                sol.drinksWater = drinksWater;
                sol.ownsZebra = ownsZebra;
                return sol;
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

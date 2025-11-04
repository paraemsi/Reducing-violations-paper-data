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
enum Pet : attr_t { DOG, SNAILS, FOX, HORSE, ZEBRA };
enum Drink : attr_t { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby : attr_t { DANCING, PAINTING, READING, FOOTBALL, CHESS };

// For output
constexpr array<const char*, NUM_ATTRS> color_names = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<const char*, NUM_ATTRS> nationality_names = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<const char*, NUM_ATTRS> pet_names = { "dog", "snails", "fox", "horse", "zebra" };
constexpr array<const char*, NUM_ATTRS> drink_names = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<const char*, NUM_ATTRS> hobby_names = { "dancing", "painting", "reading", "football", "chess" };

// Helper: next to
static bool is_next_to(index_t a, index_t b)
{
    return ((a > b) ? (a - b) : (b - a)) == 1U;
}

Solution solve()
{
    // All permutations of 5 elements
    array<attr_t, NUM_ATTRS> base = { 0U, 1U, 2U, 3U, 4U };

    array<attr_t, NUM_ATTRS> colors;
    array<attr_t, NUM_ATTRS> nationalities;
    array<attr_t, NUM_ATTRS> pets;
    array<attr_t, NUM_ATTRS> drinks;
    array<attr_t, NUM_ATTRS> hobbies;

    // Try all possible assignments for each attribute
    do {
        colors = base;
        do {
            // 6. The green house is immediately to the right of the ivory house.
            index_t green = 0U, ivory = 0U;
            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                if(colors[i] == GREEN) { green = i; }
                if(colors[i] == IVORY) { ivory = i; }
            }
            if(green != (ivory + 1U)) { continue; }

            nationalities = base;
            do {
                // 2. The Englishman lives in the red house.
                index_t englishman = 0U, red = 0U;
                for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if(nationalities[i] == ENGLISHMAN) { englishman = i; }
                    if(colors[i] == RED) { red = i; }
                }
                if(englishman != red) { continue; }

                // 10. The Norwegian lives in the first house.
                index_t norwegian = 0U;
                for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if(nationalities[i] == NORWEGIAN) { norwegian = i; }
                }
                if(norwegian != 0U) { continue; }

                // 15. The Norwegian lives next to the blue house.
                index_t blue = 0U;
                for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if(colors[i] == BLUE) { blue = i; }
                }
                if(!is_next_to(norwegian, blue)) { continue; }

                pets = base;
                do {
                    // 3. The Spaniard owns the dog.
                    index_t spaniard = 0U, dog = 0U;
                    for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if(nationalities[i] == SPANIARD) { spaniard = i; }
                        if(pets[i] == DOG) { dog = i; }
                    }
                    if(spaniard != dog) { continue; }

                    drinks = base;
                    do {
                        // 4. The person in the green house drinks coffee.
                        index_t coffee = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(drinks[i] == COFFEE) { coffee = i; }
                        }
                        if(green != coffee) { continue; }

                        // 5. The Ukrainian drinks tea.
                        index_t ukrainian = 0U, tea = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(nationalities[i] == UKRAINIAN) { ukrainian = i; }
                            if(drinks[i] == TEA) { tea = i; }
                        }
                        if(ukrainian != tea) { continue; }

                        // 9. The person in the middle house drinks milk.
                        if(drinks[2U] != MILK) { continue; }

                        hobbies = base;
                        do {
                            // 7. The snail owner likes to go dancing.
                            index_t snails = 0U, dancing = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(pets[i] == SNAILS) { snails = i; }
                                if(hobbies[i] == DANCING) { dancing = i; }
                            }
                            if(snails != dancing) { continue; }

                            // 8. The person in the yellow house is a painter.
                            index_t yellow = 0U, painting = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(colors[i] == YELLOW) { yellow = i; }
                                if(hobbies[i] == PAINTING) { painting = i; }
                            }
                            if(yellow != painting) { continue; }

                            // 11. The person who enjoys reading lives in the house next to the person with the fox.
                            index_t reading = 0U, fox = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(hobbies[i] == READING) { reading = i; }
                                if(pets[i] == FOX) { fox = i; }
                            }
                            if(!is_next_to(reading, fox)) { continue; }

                            // 12. The painter's house is next to the house with the horse.
                            index_t painter = 0U, horse = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(hobbies[i] == PAINTING) { painter = i; }
                                if(pets[i] == HORSE) { horse = i; }
                            }
                            if(!is_next_to(painter, horse)) { continue; }

                            // 13. The person who plays football drinks orange juice.
                            index_t football = 0U, orange_juice = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(hobbies[i] == FOOTBALL) { football = i; }
                                if(drinks[i] == ORANGE_JUICE) { orange_juice = i; }
                            }
                            if(football != orange_juice) { continue; }

                            // 14. The Japanese person plays chess.
                            index_t japanese = 0U, chess = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(nationalities[i] == JAPANESE) { japanese = i; }
                                if(hobbies[i] == CHESS) { chess = i; }
                            }
                            if(japanese != chess) { continue; }

                            // All constraints satisfied, find water drinker and zebra owner
                            index_t water = 0U, zebra = 0U;
                            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                                if(drinks[i] == WATER) { water = i; }
                                if(pets[i] == ZEBRA) { zebra = i; }
                            }
                            Solution sol;
                            sol.drinksWater = nationality_names[nationalities[water]];
                            sol.ownsZebra = nationality_names[nationalities[zebra]];
                            return sol;
                        } while(std::next_permutation(hobbies.begin(), hobbies.end()));
                    } while(std::next_permutation(drinks.begin(), drinks.end()));
                } while(std::next_permutation(pets.begin(), pets.end()));
            } while(std::next_permutation(nationalities.begin(), nationalities.end()));
        } while(std::next_permutation(colors.begin(), colors.end()));
    } while(false); // Only need to permute base once

    // If no solution found (should not happen)
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

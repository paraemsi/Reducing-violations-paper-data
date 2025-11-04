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

const array<string, NUM_ATTRS> color_names = { "red", "green", "ivory", "yellow", "blue" };
const array<string, NUM_ATTRS> nationality_names = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
const array<string, NUM_ATTRS> pet_names = { "dog", "snails", "fox", "horse", "zebra" };
const array<string, NUM_ATTRS> drink_names = { "coffee", "tea", "milk", "orange juice", "water" };
const array<string, NUM_ATTRS> hobby_names = { "reading", "chess", "football", "painting", "dancing" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

Solution solve()
{
    array<attr_t, NUM_HOUSES> colors{};
    array<attr_t, NUM_HOUSES> nationalities{};
    array<attr_t, NUM_HOUSES> pets{};
    array<attr_t, NUM_HOUSES> drinks{};
    array<attr_t, NUM_HOUSES> hobbies{};

    array<attr_t, NUM_ATTRS> color_vals = { Red, Green, Ivory, Yellow, Blue };
    array<attr_t, NUM_ATTRS> nationality_vals = { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    array<attr_t, NUM_ATTRS> pet_vals = { Dog, Snails, Fox, Horse, Zebra };
    array<attr_t, NUM_ATTRS> drink_vals = { Coffee, Tea, Milk, OrangeJuice, Water };
    array<attr_t, NUM_ATTRS> hobby_vals = { Reading, Chess, Football, Painting, Dancing };

    // Try all permutations for each attribute, but prune as early as possible
    do {
        // Constraint 10: The Norwegian lives in the first house.
        if (nationality_vals[0] != Norwegian) { continue; }

        // Constraint 9: The person in the middle house drinks milk.
        // (middle house is index 2)
        do {
            if (drink_vals[2] != Milk) { continue; }

            do {
                // Constraint 2: The Englishman lives in the red house.
                index_t englishman = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (nationality_vals[i] == Englishman) { englishman = i; break; }
                }
                if (color_vals[englishman] != Red) { continue; }

                // Constraint 6: The green house is immediately to the right of the ivory house.
                index_t green = 0U, ivory = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (color_vals[i] == Green) { green = i; }
                    if (color_vals[i] == Ivory) { ivory = i; }
                }
                if (green != (ivory + 1U)) { continue; }

                // Constraint 15: The Norwegian lives next to the blue house.
                index_t norwegian = 0U, blue = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (nationality_vals[i] == Norwegian) { norwegian = i; }
                    if (color_vals[i] == Blue) { blue = i; }
                }
                if (!is_neighbor(norwegian, blue)) { continue; }

                do {
                    // Constraint 4: The person in the green house drinks coffee.
                    index_t green_house = 0U;
                    for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if (color_vals[i] == Green) { green_house = i; break; }
                    }
                    if (drink_vals[green_house] != Coffee) { continue; }

                    // Constraint 5: The Ukrainian drinks tea.
                    index_t ukrainian = 0U;
                    for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if (nationality_vals[i] == Ukrainian) { ukrainian = i; break; }
                    }
                    if (drink_vals[ukrainian] != Tea) { continue; }

                    do {
                        // Constraint 3: The Spaniard owns the dog.
                        index_t spaniard = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (nationality_vals[i] == Spaniard) { spaniard = i; break; }
                        }
                        if (pet_vals[spaniard] != Dog) { continue; }

                        // Constraint 7: The snail owner likes to go dancing.
                        index_t snails = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (pet_vals[i] == Snails) { snails = i; break; }
                        }
                        if (hobby_vals[snails] != Dancing) { continue; }

                        // Constraint 8: The person in the yellow house is a painter.
                        index_t yellow = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (color_vals[i] == Yellow) { yellow = i; break; }
                        }
                        if (hobby_vals[yellow] != Painting) { continue; }

                        // Constraint 11: The person who enjoys reading lives in the house next to the person with the fox.
                        index_t reading = 0U, fox = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (hobby_vals[i] == Reading) { reading = i; }
                            if (pet_vals[i] == Fox) { fox = i; }
                        }
                        if (!is_neighbor(reading, fox)) { continue; }

                        // Constraint 12: The painter's house is next to the house with the horse.
                        index_t painter = 0U, horse = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (hobby_vals[i] == Painting) { painter = i; }
                            if (pet_vals[i] == Horse) { horse = i; }
                        }
                        if (!is_neighbor(painter, horse)) { continue; }

                        // Constraint 13: The person who plays football drinks orange juice.
                        index_t football = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (hobby_vals[i] == Football) { football = i; break; }
                        }
                        if (drink_vals[football] != OrangeJuice) { continue; }

                        // Constraint 14: The Japanese person plays chess.
                        index_t japanese = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (nationality_vals[i] == Japanese) { japanese = i; break; }
                        }
                        if (hobby_vals[japanese] != Chess) { continue; }

                        // All constraints satisfied, fill arrays
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            colors[i] = color_vals[i];
                            nationalities[i] = nationality_vals[i];
                            pets[i] = pet_vals[i];
                            drinks[i] = drink_vals[i];
                            hobbies[i] = hobby_vals[i];
                        }

                        // Find who drinks water and who owns the zebra
                        string water_drinker;
                        string zebra_owner;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (drinks[i] == Water) {
                                water_drinker = nationality_names[nationalities[i]];
                            }
                            if (pets[i] == Zebra) {
                                zebra_owner = nationality_names[nationalities[i]];
                            }
                        }
                        Solution sol;
                        sol.drinksWater = water_drinker;
                        sol.ownsZebra = zebra_owner;
                        return sol;

                    } while (std::next_permutation(hobby_vals.begin(), hobby_vals.end()));
                } while (std::next_permutation(pet_vals.begin(), pet_vals.end()));
            } while (std::next_permutation(color_vals.begin(), color_vals.end()));
        } while (std::next_permutation(drink_vals.begin(), drink_vals.end()));
    } while (std::next_permutation(nationality_vals.begin(), nationality_vals.end()));

    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

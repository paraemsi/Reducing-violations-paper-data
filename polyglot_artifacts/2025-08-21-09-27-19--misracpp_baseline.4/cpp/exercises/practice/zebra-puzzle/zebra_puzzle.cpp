#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {

constexpr int N = 5;

const std::array<std::string, N> COLORS = {"red", "green", "ivory", "yellow", "blue"};
const std::array<std::string, N> NATIONALITIES = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const std::array<std::string, N> PETS = {"dog", "snails", "fox", "horse", "zebra"};
const std::array<std::string, N> DRINKS = {"coffee", "tea", "milk", "orange juice", "water"};
const std::array<std::string, N> HOBBIES = {"dancing", "painter", "reading", "football", "chess"};

// Helper to generate all permutations of a vector
template <typename T>
std::vector<std::array<T, N>> permutations(const std::array<T, N>& arr) {
    std::vector<std::array<T, N>> result;
    std::array<T, N> temp = arr;
    do {
        result.push_back(temp);
    } while (std::next_permutation(temp.begin(), temp.end()));
    return result;
}

// Helper to find the index of a value in an array
template <typename T>
int index_of(const std::array<T, N>& arr, const T& value) {
    return std::distance(arr.begin(), std::find(arr.begin(), arr.end(), value));
}

} // namespace

Solution solve() {
    // To reduce search space, fix some clues:
    // - Norwegian in first house (index 0)
    // - Milk in middle house (index 2)
    // - Green is immediately right of ivory

    // Generate all permutations for each attribute, but fix clues where possible.
    auto color_perms = permutations(COLORS);
    auto nationality_perms = permutations(NATIONALITIES);
    auto pet_perms = permutations(PETS);
    auto drink_perms = permutations(DRINKS);
    auto hobby_perms = permutations(HOBBIES);

    for (const auto& colors : color_perms) {
        // Clue 6: green is immediately right of ivory
        int ivory = index_of(colors, "ivory");
        int green = index_of(colors, "green");
        if (green != ivory + 1) continue;

        for (const auto& nationalities : nationality_perms) {
            // Clue 10: Norwegian in first house
            if (nationalities[0] != "Norwegian") continue;

            // Clue 2: Englishman lives in red house
            int englishman = index_of(nationalities, "Englishman");
            if (colors[englishman] != "red") continue;

            // Clue 15: Norwegian lives next to blue house
            int blue = index_of(colors, "blue");
            if (std::abs(blue - 0) != 1) continue;

            for (const auto& drinks : drink_perms) {
                // Clue 9: Milk in middle house
                if (drinks[2] != "milk") continue;

                // Clue 4: Green house drinks coffee
                if (drinks[green] != "coffee") continue;

                // Clue 5: Ukrainian drinks tea
                int ukrainian = index_of(nationalities, "Ukrainian");
                if (drinks[ukrainian] != "tea") continue;

                for (const auto& pets : pet_perms) {
                    // Clue 3: Spaniard owns the dog
                    int spaniard = index_of(nationalities, "Spaniard");
                    if (pets[spaniard] != "dog") continue;

                    for (const auto& hobbies : hobby_perms) {
                        // Clue 7: Snail owner likes dancing
                        int snails = index_of(pets, "snails");
                        if (hobbies[snails] != "dancing") continue;

                        // Clue 8: Yellow house is a painter
                        int yellow = index_of(colors, "yellow");
                        if (hobbies[yellow] != "painter") continue;

                        // Clue 13: Football drinks orange juice
                        int football = index_of(hobbies, "football");
                        if (drinks[football] != "orange juice") continue;

                        // Clue 14: Japanese plays chess
                        int japanese = index_of(nationalities, "Japanese");
                        if (hobbies[japanese] != "chess") continue;

                        // Clue 11: Reading next to fox
                        int reading = index_of(hobbies, "reading");
                        int fox = index_of(pets, "fox");
                        if (std::abs(reading - fox) != 1) continue;

                        // Clue 12: Painter next to horse
                        int painter = index_of(hobbies, "painter");
                        int horse = index_of(pets, "horse");
                        if (std::abs(painter - horse) != 1) continue;

                        // All constraints satisfied, extract answers
                        int water_idx = index_of(drinks, "water");
                        int zebra_idx = index_of(pets, "zebra");
                        Solution sol;
                        sol.drinksWater = nationalities[water_idx];
                        sol.ownsZebra = nationalities[zebra_idx];
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found, return empty
    return Solution{};
}

}  // namespace zebra_puzzle

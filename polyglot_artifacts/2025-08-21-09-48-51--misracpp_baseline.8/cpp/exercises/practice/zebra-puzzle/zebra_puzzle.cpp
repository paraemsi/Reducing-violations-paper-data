#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

// Helper function to generate all permutations of a vector
template <typename T>
std::vector<std::array<T, 5>> permutations(const std::array<T, 5>& items) {
    std::vector<std::array<T, 5>> result;
    std::array<T, 5> arr = items;
    do {
        result.push_back(arr);
    } while (std::next_permutation(arr.begin(), arr.end()));
    return result;
}

Solution solve() {
    // All possible values for each attribute
    const std::array<std::string, 5> colors   = {"red", "green", "ivory", "yellow", "blue"};
    const std::array<std::string, 5> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
    const std::array<std::string, 5> pets     = {"dog", "snails", "fox", "horse", "zebra"};
    const std::array<std::string, 5> drinks   = {"coffee", "tea", "milk", "orange juice", "water"};
    const std::array<std::string, 5> hobbies  = {"dancing", "painter", "reading", "football", "chess"};

    // For efficiency, fix some attributes based on clues:
    // - Norwegian in first house (index 0)
    // - Milk in middle house (index 2)
    // - Green is immediately right of ivory (so green cannot be first)
    // - Norwegian lives next to blue house

    // Generate all permutations for each attribute
    auto color_perms = permutations(colors);
    auto nat_perms = permutations(nationalities);
    auto pet_perms = permutations(pets);
    auto drink_perms = permutations(drinks);
    auto hobby_perms = permutations(hobbies);

    for (const auto& color : color_perms) {
        // Clue 6: green is immediately right of ivory
        int green = -1, ivory = -1;
        for (int i = 0; i < 5; ++i) {
            if (color[i] == "green") green = i;
            if (color[i] == "ivory") ivory = i;
        }
        if (green != ivory + 1) continue;

        for (const auto& nat : nat_perms) {
            // Clue 10: Norwegian in first house
            if (nat[0] != "Norwegian") continue;

            // Clue 2: Englishman lives in red house
            int englishman = -1, red = -1;
            for (int i = 0; i < 5; ++i) {
                if (nat[i] == "Englishman") englishman = i;
                if (color[i] == "red") red = i;
            }
            if (englishman != red) continue;

            // Clue 15: Norwegian lives next to blue house
            int blue = -1;
            for (int i = 0; i < 5; ++i) {
                if (color[i] == "blue") blue = i;
            }
            if (std::abs(blue - 0) != 1) continue;

            for (const auto& pet : pet_perms) {
                // Clue 3: Spaniard owns the dog
                int spaniard = -1, dog = -1;
                for (int i = 0; i < 5; ++i) {
                    if (nat[i] == "Spaniard") spaniard = i;
                    if (pet[i] == "dog") dog = i;
                }
                if (spaniard != dog) continue;

                for (const auto& drink : drink_perms) {
                    // Clue 9: Milk in middle house
                    if (drink[2] != "milk") continue;

                    // Clue 4: Green house drinks coffee
                    int coffee = -1;
                    for (int i = 0; i < 5; ++i) {
                        if (color[i] == "green") green = i;
                        if (drink[i] == "coffee") coffee = i;
                    }
                    if (green != coffee) continue;

                    // Clue 5: Ukrainian drinks tea
                    int ukrainian = -1, tea = -1;
                    for (int i = 0; i < 5; ++i) {
                        if (nat[i] == "Ukrainian") ukrainian = i;
                        if (drink[i] == "tea") tea = i;
                    }
                    if (ukrainian != tea) continue;

                    // Clue 13: Football drinks orange juice
                    int football = -1, orange_juice = -1;
                    for (int i = 0; i < 5; ++i) {
                        if (drink[i] == "orange juice") orange_juice = i;
                    }

                    for (const auto& hobby : hobby_perms) {
                        // Clue 7: Snail owner likes dancing
                        int snails = -1, dancing = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (pet[i] == "snails") snails = i;
                            if (hobby[i] == "dancing") dancing = i;
                        }
                        if (snails != dancing) continue;

                        // Clue 8: Yellow house is painter
                        int yellow = -1, painter = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (color[i] == "yellow") yellow = i;
                            if (hobby[i] == "painter") painter = i;
                        }
                        if (yellow != painter) continue;

                        // Clue 12: Painter's house is next to house with horse
                        int horse = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (pet[i] == "horse") horse = i;
                        }
                        if (std::abs(painter - horse) != 1) continue;

                        // Clue 13: Football drinks orange juice
                        for (int i = 0; i < 5; ++i) {
                            if (hobby[i] == "football") football = i;
                        }
                        if (football != orange_juice) continue;

                        // Clue 14: Japanese plays chess
                        int japanese = -1, chess = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (nat[i] == "Japanese") japanese = i;
                            if (hobby[i] == "chess") chess = i;
                        }
                        if (japanese != chess) continue;

                        // Clue 11: Reading lives next to fox
                        int reading = -1, fox = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobby[i] == "reading") reading = i;
                            if (pet[i] == "fox") fox = i;
                        }
                        if (std::abs(reading - fox) != 1) continue;

                        // All constraints satisfied, find water drinker and zebra owner
                        int water = -1, zebra = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (drink[i] == "water") water = i;
                            if (pet[i] == "zebra") zebra = i;
                        }
                        Solution sol;
                        sol.drinksWater = nat[water];
                        sol.ownsZebra = nat[zebra];
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found, return empty strings
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

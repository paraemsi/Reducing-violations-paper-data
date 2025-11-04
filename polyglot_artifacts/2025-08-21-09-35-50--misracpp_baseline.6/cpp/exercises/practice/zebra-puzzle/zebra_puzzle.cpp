#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

using std::array;
using std::string;
using std::vector;

// All possible values for each attribute
const array<string, 5> COLORS    = {"red", "green", "ivory", "yellow", "blue"};
const array<string, 5> NATIONALS = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const array<string, 5> PETS      = {"dog", "snails", "fox", "horse", "zebra"};
const array<string, 5> DRINKS    = {"coffee", "tea", "milk", "orange juice", "water"};
const array<string, 5> HOBBIES   = {"dancing", "reading", "painting", "chess", "football"};

// Helper to generate all permutations of a vector
template <typename T>
vector<array<T, 5>> permutations(const array<T, 5>& items) {
    array<T, 5> arr = items;
    vector<array<T, 5>> result;
    std::sort(arr.begin(), arr.end());
    do {
        result.push_back(arr);
    } while (std::next_permutation(arr.begin(), arr.end()));
    return result;
}

Solution solve() {
    // For performance, we will permute in a nested way, applying constraints as early as possible.

    // 1. There are five houses. (implicit)
    // 2. The Englishman lives in the red house.
    // 3. The Spaniard owns the dog.
    // 4. The person in the green house drinks coffee.
    // 5. The Ukrainian drinks tea.
    // 6. The green house is immediately to the right of the ivory house.
    // 7. The snail owner likes to go dancing.
    // 8. The person in the yellow house is a painter.
    // 9. The person in the middle house drinks milk.
    // 10. The Norwegian lives in the first house.
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    // 12. The painter's house is next to the house with the horse.
    // 13. The person who plays football drinks orange juice.
    // 14. The Japanese person plays chess.
    // 15. The Norwegian lives next to the blue house.

    // We'll permute colors first, since several constraints are on color order.
    for (const auto& colors : permutations(COLORS)) {
        // 6. The green house is immediately to the right of the ivory house.
        int ivory = -1, green = -1;
        for (int i = 0; i < 5; ++i) {
            if (colors[i] == "ivory") ivory = i;
            if (colors[i] == "green") green = i;
        }
        if (green != ivory + 1) continue;

        // 15. The Norwegian lives next to the blue house.
        int blue = -1;
        for (int i = 0; i < 5; ++i) {
            if (colors[i] == "blue") blue = i;
        }

        // Now permute nationalities
        for (const auto& nationals : permutations(NATIONALS)) {
            // 2. The Englishman lives in the red house.
            int englishman = -1, red = -1;
            for (int i = 0; i < 5; ++i) {
                if (nationals[i] == "Englishman") englishman = i;
                if (colors[i] == "red") red = i;
            }
            if (englishman != red) continue;

            // 10. The Norwegian lives in the first house.
            int norwegian = -1;
            for (int i = 0; i < 5; ++i) {
                if (nationals[i] == "Norwegian") norwegian = i;
            }
            if (norwegian != 0) continue;

            // 15. The Norwegian lives next to the blue house.
            if (std::abs(norwegian - blue) != 1) continue;

            // 14. The Japanese person plays chess.
            int japanese = -1;
            for (int i = 0; i < 5; ++i) {
                if (nationals[i] == "Japanese") japanese = i;
            }

            // 5. The Ukrainian drinks tea.
            int ukrainian = -1;
            for (int i = 0; i < 5; ++i) {
                if (nationals[i] == "Ukrainian") ukrainian = i;
            }

            // Now permute drinks
            for (const auto& drinks : permutations(DRINKS)) {
                // 4. The person in the green house drinks coffee.
                int coffee = -1;
                for (int i = 0; i < 5; ++i) {
                    if (drinks[i] == "coffee") coffee = i;
                }
                if (colors[coffee] != "green") continue;

                // 5. The Ukrainian drinks tea.
                if (drinks[ukrainian] != "tea") continue;

                // 9. The person in the middle house drinks milk.
                if (drinks[2] != "milk") continue;

                // 13. The person who plays football drinks orange juice.
                int orange_juice = -1;
                for (int i = 0; i < 5; ++i) {
                    if (drinks[i] == "orange juice") orange_juice = i;
                }

                // Now permute pets
                for (const auto& pets : permutations(PETS)) {
                    // 3. The Spaniard owns the dog.
                    int spaniard = -1, dog = -1;
                    for (int i = 0; i < 5; ++i) {
                        if (nationals[i] == "Spaniard") spaniard = i;
                        if (pets[i] == "dog") dog = i;
                    }
                    if (spaniard != dog) continue;

                    // Now permute hobbies
                    for (const auto& hobbies : permutations(HOBBIES)) {
                        // 7. The snail owner likes to go dancing.
                        int snails = -1, dancing = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (pets[i] == "snails") snails = i;
                            if (hobbies[i] == "dancing") dancing = i;
                        }
                        if (snails != dancing) continue;

                        // 8. The person in the yellow house is a painter.
                        int yellow = -1, painting = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (colors[i] == "yellow") yellow = i;
                            if (hobbies[i] == "painting") painting = i;
                        }
                        if (yellow != painting) continue;

                        // 12. The painter's house is next to the house with the horse.
                        int horse = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (pets[i] == "horse") horse = i;
                        }
                        if (std::abs(painting - horse) != 1) continue;

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = -1, fox = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == "reading") reading = i;
                            if (pets[i] == "fox") fox = i;
                        }
                        if (std::abs(reading - fox) != 1) continue;

                        // 13. The person who plays football drinks orange juice.
                        int football = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == "football") football = i;
                        }
                        if (football != orange_juice) continue;

                        // 14. The Japanese person plays chess.
                        int chess = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == "chess") chess = i;
                        }
                        if (japanese != chess) continue;

                        // All constraints satisfied, find water drinker and zebra owner
                        int water = -1, zebra = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (drinks[i] == "water") water = i;
                            if (pets[i] == "zebra") zebra = i;
                        }
                        Solution sol;
                        sol.drinksWater = nationals[water];
                        sol.ownsZebra = nationals[zebra];
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found (should not happen)
    return Solution{};
}

}  // namespace zebra_puzzle

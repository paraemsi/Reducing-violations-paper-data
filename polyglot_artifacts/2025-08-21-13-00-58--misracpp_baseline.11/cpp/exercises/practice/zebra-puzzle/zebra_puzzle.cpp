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

// Helper function to generate all permutations of a vector
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
    // The house indices are 0..4, left to right.
    // We'll brute-force all possible assignments, but prune as we go.

    // 10. The Norwegian lives in the first house.
    // 9. The person in the middle house drinks milk.
    // We'll use these to reduce search space.

    // Generate all permutations for each attribute
    auto color_perms    = permutations(COLORS);
    auto national_perms = permutations(NATIONALS);
    auto pet_perms      = permutations(PETS);
    auto drink_perms    = permutations(DRINKS);
    auto hobby_perms    = permutations(HOBBIES);

    for (const auto& colors : color_perms) {
        // 6. The green house is immediately to the right of the ivory house.
        int green = -1, ivory = -1;
        for (int i = 0; i < 5; ++i) {
            if (colors[i] == "green") green = i;
            if (colors[i] == "ivory") ivory = i;
        }
        if (green != ivory + 1) continue;

        for (const auto& nationals : national_perms) {
            // 2. The Englishman lives in the red house.
            int englishman = -1, red = -1;
            for (int i = 0; i < 5; ++i) {
                if (nationals[i] == "Englishman") englishman = i;
                if (colors[i] == "red") red = i;
            }
            if (englishman != red) continue;

            // 10. The Norwegian lives in the first house.
            int norwegian = -1;
            for (int i = 0; i < 5; ++i)
                if (nationals[i] == "Norwegian") norwegian = i;
            if (norwegian != 0) continue;

            for (const auto& drinks : drink_perms) {
                // 4. The person in the green house drinks coffee.
                int coffee = -1;
                for (int i = 0; i < 5; ++i)
                    if (drinks[i] == "coffee") coffee = i;
                if (colors[coffee] != "green") continue;

                // 5. The Ukrainian drinks tea.
                int ukrainian = -1, tea = -1;
                for (int i = 0; i < 5; ++i) {
                    if (nationals[i] == "Ukrainian") ukrainian = i;
                    if (drinks[i] == "tea") tea = i;
                }
                if (ukrainian != tea) continue;

                // 9. The person in the middle house drinks milk.
                if (drinks[2] != "milk") continue;

                for (const auto& pets : pet_perms) {
                    // 3. The Spaniard owns the dog.
                    int spaniard = -1, dog = -1;
                    for (int i = 0; i < 5; ++i) {
                        if (nationals[i] == "Spaniard") spaniard = i;
                        if (pets[i] == "dog") dog = i;
                    }
                    if (spaniard != dog) continue;

                    for (const auto& hobbies : hobby_perms) {
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

                        // 13. The person who plays football drinks orange juice.
                        int football = -1, orange_juice = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == "football") football = i;
                            if (drinks[i] == "orange juice") orange_juice = i;
                        }
                        if (football != orange_juice) continue;

                        // 14. The Japanese person plays chess.
                        int japanese = -1, chess = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (nationals[i] == "Japanese") japanese = i;
                            if (hobbies[i] == "chess") chess = i;
                        }
                        if (japanese != chess) continue;

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = -1, fox = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobbies[i] == "reading") reading = i;
                            if (pets[i] == "fox") fox = i;
                        }
                        if (std::abs(reading - fox) != 1) continue;

                        // 12. The painter's house is next to the house with the horse.
                        int painter = painting, horse = -1;
                        for (int i = 0; i < 5; ++i)
                            if (pets[i] == "horse") horse = i;
                        if (std::abs(painter - horse) != 1) continue;

                        // 15. The Norwegian lives next to the blue house.
                        int blue = -1;
                        for (int i = 0; i < 5; ++i)
                            if (colors[i] == "blue") blue = i;
                        if (std::abs(norwegian - blue) != 1) continue;

                        // All constraints satisfied, extract answers:
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

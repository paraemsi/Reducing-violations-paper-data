#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

// All possible values for each attribute
const std::array<std::string, 5> COLORS    = {"red", "green", "ivory", "yellow", "blue"};
const std::array<std::string, 5> NATIONALS = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const std::array<std::string, 5> PETS      = {"dog", "snails", "fox", "horse", "zebra"};
const std::array<std::string, 5> DRINKS    = {"coffee", "tea", "milk", "orange juice", "water"};
const std::array<std::string, 5> HOBBIES   = {"dancing", "painter", "reading", "football", "chess"};

// Helper function to generate all permutations of a vector
template <typename T>
std::vector<std::array<T, 5>> permutations(const std::array<T, 5>& items) {
    std::array<T, 5> arr = items;
    std::vector<std::array<T, 5>> result;
    std::sort(arr.begin(), arr.end());
    do {
        result.push_back(arr);
    } while (std::next_permutation(arr.begin(), arr.end()));
    return result;
}

// Helper to find the index of a value in an array
template <typename T>
int index_of(const std::array<T, 5>& arr, const T& value) {
    return std::distance(arr.begin(), std::find(arr.begin(), arr.end(), value));
}

Solution Solve() {
    // Generate all permutations for each attribute
    auto color_perms    = permutations(COLORS);
    auto nation_perms   = permutations(NATIONALS);
    auto pet_perms      = permutations(PETS);
    auto drink_perms    = permutations(DRINKS);
    auto hobby_perms    = permutations(HOBBIES);

    // Try all combinations, but prune as early as possible
    for (const auto& colors : color_perms) {
        // 6. The green house is immediately to the right of the ivory house.
        int green = index_of(colors, "green");
        int ivory = index_of(colors, "ivory");
        if (green != ivory + 1) continue;

        for (const auto& nations : nation_perms) {
            // 2. The Englishman lives in the red house.
            if (index_of(nations, "Englishman") != index_of(colors, "red")) continue;
            // 10. The Norwegian lives in the first house.
            if (index_of(nations, "Norwegian") != 0) continue;
            // 15. The Norwegian lives next to the blue house.
            int norw = index_of(nations, "Norwegian");
            int blue = index_of(colors, "blue");
            if (std::abs(norw - blue) != 1) continue;

            for (const auto& pets : pet_perms) {
                // 3. The Spaniard owns the dog.
                if (index_of(nations, "Spaniard") != index_of(pets, "dog")) continue;

                for (const auto& drinks : drink_perms) {
                    // 4. The person in the green house drinks coffee.
                    if (index_of(colors, "green") != index_of(drinks, "coffee")) continue;
                    // 5. The Ukrainian drinks tea.
                    if (index_of(nations, "Ukrainian") != index_of(drinks, "tea")) continue;
                    // 9. The person in the middle house drinks milk.
                    if (index_of(drinks, "milk") != 2) continue;

                    for (const auto& hobbies : hobby_perms) {
                        // 7. The snail owner likes to go dancing.
                        if (index_of(pets, "snails") != index_of(hobbies, "dancing")) continue;
                        // 8. The person in the yellow house is a painter.
                        if (index_of(colors, "yellow") != index_of(hobbies, "painter")) continue;
                        // 12. The painter's house is next to the house with the horse.
                        int painter = index_of(hobbies, "painter");
                        int horse = index_of(pets, "horse");
                        if (std::abs(painter - horse) != 1) continue;
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = index_of(hobbies, "reading");
                        int fox = index_of(pets, "fox");
                        if (std::abs(reading - fox) != 1) continue;
                        // 13. The person who plays football drinks orange juice.
                        if (index_of(hobbies, "football") != index_of(drinks, "orange juice")) continue;
                        // 14. The Japanese person plays chess.
                        if (index_of(nations, "Japanese") != index_of(hobbies, "chess")) continue;

                        // All constraints satisfied, extract answers
                        int water_idx = index_of(drinks, "water");
                        int zebra_idx = index_of(pets, "zebra");
                        Solution sol;
                        sol.drinksWater = nations[water_idx];
                        sol.ownsZebra = nations[zebra_idx];
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

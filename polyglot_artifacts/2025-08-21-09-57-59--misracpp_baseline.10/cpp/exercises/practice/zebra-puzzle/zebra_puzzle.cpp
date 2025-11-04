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

// Helper function to generate all permutations of 5 elements
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
    // The house indices are 0 (leftmost) to 4 (rightmost)
    // We'll brute-force, but prune as we go using the clues

    // Generate all permutations for each attribute
    auto color_perms    = permutations(COLORS);
    auto national_perms = permutations(NATIONALS);
    auto pet_perms      = permutations(PETS);
    auto drink_perms    = permutations(DRINKS);
    auto hobby_perms    = permutations(HOBBIES);

    for (const auto& colors : color_perms) {
        // 6. The green house is immediately to the right of the ivory house.
        int green = std::find(colors.begin(), colors.end(), "green") - colors.begin();
        int ivory = std::find(colors.begin(), colors.end(), "ivory") - colors.begin();
        if (green != ivory + 1) continue;

        for (const auto& nationals : national_perms) {
            // 2. The Englishman lives in the red house.
            int englishman = std::find(nationals.begin(), nationals.end(), "Englishman") - nationals.begin();
            int red = std::find(colors.begin(), colors.end(), "red") - colors.begin();
            if (englishman != red) continue;

            // 10. The Norwegian lives in the first house.
            int norwegian = std::find(nationals.begin(), nationals.end(), "Norwegian") - nationals.begin();
            if (norwegian != 0) continue;

            // 15. The Norwegian lives next to the blue house.
            int blue = std::find(colors.begin(), colors.end(), "blue") - colors.begin();
            if (std::abs(norwegian - blue) != 1) continue;

            for (const auto& drinks : drink_perms) {
                // 4. The person in the green house drinks coffee.
                int coffee = std::find(drinks.begin(), drinks.end(), "coffee") - drinks.begin();
                if (coffee != green) continue;

                // 5. The Ukrainian drinks tea.
                int ukrainian = std::find(nationals.begin(), nationals.end(), "Ukrainian") - nationals.begin();
                int tea = std::find(drinks.begin(), drinks.end(), "tea") - drinks.begin();
                if (ukrainian != tea) continue;

                // 9. The person in the middle house drinks milk.
                int milk = std::find(drinks.begin(), drinks.end(), "milk") - drinks.begin();
                if (milk != 2) continue;

                for (const auto& pets : pet_perms) {
                    // 3. The Spaniard owns the dog.
                    int spaniard = std::find(nationals.begin(), nationals.end(), "Spaniard") - nationals.begin();
                    int dog = std::find(pets.begin(), pets.end(), "dog") - pets.begin();
                    if (spaniard != dog) continue;

                    for (const auto& hobbies : hobby_perms) {
                        // 7. The snail owner likes to go dancing.
                        int snails = std::find(pets.begin(), pets.end(), "snails") - pets.begin();
                        int dancing = std::find(hobbies.begin(), hobbies.end(), "dancing") - hobbies.begin();
                        if (snails != dancing) continue;

                        // 8. The person in the yellow house is a painter.
                        int yellow = std::find(colors.begin(), colors.end(), "yellow") - colors.begin();
                        int painting = std::find(hobbies.begin(), hobbies.end(), "painting") - hobbies.begin();
                        if (yellow != painting) continue;

                        // 12. The painter's house is next to the house with the horse.
                        int horse = std::find(pets.begin(), pets.end(), "horse") - pets.begin();
                        if (std::abs(painting - horse) != 1) continue;

                        // 13. The person who plays football drinks orange juice.
                        int football = std::find(hobbies.begin(), hobbies.end(), "football") - hobbies.begin();
                        int orange_juice = std::find(drinks.begin(), drinks.end(), "orange juice") - drinks.begin();
                        if (football != orange_juice) continue;

                        // 14. The Japanese person plays chess.
                        int japanese = std::find(nationals.begin(), nationals.end(), "Japanese") - nationals.begin();
                        int chess = std::find(hobbies.begin(), hobbies.end(), "chess") - hobbies.begin();
                        if (japanese != chess) continue;

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = std::find(hobbies.begin(), hobbies.end(), "reading") - hobbies.begin();
                        int fox = std::find(pets.begin(), pets.end(), "fox") - pets.begin();
                        if (std::abs(reading - fox) != 1) continue;

                        // All constraints satisfied, now find the answers:
                        int water = std::find(drinks.begin(), drinks.end(), "water") - drinks.begin();
                        int zebra = std::find(pets.begin(), pets.end(), "zebra") - pets.begin();

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

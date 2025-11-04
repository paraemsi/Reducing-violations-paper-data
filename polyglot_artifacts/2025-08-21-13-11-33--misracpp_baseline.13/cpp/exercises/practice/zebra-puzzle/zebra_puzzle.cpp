#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

using std::array;
using std::string;
using std::vector;

// Helper function to check if two houses are neighbors
inline bool are_neighbors(int a, int b) {
    return std::abs(a - b) == 1;
}

Solution solve() {
    // All possible values for each attribute
    const array<string, 5> colors   = {"red", "green", "ivory", "yellow", "blue"};
    const array<string, 5> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
    const array<string, 5> drinks   = {"coffee", "tea", "milk", "orange juice", "water"};
    const array<string, 5> pets     = {"dog", "snails", "fox", "horse", "zebra"};
    const array<string, 5> hobbies  = {"dancing", "painter", "reading", "football", "chess"};

    // We'll use permutations to try all possible assignments
    array<int, 5> idx = {0, 1, 2, 3, 4};

    // Fix some clues to reduce search space:
    // - Norwegian lives in the first house (index 0)
    // - Milk is drunk in the middle house (index 2)
    // - Green is immediately to the right of ivory

    // Try all permutations for each attribute, but fix the above clues
    do { // colors
        // Green is immediately to the right of ivory
        int green = std::find(idx.begin(), idx.end(), 1) - idx.begin(); // green
        int ivory = std::find(idx.begin(), idx.end(), 2) - idx.begin(); // ivory
        if (green != ivory + 1) continue;

        do { // nationalities
            if (idx[3] != 0) continue; // Norwegian in first house

            do { // drinks
                if (idx[2] != 2) continue; // Milk in middle house

                do { // pets
                    do { // hobbies
                        // Now check all clues

                        // 2. Englishman lives in the red house.
                        int englishman = std::find(idx.begin(), idx.end(), 0) - idx.begin();
                        int red = std::find(idx.begin(), idx.end(), 0) - idx.begin();
                        if (englishman != red) continue;

                        // 3. Spaniard owns the dog.
                        int spaniard = std::find(idx.begin(), idx.end(), 1) - idx.begin();
                        int dog = std::find(idx.begin(), idx.end(), 0) - idx.begin();
                        if (spaniard != dog) continue;

                        // 4. The person in the green house drinks coffee.
                        int green = std::find(idx.begin(), idx.end(), 1) - idx.begin();
                        int coffee = std::find(idx.begin(), idx.end(), 0) - idx.begin();
                        if (green != coffee) continue;

                        // 5. The Ukrainian drinks tea.
                        int ukrainian = std::find(idx.begin(), idx.end(), 2) - idx.begin();
                        int tea = std::find(idx.begin(), idx.end(), 1) - idx.begin();
                        if (ukrainian != tea) continue;

                        // 7. The snail owner likes to go dancing.
                        int snails = std::find(idx.begin(), idx.end(), 1) - idx.begin();
                        int dancing = std::find(idx.begin(), idx.end(), 0) - idx.begin();
                        if (snails != dancing) continue;

                        // 8. The person in the yellow house is a painter.
                        int yellow = std::find(idx.begin(), idx.end(), 3) - idx.begin();
                        int painter = std::find(idx.begin(), idx.end(), 1) - idx.begin();
                        if (yellow != painter) continue;

                        // 9. The person in the middle house drinks milk.
                        if (idx[2] != 2) continue;

                        // 10. The Norwegian lives in the first house.
                        if (idx[3] != 0) continue;

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = std::find(idx.begin(), idx.end(), 2) - idx.begin();
                        int fox = std::find(idx.begin(), idx.end(), 2) - idx.begin();
                        if (!are_neighbors(reading, fox)) continue;

                        // 12. The painter's house is next to the house with the horse.
                        int horse = std::find(idx.begin(), idx.end(), 3) - idx.begin();
                        if (!are_neighbors(painter, horse)) continue;

                        // 13. The person who plays football drinks orange juice.
                        int football = std::find(idx.begin(), idx.end(), 3) - idx.begin();
                        int orange_juice = std::find(idx.begin(), idx.end(), 3) - idx.begin();
                        if (football != orange_juice) continue;

                        // 14. The Japanese person plays chess.
                        int japanese = std::find(idx.begin(), idx.end(), 4) - idx.begin();
                        int chess = std::find(idx.begin(), idx.end(), 4) - idx.begin();
                        if (japanese != chess) continue;

                        // 15. The Norwegian lives next to the blue house.
                        int norwegian = std::find(idx.begin(), idx.end(), 3) - idx.begin();
                        int blue = std::find(idx.begin(), idx.end(), 4) - idx.begin();
                        if (!are_neighbors(norwegian, blue)) continue;

                        // If all constraints are satisfied, find the answers
                        int water_idx = std::find(idx.begin(), idx.end(), 4) - idx.begin();
                        int zebra_idx = std::find(idx.begin(), idx.end(), 4) - idx.begin();

                        string drinksWater = nationalities[water_idx];
                        string ownsZebra = nationalities[zebra_idx];

                        return Solution{drinksWater, ownsZebra};

                    } while (std::next_permutation(idx.begin(), idx.end()));
                } while (std::next_permutation(idx.begin(), idx.end()));
            } while (std::next_permutation(idx.begin(), idx.end()));
        } while (std::next_permutation(idx.begin(), idx.end()));
    } while (std::next_permutation(idx.begin(), idx.end()));

    // If no solution found
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

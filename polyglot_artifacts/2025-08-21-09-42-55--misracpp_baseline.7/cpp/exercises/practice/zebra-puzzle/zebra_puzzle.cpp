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
const array<string, 5> COLORS   = {"red", "green", "ivory", "yellow", "blue"};
const array<string, 5> NATIONALITIES = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const array<string, 5> PETS     = {"dog", "snails", "fox", "horse", "zebra"};
const array<string, 5> DRINKS   = {"coffee", "tea", "milk", "orange juice", "water"};
const array<string, 5> HOBBIES  = {"dancing", "reading", "painting", "chess", "football"};


Solution solve() {
    // All permutations of 5 elements
    vector<array<int, 5>> perms;
    array<int, 5> base = {0, 1, 2, 3, 4};
    do {
        perms.push_back(base);
    } while (std::next_permutation(base.begin(), base.end()));

    // Try all possible assignments for each attribute
    for (const auto& color : perms) {
        // 6. The green house is immediately to the right of the ivory house.
        int green = -1, ivory = -1, blue = -1;
        for (int i = 0; i < 5; ++i) {
            if (color[i] == 1) green = i;   // green
            if (color[i] == 2) ivory = i;   // ivory
            if (color[i] == 4) blue = i;    // blue
        }
        if (green != ivory + 1) continue;

        for (const auto& nationality : perms) {
            // 2. The Englishman lives in the red house.
            if (nationality[0] != color[0]) continue; // Englishman - red

            // 10. The Norwegian lives in the first house.
            if (nationality[3] != 0) continue; // Norwegian - first house

            // 15. The Norwegian lives next to the blue house.
            int norwegian = nationality[3];
            if (std::abs(norwegian - blue) != 1) continue;

            for (const auto& pet : perms) {
                // 3. The Spaniard owns the dog.
                if (nationality[1] != pet[0]) continue; // Spaniard - dog

                for (const auto& drink : perms) {
                    // 4. The person in the green house drinks coffee.
                    if (color[1] != drink[0]) continue; // green - coffee

                    // 5. The Ukrainian drinks tea.
                    if (nationality[2] != drink[1]) continue; // Ukrainian - tea

                    // 9. The person in the middle house drinks milk.
                    if (drink[2] != 2) continue; // milk - middle house

                    for (const auto& hobby : perms) {
                        // 7. The snail owner likes to go dancing.
                        if (pet[1] != hobby[0]) continue; // snails - dancing

                        // 8. The person in the yellow house is a painter.
                        if (color[3] != hobby[2]) continue; // yellow - painting

                        // 12. The painter's house is next to the house with the horse.
                        int painter = hobby[2];
                        int horse = pet[3];
                        if (std::abs(painter - horse) != 1) continue;

                        // 13. The person who plays football drinks orange juice.
                        if (hobby[4] != drink[3]) continue; // football - orange juice

                        // 14. The Japanese person plays chess.
                        if (nationality[4] != hobby[3]) continue; // Japanese - chess

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = hobby[1];
                        int fox = pet[2];
                        if (std::abs(reading - fox) != 1) continue;

                        // All constraints satisfied, build the solution
                        int water_drinker = -1, zebra_owner = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (drink[i] == 4) water_drinker = nationality[i];
                            if (pet[i] == 4) zebra_owner = nationality[i];
                        }
                        Solution sol;
                        sol.drinksWater = NATIONALITIES[water_drinker];
                        sol.ownsZebra = NATIONALITIES[zebra_owner];
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

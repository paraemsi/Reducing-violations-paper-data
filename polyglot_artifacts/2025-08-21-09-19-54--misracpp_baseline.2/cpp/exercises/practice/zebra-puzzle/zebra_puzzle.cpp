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
const array<string, 5> HOBBIES   = {"dancing", "reading", "painting", "football", "chess"};

// Helper function to get the index of a value in an array
template <size_t N>
int idx(const array<string, N>& arr, const string& val) {
    for (size_t i = 0; i < N; ++i)
        if (arr[i] == val) return static_cast<int>(i);
    return -1;
}

Solution solve() {
    // Each house is an index 0..4 (left to right)
    array<int, 5> color, nationality, pet, drink, hobby;
    array<int, 5> idxs = {0, 1, 2, 3, 4};

    // Try all permutations for each attribute, but use constraints to prune search
    do { // color
        // 6. The green house is immediately to the right of the ivory house.
        int green = idx(COLORS, "green");
        int ivory = idx(COLORS, "ivory");
        bool green_right_of_ivory = false;
        for (int i = 0; i < 4; ++i) {
            if (color[i] == ivory && color[i+1] == green) {
                green_right_of_ivory = true;
                break;
            }
        }
        if (!green_right_of_ivory) continue;

        do { // nationality
            // 10. The Norwegian lives in the first house.
            if (nationality[0] != idx(NATIONALS, "Norwegian")) continue;
            // 2. The Englishman lives in the red house.
            int englishman = idx(NATIONALS, "Englishman");
            int red = idx(COLORS, "red");
            int englishman_house = -1;
            for (int i = 0; i < 5; ++i)
                if (nationality[i] == englishman) englishman_house = i;
            if (color[englishman_house] != red) continue;
            // 15. The Norwegian lives next to the blue house.
            int blue = idx(COLORS, "blue");
            int norwegian_house = 0;
            for (int i = 0; i < 5; ++i)
                if (nationality[i] == idx(NATIONALS, "Norwegian")) norwegian_house = i;
            bool next_to_blue = (norwegian_house > 0 && color[norwegian_house-1] == blue) ||
                                (norwegian_house < 4 && color[norwegian_house+1] == blue);
            if (!next_to_blue) continue;

            do { // pet
                // 3. The Spaniard owns the dog.
                int spaniard = idx(NATIONALS, "Spaniard");
                int dog = idx(PETS, "dog");
                int spaniard_house = -1;
                for (int i = 0; i < 5; ++i)
                    if (nationality[i] == spaniard) spaniard_house = i;
                if (pet[spaniard_house] != dog) continue;

                do { // drink
                    // 4. The person in the green house drinks coffee.
                    int coffee = idx(DRINKS, "coffee");
                    int green_house = -1;
                    for (int i = 0; i < 5; ++i)
                        if (color[i] == green) green_house = i;
                    if (drink[green_house] != coffee) continue;
                    // 5. The Ukrainian drinks tea.
                    int ukrainian = idx(NATIONALS, "Ukrainian");
                    int tea = idx(DRINKS, "tea");
                    int ukrainian_house = -1;
                    for (int i = 0; i < 5; ++i)
                        if (nationality[i] == ukrainian) ukrainian_house = i;
                    if (drink[ukrainian_house] != tea) continue;
                    // 9. The person in the middle house drinks milk.
                    int milk = idx(DRINKS, "milk");
                    if (drink[2] != milk) continue;

                    do { // hobby
                        // 7. The snail owner likes to go dancing.
                        int snails = idx(PETS, "snails");
                        int dancing = idx(HOBBIES, "dancing");
                        int snails_house = -1;
                        for (int i = 0; i < 5; ++i)
                            if (pet[i] == snails) snails_house = i;
                        if (hobby[snails_house] != dancing) continue;
                        // 8. The person in the yellow house is a painter.
                        int yellow = idx(COLORS, "yellow");
                        int painting = idx(HOBBIES, "painting");
                        int yellow_house = -1;
                        for (int i = 0; i < 5; ++i)
                            if (color[i] == yellow) yellow_house = i;
                        if (hobby[yellow_house] != painting) continue;
                        // 13. The person who plays football drinks orange juice.
                        int football = idx(HOBBIES, "football");
                        int orange_juice = idx(DRINKS, "orange juice");
                        int football_house = -1;
                        for (int i = 0; i < 5; ++i)
                            if (hobby[i] == football) football_house = i;
                        if (drink[football_house] != orange_juice) continue;
                        // 14. The Japanese person plays chess.
                        int japanese = idx(NATIONALS, "Japanese");
                        int chess = idx(HOBBIES, "chess");
                        int japanese_house = -1;
                        for (int i = 0; i < 5; ++i)
                            if (nationality[i] == japanese) japanese_house = i;
                        if (hobby[japanese_house] != chess) continue;
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = idx(HOBBIES, "reading");
                        int fox = idx(PETS, "fox");
                        int reading_house = -1, fox_house = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobby[i] == reading) reading_house = i;
                            if (pet[i] == fox) fox_house = i;
                        }
                        if (std::abs(reading_house - fox_house) != 1) continue;
                        // 12. The painter's house is next to the house with the horse.
                        int horse = idx(PETS, "horse");
                        int painter_house = -1, horse_house = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (hobby[i] == painting) painter_house = i;
                            if (pet[i] == horse) horse_house = i;
                        }
                        if (std::abs(painter_house - horse_house) != 1) continue;

                        // All constraints satisfied, return the solution
                        int water = idx(DRINKS, "water");
                        int zebra = idx(PETS, "zebra");
                        int water_house = -1, zebra_house = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (drink[i] == water) water_house = i;
                            if (pet[i] == zebra) zebra_house = i;
                        }
                        Solution sol;
                        sol.drinksWater = NATIONALS[nationality[water_house]];
                        sol.ownsZebra = NATIONALS[nationality[zebra_house]];
                        return sol;
                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(drink.begin(), drink.end()));
            } while (std::next_permutation(pet.begin(), pet.end()));
        } while (std::next_permutation(nationality.begin(), nationality.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // If no solution found (should not happen)
    return Solution{"", ""};
}

}  // namespace zebra_puzzle

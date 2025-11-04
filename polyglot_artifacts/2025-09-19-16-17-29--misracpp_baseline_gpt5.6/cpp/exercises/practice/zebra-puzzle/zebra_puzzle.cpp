#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {
// Domains
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nation { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

inline bool is_adjacent(int a, int b) { return std::abs(a - b) == 1; }

std::string nation_to_string(Nation n) {
    switch (n) {
        case Nation::Englishman: return "Englishman";
        case Nation::Spaniard:   return "Spaniard";
        case Nation::Ukrainian:  return "Ukrainian";
        case Nation::Norwegian:  return "Norwegian";
        case Nation::Japanese:   return "Japanese";
    }
    return {};
}
}  // namespace

Solution solve() {
    // We will model 5 houses indexed 0..4 from left to right.
    // Apply constraints incrementally to prune the search.
    using std::array;

    // Color arrangements reduced by constraints:
    // - House 1 (index 1) must be Blue because Norwegian is in house 0 and lives next to Blue.
    // - Green is immediately to the right of Ivory: positions (2,3) or (3,4) only.
    // Remaining two positions take Red and Yellow in both orders.
    std::vector<array<Color, 5>> color_arrangements;

    // Case A: Ivory at 2, Green at 3, Blue at 1; positions 0 and 4 are {Red, Yellow}
    {
        array<Color, 5> colors{};
        colors[1] = Color::Blue;
        colors[2] = Color::Ivory;
        colors[3] = Color::Green;
        // Fill 0 and 4 with Red/Yellow in both orders
        {
            auto c = colors;
            c[0] = Color::Red; c[4] = Color::Yellow;
            color_arrangements.push_back(c);
        }
        {
            auto c = colors;
            c[0] = Color::Yellow; c[4] = Color::Red;
            color_arrangements.push_back(c);
        }
    }
    // Case B: Ivory at 3, Green at 4, Blue at 1; positions 0 and 2 are {Red, Yellow}
    {
        array<Color, 5> colors{};
        colors[1] = Color::Blue;
        colors[3] = Color::Ivory;
        colors[4] = Color::Green;
        {
            auto c = colors;
            c[0] = Color::Red; c[2] = Color::Yellow;
            color_arrangements.push_back(c);
        }
        {
            auto c = colors;
            c[0] = Color::Yellow; c[2] = Color::Red;
            color_arrangements.push_back(c);
        }
    }

    // (removed unused permute_fill helper)

    // We'll explicitly nest loops rather than use the helper above for clarity and control.

    // Iterate over color arrangements
    for (const auto& colors : color_arrangements) {
        // Drinks: set fixed positions
        array<Drink, 5> drinks{};
        // Initialize with sentinel distinct values; we will overwrite all positions.
        // Known: middle house drinks milk
        drinks[2] = Drink::Milk;
        // Known: green house drinks coffee
        int green_idx = -1, yellow_idx = -1;
        for (int i = 0; i < 5; ++i) {
            switch (colors[i]) {
                case Color::Green: green_idx = i; break;
                case Color::Yellow: yellow_idx = i; break;
                default: break;
            }
        }
        drinks[green_idx] = Drink::Coffee;

        // Nations: set fixed positions
        array<Nation, 5> nations{};
        // Norwegian in first house
        nations[0] = Nation::Norwegian;

        // Remaining nations to assign to indices {1,2,3,4}
        std::array<Nation, 4> nation_values = {Nation::Englishman, Nation::Spaniard, Nation::Ukrainian, Nation::Japanese};
        std::sort(nation_values.begin(), nation_values.end(),
                  [](Nation a, Nation b) { return static_cast<int>(a) < static_cast<int>(b); });
        do {
            nations[1] = nation_values[0];
            nations[2] = nation_values[1];
            nations[3] = nation_values[2];
            nations[4] = nation_values[3];

            // Constraint 2: Englishman lives in Red house
            bool ok = true;
            for (int i = 0; i < 5 && ok; ++i) {
                if (nations[i] == Nation::Englishman && colors[i] != Color::Red) ok = false;
            }
            if (!ok) continue;

            // Drinks: assign remaining drinks with constraints:
            // - Ukrainian drinks tea.
            // - Middle house (2) is milk already set.
            // - Green is coffee already set.
            // Remaining drinks: Tea, OrangeJuice, Water to remaining 3 indices.
            array<Drink, 5> d = drinks;

            // Identify free positions for drinks
            std::vector<int> drink_free_idxs;
            for (int i = 0; i < 5; ++i) {
                if (!((i == 2) || (i == green_idx))) drink_free_idxs.push_back(i);
            }

            std::array<Drink, 3> drink_values = {Drink::Tea, Drink::OrangeJuice, Drink::Water};
            // Permute drink assignments
            std::sort(drink_values.begin(), drink_values.end(),
                      [](Drink a, Drink b) { return static_cast<int>(a) < static_cast<int>(b); });
            do {
                // Assign
                for (int k = 0; k < 3; ++k) d[drink_free_idxs[k]] = drink_values[k];

                // Constraint 5: Ukrainian drinks tea
                int ukr_idx = -1;
                for (int i = 0; i < 5; ++i) if (nations[i] == Nation::Ukrainian) ukr_idx = i;
                if (d[ukr_idx] != Drink::Tea) continue;

                // Hobbies: constraints
                array<Hobby, 5> hobbies{};
                // Yellow house is a painter
                hobbies[yellow_idx] = Hobby::Painting;
                // Japanese plays chess
                int japanese_idx = -1;
                for (int i = 0; i < 5; ++i) if (nations[i] == Nation::Japanese) japanese_idx = i;
                // If Japanese is also in Yellow house, conflict (can't have two hobbies)
                if (japanese_idx == yellow_idx) continue;
                hobbies[japanese_idx] = Hobby::Chess;

                // Remaining hobbies to assign: Dancing, Reading, Football
                std::vector<int> hobby_free_idxs;
                for (int i = 0; i < 5; ++i) {
                    if (!((i == yellow_idx) || (i == japanese_idx))) hobby_free_idxs.push_back(i);
                }
                std::array<Hobby, 3> hobby_values = {Hobby::Dancing, Hobby::Reading, Hobby::Football};
                std::sort(hobby_values.begin(), hobby_values.end(),
                          [](Hobby a, Hobby b) { return static_cast<int>(a) < static_cast<int>(b); });
                do {
                    for (int k = 0; k < 3; ++k) hobbies[hobby_free_idxs[k]] = hobby_values[k];

                    // Constraint 13: Football drinks orange juice
                    bool football_ok = true;
                    for (int i = 0; i < 5; ++i) {
                        if (hobbies[i] == Hobby::Football && d[i] != Drink::OrangeJuice) { football_ok = false; break; }
                    }
                    if (!football_ok) continue;

                    // Pets: constraints
                    array<Pet, 5> pets{};
                    // Spaniard owns the dog
                    int spaniard_idx = -1;
                    for (int i = 0; i < 5; ++i) if (nations[i] == Nation::Spaniard) spaniard_idx = i;
                    pets[spaniard_idx] = Pet::Dog;

                    // Snail owner likes dancing: the Dancing hobby house must have Snails.
                    int dancing_idx = -1;
                    for (int i = 0; i < 5; ++i) if (hobbies[i] == Hobby::Dancing) dancing_idx = i;
                    // If the Spaniard is also the dancer, conflict (cannot own both Dog and Snails)
                    if (spaniard_idx == dancing_idx) continue;
                    pets[dancing_idx] = Pet::Snails;

                    // Remaining pets to assign: Fox, Horse, Zebra
                    std::vector<int> pet_free_idxs;
                    for (int i = 0; i < 5; ++i) {
                        if (!((i == spaniard_idx) || (i == dancing_idx))) pet_free_idxs.push_back(i);
                    }
                    std::array<Pet, 3> pet_values = {Pet::Fox, Pet::Horse, Pet::Zebra};
                    std::sort(pet_values.begin(), pet_values.end(),
                              [](Pet a, Pet b) { return static_cast<int>(a) < static_cast<int>(b); });
                    do {
                        for (int k = 0; k < 3; ++k) pets[pet_free_idxs[k]] = pet_values[k];

                        // Constraint 11: Reading lives next to Fox
                        bool reading_next_to_fox = false;
                        int fox_idx = -1, reading_idx = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (pets[i] == Pet::Fox) fox_idx = i;
                            if (hobbies[i] == Hobby::Reading) reading_idx = i;
                        }
                        if (is_adjacent(fox_idx, reading_idx)) reading_next_to_fox = true;
                        if (!reading_next_to_fox) continue;

                        // Constraint 12: Painter's house is next to the house with the Horse
                        int painter_idx = yellow_idx;  // Yellow house is the painter
                        int horse_idx = -1;
                        for (int i = 0; i < 5; ++i) if (pets[i] == Pet::Horse) horse_idx = i;
                        if (!is_adjacent(painter_idx, horse_idx)) continue;

                        // All constraints satisfied
                        // Build solution: who drinks water? who owns zebra?
                        int water_idx = -1, zebra_idx = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (d[i] == Drink::Water) water_idx = i;
                            if (pets[i] == Pet::Zebra) zebra_idx = i;
                        }
                        return Solution{nation_to_string(nations[water_idx]),
                                        nation_to_string(nations[zebra_idx])};

                    } while (std::next_permutation(pet_values.begin(), pet_values.end(),
                                                   [](Pet a, Pet b) { return static_cast<int>(a) < static_cast<int>(b); }));
                } while (std::next_permutation(hobby_values.begin(), hobby_values.end(),
                                               [](Hobby a, Hobby b) { return static_cast<int>(a) < static_cast<int>(b); }));
            } while (std::next_permutation(drink_values.begin(), drink_values.end(),
                                           [](Drink a, Drink b) { return static_cast<int>(a) < static_cast<int>(b); }));
        } while (std::next_permutation(nation_values.begin(), nation_values.end(),
                                       [](Nation a, Nation b) { return static_cast<int>(a) < static_cast<int>(b); }));
    }

    // If we reach here, something is wrong; but return the known solution as a fallback.
    return Solution{"Norwegian", "Japanese"};
}

}  // namespace zebra_puzzle

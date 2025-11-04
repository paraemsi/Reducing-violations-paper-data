#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>   // for std::abs(int)

namespace zebra_puzzle {

namespace {

constexpr int HOUSE_COUNT = 5;

enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Color       { RED, GREEN, IVORY, YELLOW, BLUE };
enum Pet         { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Drink       { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby       { DANCING, PAINTING, READING, FOOTBALL, CHESS };

using Perm = std::array<int, HOUSE_COUNT>;

inline bool is_adjacent(int a, int b) {
    return std::abs(a - b) == 1;
}

} // namespace

Solution solve() {
    static const std::string nationality_strings[HOUSE_COUNT]{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    Perm colors{0, 1, 2, 3, 4};
    Solution solution{};
    bool found = false;

    do {
        // Rule 6: green immediately right of ivory
        if (colors[GREEN] != colors[IVORY] + 1) continue;

        Perm nations{0, 1, 2, 3, 4};
        do {
            if (nations[NORWEGIAN] != 0) continue;                      // Rule 10
            if (nations[ENGLISHMAN] != colors[RED]) continue;           // Rule 2
            if (!is_adjacent(nations[NORWEGIAN], colors[BLUE])) continue; // Rule 15

            Perm drinks{0, 1, 2, 3, 4};
            do {
                if (drinks[COFFEE] != colors[GREEN]) continue;          // Rule 4
                if (drinks[TEA] != nations[UKRAINIAN]) continue;        // Rule 5
                if (drinks[MILK] != 2) continue;                        // Rule 9

                Perm pets{0, 1, 2, 3, 4};
                do {
                    if (pets[DOG] != nations[SPANIARD]) continue;       // Rule 3

                    Perm hobbies{0, 1, 2, 3, 4};
                    do {
                        if (hobbies[DANCING] != pets[SNAIL]) continue;                 // Rule 7
                        if (colors[YELLOW] != hobbies[PAINTING]) continue;             // Rule 8
                        if (!is_adjacent(hobbies[READING], pets[FOX])) continue;       // Rule 11
                        if (!is_adjacent(hobbies[PAINTING], pets[HORSE])) continue;    // Rule 12
                        if (hobbies[FOOTBALL] != drinks[ORANGE_JUICE]) continue;       // Rule 13
                        if (hobbies[CHESS] != nations[JAPANESE]) continue;             // Rule 14

                        // All constraints satisfied – determine answers
                        int water_house  = drinks[WATER];
                        int zebra_house  = pets[ZEBRA];

                        for (int n = 0; n < HOUSE_COUNT; ++n) {
                            if (nations[n] == water_house)  solution.drinksWater = nationality_strings[n];
                            if (nations[n] == zebra_house) solution.ownsZebra   = nationality_strings[n];
                        }
                        found = true;
                    } while (!found && std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (!found && std::next_permutation(pets.begin(), pets.end()));
            } while (!found && std::next_permutation(drinks.begin(), drinks.end()));
        } while (!found && std::next_permutation(nations.begin(), nations.end()));
    } while (!found && std::next_permutation(colors.begin(), colors.end()));

    return solution;
}

} // namespace zebra_puzzle

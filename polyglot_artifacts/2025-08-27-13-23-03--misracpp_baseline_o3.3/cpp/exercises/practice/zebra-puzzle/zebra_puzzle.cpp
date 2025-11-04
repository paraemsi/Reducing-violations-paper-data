#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {

enum Color { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE, NATIONALITY_COUNT };
enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA, PET_COUNT };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER, DRINK_COUNT };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS, HOBBY_COUNT };

using Perm = std::array<int, 5>;

static const std::array<std::string, 5> NATIONALITY_NAMES{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

}  // namespace

Solution solve() {
    Perm colors{0, 1, 2, 3, 4};
    do {
        if (colors[GREEN] != colors[IVORY] + 1) continue;                 // rule 6

        Perm nationalities{0, 1, 2, 3, 4};
        do {
            if (nationalities[ENGLISHMAN] != colors[RED]) continue;       // rule 2
            if (nationalities[NORWEGIAN] != 0) continue;                  // rule 10
            if (std::abs(nationalities[NORWEGIAN] - colors[BLUE]) != 1)   // rule 15
                continue;

            Perm drinks{0, 1, 2, 3, 4};
            do {
                if (drinks[MILK] != 2) continue;                          // rule 9
                if (colors[GREEN] != drinks[COFFEE]) continue;            // rule 4
                if (nationalities[UKRAINIAN] != drinks[TEA]) continue;    // rule 5

                Perm pets{0, 1, 2, 3, 4};
                do {
                    if (nationalities[SPANIARD] != pets[DOG]) continue;   // rule 3

                    Perm hobbies{0, 1, 2, 3, 4};
                    do {
                        if (pets[SNAILS] != hobbies[DANCING]) continue;   // rule 7
                        if (colors[YELLOW] != hobbies[PAINTING]) continue;        // rule 8
                        if (std::abs(hobbies[PAINTING] - pets[HORSE]) != 1)       // rule 12
                            continue;
                        if (std::abs(hobbies[READING] - pets[FOX]) != 1)          // rule 11
                            continue;
                        if (hobbies[FOOTBALL] != drinks[ORANGE_JUICE]) continue;  // rule 13
                        if (nationalities[JAPANESE] != hobbies[CHESS]) continue;  // rule 14

                        // All constraints satisfied – extract answer.
                        int water_house = drinks[WATER];
                        int zebra_house = pets[ZEBRA];

                        Solution result;
                        for (int i = 0; i < 5; ++i) {
                            if (nationalities[i] == water_house)
                                result.drinksWater = NATIONALITY_NAMES[i];
                            if (nationalities[i] == zebra_house)
                                result.ownsZebra = NATIONALITY_NAMES[i];
                        }
                        return result;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    return {};  // Should never be reached
}

}  // namespace zebra_puzzle

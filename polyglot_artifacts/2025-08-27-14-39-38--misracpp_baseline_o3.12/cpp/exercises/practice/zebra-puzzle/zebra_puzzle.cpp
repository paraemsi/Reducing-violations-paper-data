#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <string>

namespace zebra_puzzle {

namespace {

using std::array;
using std::next_permutation;
using std::string;
using std::abs;

enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

constexpr array<string, 5> kNationalityNames{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

}  // namespace

Solution solve() {
    array<int, 5> nat{0, 1, 2, 3, 4};
    do {  // Nationalities
        if (nat[NORWEGIAN] != 0) continue;  // 10

        array<int, 5> color{0, 1, 2, 3, 4};
        do {  // Colors
            if (nat[ENGLISHMAN] != color[RED]) continue;             // 2
            if (color[GREEN] - color[IVORY] != 1) continue;          // 6
            if (abs(nat[NORWEGIAN] - color[BLUE]) != 1) continue;    // 15

            array<int, 5> drink{0, 1, 2, 3, 4};
            do {  // Drinks
                if (color[GREEN] != drink[COFFEE]) continue;         // 4
                if (nat[UKRAINIAN] != drink[TEA]) continue;          // 5
                if (drink[MILK] != 2) continue;                      // 9 (middle)

                array<int, 5> pet{0, 1, 2, 3, 4};
                do {  // Pets
                    if (nat[SPANIARD] != pet[DOG]) continue;         // 3

                    array<int, 5> hobby{0, 1, 2, 3, 4};
                    do {  // Hobbies
                        if (pet[SNAILS] != hobby[DANCING]) continue;          // 7
                        if (color[YELLOW] != hobby[PAINTER]) continue;        // 8
                        if (hobby[FOOTBALL] != drink[ORANGE_JUICE]) continue; // 13
                        if (nat[JAPANESE] != hobby[CHESS]) continue;          // 14
                        if (abs(hobby[PAINTER] - pet[HORSE]) != 1) continue;  // 12
                        if (abs(hobby[READING] - pet[FOX]) != 1) continue;    // 11

                        // All constraints satisfied – build result
                        int water_house = drink[WATER];
                        int zebra_house = pet[ZEBRA];

                        Solution result;
                        for (size_t i = 0; i < nat.size(); ++i) {
                            if (nat[i] == water_house)
                                result.drinksWater = kNationalityNames[i];
                            if (nat[i] == zebra_house)
                                result.ownsZebra = kNationalityNames[i];
                        }
                        return result;
                    } while (next_permutation(hobby.begin(), hobby.end()));
                } while (next_permutation(pet.begin(), pet.end()));
            } while (next_permutation(drink.begin(), drink.end()));
        } while (next_permutation(color.begin(), color.end()));
    } while (next_permutation(nat.begin(), nat.end()));

    return {};  // Should never reach here
}

}  // namespace zebra_puzzle

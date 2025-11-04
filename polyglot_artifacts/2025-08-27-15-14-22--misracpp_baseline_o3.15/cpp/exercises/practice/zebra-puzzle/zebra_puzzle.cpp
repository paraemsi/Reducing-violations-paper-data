#include "zebra_puzzle.h"

#include <array>
#include <algorithm>
#include <cstdlib>  // for std::abs on integral types
#include <cmath>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Nationality { ENGLISH, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
    enum Drink { COFFEE, TEA, MILK, OJ, WATER };
    enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

    const std::array<std::string, 5> nationality_names{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    std::array<int, 5> base{0, 1, 2, 3, 4};

    std::array<int, 5> color = base;
    do {
        if (color[GREEN] != color[IVORY] + 1) continue;               // #6

        std::array<int, 5> nat = base;
        do {
            if (nat[ENGLISH] != color[RED]) continue;                 // #2
            if (nat[NORWEGIAN] != 0) continue;                        // #10
            if (std::abs(nat[NORWEGIAN] - color[BLUE]) != 1) continue;// #15

            std::array<int, 5> drink = base;
            do {
                if (drink[COFFEE] != color[GREEN]) continue;          // #4
                if (drink[TEA] != nat[UKRAINIAN]) continue;           // #5
                if (drink[MILK] != 2) continue;                       // #9

                std::array<int, 5> hobby = base;
                do {
                    if (hobby[PAINTER] != color[YELLOW]) continue;    // #8
                    if (hobby[FOOTBALL] != drink[OJ]) continue;       // #13
                    if (hobby[CHESS] != nat[JAPANESE]) continue;      // #14

                    std::array<int, 5> pet = base;
                    do {
                        if (pet[DOG] != nat[SPANIARD]) continue;      // #3
                        if (pet[SNAIL] != hobby[DANCING]) continue;   // #7
                        if (std::abs(hobby[READING] - pet[FOX]) != 1) continue;   // #11
                        if (std::abs(hobby[PAINTER] - pet[HORSE]) != 1) continue; // #12

                        Solution s;
                        int water_house = drink[WATER];
                        int zebra_house = pet[ZEBRA];
                        for (int i = 0; i < 5; ++i) {
                            if (nat[i] == water_house)
                                s.drinksWater = nationality_names[i];
                            if (nat[i] == zebra_house)
                                s.ownsZebra = nationality_names[i];
                        }
                        return s;
                    } while (std::next_permutation(pet.begin(), pet.end()));
                } while (std::next_permutation(hobby.begin(), hobby.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    return {}; // Should never be reached
}

}  // namespace zebra_puzzle

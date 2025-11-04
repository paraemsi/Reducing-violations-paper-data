#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    enum Color { BLUE, GREEN, IVORY, RED, YELLOW };
    enum Nationality { ENGLISHMAN, JAPANESE, NORWEGIAN, SPANIARD, UKRAINIAN };
    enum Pet { DOG, FOX, HORSE, SNAILS, ZEBRA };
    enum Drink { COFFEE, MILK, ORANGE_JUICE, TEA, WATER };
    enum Hobby { CHESS, DANCING, FOOTBALL, PAINTING, READING };

    std::array<int, 5> indices = {0, 1, 2, 3, 4};

    std::array<std::string, 5> nat_names = {
        "Englishman", "Japanese", "Norwegian", "Spaniard", "Ukrainian"};

    Solution sol;

    std::array<int, 5> color, nat, drink, pet, hobby;

    // Permute colors first – apply the "green right of ivory" constraint early.
    color = indices;
    do {
        int idx_green = std::find(color.begin(), color.end(), GREEN) - color.begin();
        int idx_ivory = std::find(color.begin(), color.end(), IVORY) - color.begin();
        if (idx_green != idx_ivory + 1) continue;  // 6

        // Permute nationalities next.
        nat = indices;
        do {
            if (nat[0] != NORWEGIAN) continue;  // 10

            int idx_red = std::find(color.begin(), color.end(), RED) - color.begin();
            int idx_english =
                std::find(nat.begin(), nat.end(), ENGLISHMAN) - nat.begin();
            if (idx_red != idx_english) continue;  // 2

            int idx_blue = std::find(color.begin(), color.end(), BLUE) - color.begin();
            int idx_norway = 0;  // Norwegian lives in the first house
            if (std::abs(idx_norway - idx_blue) != 1) continue;  // 15

            // Drinks.
            drink = indices;
            do {
                if (drink[2] != MILK) continue;                 // 9
                if (drink[idx_green] != COFFEE) continue;       // 4

                int idx_ukrainian =
                    std::find(nat.begin(), nat.end(), UKRAINIAN) - nat.begin();
                if (drink[idx_ukrainian] != TEA) continue;      // 5

                // Pets.
                pet = indices;
                do {
                    int idx_span =
                        std::find(nat.begin(), nat.end(), SPANIARD) - nat.begin();
                    if (pet[idx_span] != DOG) continue;         // 3

                    // Hobbies.
                    hobby = indices;
                    do {
                        int idx_snails =
                            std::find(pet.begin(), pet.end(), SNAILS) - pet.begin();
                        if (hobby[idx_snails] != DANCING) continue;       // 7

                        int idx_yellow =
                            std::find(color.begin(), color.end(), YELLOW) - color.begin();
                        if (hobby[idx_yellow] != PAINTING) continue;      // 8

                        int idx_football =
                            std::find(hobby.begin(), hobby.end(), FOOTBALL) - hobby.begin();
                        if (drink[idx_football] != ORANGE_JUICE) continue; // 13

                        int idx_japanese =
                            std::find(nat.begin(), nat.end(), JAPANESE) - nat.begin();
                        if (hobby[idx_japanese] != CHESS) continue;       // 14

                        int idx_reading =
                            std::find(hobby.begin(), hobby.end(), READING) - hobby.begin();
                        int idx_fox =
                            std::find(pet.begin(), pet.end(), FOX) - pet.begin();
                        if (std::abs(idx_reading - idx_fox) != 1) continue; // 11

                        int idx_painter = idx_yellow;  // painter lives in yellow
                        int idx_horse =
                            std::find(pet.begin(), pet.end(), HORSE) - pet.begin();
                        if (std::abs(idx_painter - idx_horse) != 1) continue; // 12

                        // Found the only solution.
                        int idx_water =
                            std::find(drink.begin(), drink.end(), WATER) - drink.begin();
                        sol.drinksWater = nat_names[nat[idx_water]];

                        int idx_zebra =
                            std::find(pet.begin(), pet.end(), ZEBRA) - pet.begin();
                        sol.ownsZebra = nat_names[nat[idx_zebra]];

                        return sol;
                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Should never reach here – the puzzle has exactly one solution.
    return sol;
}

}  // namespace zebra_puzzle

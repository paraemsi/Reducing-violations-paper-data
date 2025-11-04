#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {
inline bool next_to(int a, int b) { return std::abs(a - b) == 1; }
}  // namespace

Solution solve() {
    enum Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese, NatCount };
    enum Color { Red, Green, Ivory, Yellow, Blue, ColorCount };
    enum Pet { Dog, Fox, Horse, Snails, Zebra, PetCount };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water, DrinkCount };
    enum Hobby { Dancing, Painting, Reading, Football, Chess, HobbyCount };

    std::array<int, 5> base = {0, 1, 2, 3, 4};

    std::array<int, 5> nat, col, bev, hob, pet;

    // Nationalities
    nat = base;
    do {
        if (nat[Norwegian] != 0) continue;  // Clue 10

        // Colors
        col = base;
        do {
            if (col[Green] != col[Ivory] + 1) continue;            // Clue 6
            if (nat[Englishman] != col[Red]) continue;             // Clue 2
            if (!next_to(nat[Norwegian], col[Blue])) continue;     // Clue 15

            // Drinks
            bev = base;
            do {
                if (bev[Milk] != 2) continue;                      // Clue 9
                if (bev[Coffee] != col[Green]) continue;           // Clue 4
                if (bev[Tea] != nat[Ukrainian]) continue;          // Clue 5

                // Hobbies
                hob = base;
                do {
                    if (hob[Painting] != col[Yellow]) continue;          // Clue 8
                    if (hob[Chess] != nat[Japanese]) continue;            // Clue 14
                    if (hob[Football] != bev[OrangeJuice]) continue;      // Clue 13

                    // Pets
                    pet = base;
                    do {
                        if (pet[Dog] != nat[Spaniard]) continue;                // Clue 3
                        if (!next_to(hob[Reading], pet[Fox])) continue;         // Clue 11
                        if (!next_to(hob[Painting], pet[Horse])) continue;      // Clue 12
                        if (pet[Snails] != hob[Dancing]) continue;              // Clue 7

                        // Found a solution
                        static const char* nationality_names[5] = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        int water_pos = bev[Water];
                        int zebra_pos = pet[Zebra];

                        int water_nat = -1;
                        int zebra_nat = -1;

                        for (int n = 0; n < 5; ++n) {
                            if (nat[n] == water_pos) water_nat = n;
                            if (nat[n] == zebra_pos) zebra_nat = n;
                        }

                        Solution s;
                        s.drinksWater = nationality_names[water_nat];
                        s.ownsZebra = nationality_names[zebra_nat];
                        return s;
                    } while (std::next_permutation(pet.begin(), pet.end()));
                } while (std::next_permutation(hob.begin(), hob.end()));
            } while (std::next_permutation(bev.begin(), bev.end()));
        } while (std::next_permutation(col.begin(), col.end()));
    } while (std::next_permutation(nat.begin(), nat.end()));

    // No solution found (should not happen with valid puzzle).
    return Solution{};
}

}  // namespace zebra_puzzle

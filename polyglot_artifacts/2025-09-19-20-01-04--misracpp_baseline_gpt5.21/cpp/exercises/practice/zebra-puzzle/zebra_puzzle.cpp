#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>

namespace zebra_puzzle {

Solution solve() {
    using std::array;

    enum Color { Red, Green, Ivory, Yellow, Blue };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Hobby { Dancing, Painting, Reading, Football, Chess };
    enum Nat { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum Pet { Dog, Snails, Fox, Horse, Zebra };

    array<int, 5> base = {0, 1, 2, 3, 4};

    array<int, 5> color = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (color[Green] != color[Ivory] + 1) continue;

        array<int, 5> drink = base;
        do {
            // 4. The person in the green house drinks coffee.
            if (drink[Coffee] != color[Green]) continue;
            // 9. The person in the middle house drinks milk.
            if (drink[Milk] != 2) continue;

            array<int, 5> hobby = base;
            do {
                // 8. The person in the yellow house is a painter.
                if (hobby[Painting] != color[Yellow]) continue;
                // 13. The person who plays football drinks orange juice.
                if (hobby[Football] != drink[OrangeJuice]) continue;

                array<int, 5> nat = base;
                do {
                    // 2. The Englishman lives in the red house.
                    if (nat[Englishman] != color[Red]) continue;
                    // 5. The Ukrainian drinks tea.
                    if (nat[Ukrainian] != drink[Tea]) continue;
                    // 10. The Norwegian lives in the first house.
                    if (nat[Norwegian] != 0) continue;
                    // 14. The Japanese person plays chess.
                    if (nat[Japanese] != hobby[Chess]) continue;
                    // 15. The Norwegian lives next to the blue house.
                    if (std::abs(nat[Norwegian] - color[Blue]) != 1) continue;

                    array<int, 5> pet = base;
                    do {
                        // 3. The Spaniard owns the dog.
                        if (pet[Dog] != nat[Spaniard]) continue;
                        // 7. The snail owner likes to go dancing.
                        if (pet[Snails] != hobby[Dancing]) continue;
                        // 12. The painter's house is next to the house with the horse.
                        if (std::abs(hobby[Painting] - pet[Horse]) != 1) continue;
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (std::abs(hobby[Reading] - pet[Fox]) != 1) continue;

                        // Found a valid configuration
                        int natAtHouse[5];
                        for (int n = 0; n < 5; ++n) natAtHouse[nat[n]] = n;

                        int waterHouse = drink[Water];
                        int zebraHouse = pet[Zebra];

                        const char* natNames[5] = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        Solution s;
                        s.drinksWater = natNames[natAtHouse[waterHouse]];
                        s.ownsZebra = natNames[natAtHouse[zebraHouse]];
                        return s;

                    } while (std::next_permutation(pet.begin(), pet.end()));
                } while (std::next_permutation(nat.begin(), nat.end()));
            } while (std::next_permutation(hobby.begin(), hobby.end()));
        } while (std::next_permutation(drink.begin(), drink.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Return empty on failure (should not happen for well-posed puzzle).
    return Solution{};
}

}  // namespace zebra_puzzle

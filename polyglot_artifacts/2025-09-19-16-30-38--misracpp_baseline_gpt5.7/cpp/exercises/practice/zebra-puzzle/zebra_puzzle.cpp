#include "zebra_puzzle.h"

#include <algorithm>
#include <array>

namespace zebra_puzzle {

Solution solve() {
    enum Color { Red, Green, Ivory, Yellow, Blue };
    enum Nation { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Pet { Dog, Snails, Fox, Horse, Zebra };
    enum Hobby { Dancing, Painting, Reading, Football, Chess };

    using Perm = std::array<int, 5>;
    const Perm base = {0, 1, 2, 3, 4};
    auto next_to = [](int a, int b) { return a == b + 1 || a + 1 == b; };

    Perm color = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (color[Green] != color[Ivory] + 1) continue;

        Perm nation = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (nation[Norwegian] != 0) continue;

            // 2. The Englishman lives in the red house.
            if (nation[Englishman] != color[Red]) continue;

            // 15. The Norwegian lives next to the blue house.
            if (!next_to(nation[Norwegian], color[Blue])) continue;

            Perm drink = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (drink[Milk] != 2) continue;

                // 4. The person in the green house drinks coffee.
                if (color[Green] != drink[Coffee]) continue;

                // 5. The Ukrainian drinks tea.
                if (nation[Ukrainian] != drink[Tea]) continue;

                Perm pet = base;
                do {
                    // 3. The Spaniard owns the dog.
                    if (nation[Spaniard] != pet[Dog]) continue;

                    Perm hobby = base;
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (pet[Snails] != hobby[Dancing]) continue;

                        // 8. The person in the yellow house is a painter.
                        if (color[Yellow] != hobby[Painting]) continue;

                        // 12. The painter's house is next to the house with the horse.
                        if (!next_to(hobby[Painting], pet[Horse])) continue;

                        // 13. The person who plays football drinks orange juice.
                        if (hobby[Football] != drink[OrangeJuice]) continue;

                        // 14. The Japanese person plays chess.
                        if (nation[Japanese] != hobby[Chess]) continue;

                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!next_to(hobby[Reading], pet[Fox])) continue;

                        // Found unique solution.
                        int water_pos = drink[Water];
                        int zebra_pos = pet[Zebra];

                        int water_nat = -1;
                        int zebra_nat = -1;
                        for (int n = 0; n < 5; ++n) {
                            if (nation[n] == water_pos) water_nat = n;
                            if (nation[n] == zebra_pos) zebra_nat = n;
                        }

                        static const char* natNames[5] = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        Solution s;
                        s.drinksWater = natNames[water_nat];
                        s.ownsZebra = natNames[zebra_nat];
                        return s;
                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nation.begin(), nation.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Should not happen if the puzzle is well-formed.
    return Solution{};
}

}  // namespace zebra_puzzle

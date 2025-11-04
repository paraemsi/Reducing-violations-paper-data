#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    enum Color { Red, Green, Ivory, Yellow, Blue };
    enum Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum Pet { Dog, Fox, Horse, Snail, Zebra };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Hobby { Dancing, Painting, Reading, Football, Chess };

    const char* natNames[5] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    std::array<int, 5> base = {0, 1, 2, 3, 4};

    std::array<int, 5> colors = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!(colors[Green] == colors[Ivory] + 1)) continue;

        std::array<int, 5> nat = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (nat[Norwegian] != 0) continue;
            // 2. The Englishman lives in the red house.
            if (nat[Englishman] != colors[Red]) continue;
            // 15. The Norwegian lives next to the blue house.
            if (std::abs(nat[Norwegian] - colors[Blue]) != 1) continue;

            std::array<int, 5> drinks = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (drinks[Milk] != 2) continue;
                // 4. The person in the green house drinks coffee.
                if (drinks[Coffee] != colors[Green]) continue;
                // 5. The Ukrainian drinks tea.
                if (drinks[Tea] != nat[Ukrainian]) continue;

                std::array<int, 5> hobbies = base;
                do {
                    // 8. The person in the yellow house is a painter.
                    if (hobbies[Painting] != colors[Yellow]) continue;
                    // 14. The Japanese person plays chess.
                    if (hobbies[Chess] != nat[Japanese]) continue;
                    // 13. The person who plays football drinks orange juice.
                    if (hobbies[Football] != drinks[OrangeJuice]) continue;

                    std::array<int, 5> pets = base;
                    do {
                        // 3. The Spaniard owns the dog.
                        if (pets[Dog] != nat[Spaniard]) continue;
                        // 7. The snail owner likes to go dancing.
                        if (pets[Snail] != hobbies[Dancing]) continue;
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (std::abs(hobbies[Reading] - pets[Fox]) != 1) continue;
                        // 12. The painter's house is next to the house with the horse.
                        if (std::abs(hobbies[Painting] - pets[Horse]) != 1) continue;

                        // Found solution
                        int idxWater = drinks[Water];
                        int idxZebra = pets[Zebra];

                        int natWater = -1;
                        int natZebra = -1;
                        for (int n = 0; n < 5; ++n) {
                            if (nat[n] == idxWater) natWater = n;
                            if (nat[n] == idxZebra) natZebra = n;
                        }

                        Solution s;
                        s.drinksWater = natNames[natWater];
                        s.ownsZebra = natNames[natZebra];
                        return s;

                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // No valid solution found (should not happen for this puzzle).
    return Solution{};
}

}  // namespace zebra_puzzle

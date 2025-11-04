#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    enum Color { Red, Green, Ivory, Yellow, Blue, ColorCount };
    enum Nation { Englishman, Spaniard, Ukrainian, Norwegian, Japanese, NationCount };
    enum Pet { Dog, Snails, Fox, Horse, Zebra, PetCount };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water, DrinkCount };
    enum Hobby { Dancing, Painting, Reading, Football, Chess, HobbyCount };

    std::array<int, 5> color = {0, 1, 2, 3, 4};
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (color[Green] != color[Ivory] + 1) continue;

        std::array<int, 5> nation = {0, 1, 2, 3, 4};
        do {
            // 10. The Norwegian lives in the first house.
            if (nation[Norwegian] != 0) continue;
            // 2. The Englishman lives in the red house.
            if (nation[Englishman] != color[Red]) continue;
            // 15. The Norwegian lives next to the blue house.
            if (std::abs(nation[Norwegian] - color[Blue]) != 1) continue;

            std::array<int, 5> drink = {0, 1, 2, 3, 4};
            do {
                // 9. The person in the middle house drinks milk.
                if (drink[Milk] != 2) continue;
                // 4. The person in the green house drinks coffee.
                if (drink[Coffee] != color[Green]) continue;
                // 5. The Ukrainian drinks tea.
                if (drink[Tea] != nation[Ukrainian]) continue;

                std::array<int, 5> hobby = {0, 1, 2, 3, 4};
                do {
                    // 8. The person in the yellow house is a painter.
                    if (hobby[Painting] != color[Yellow]) continue;
                    // 13. The person who plays football drinks orange juice.
                    if (hobby[Football] != drink[OrangeJuice]) continue;
                    // 14. The Japanese person plays chess.
                    if (hobby[Chess] != nation[Japanese]) continue;

                    std::array<int, 5> pet = {0, 1, 2, 3, 4};
                    do {
                        // 3. The Spaniard owns the dog.
                        if (pet[Dog] != nation[Spaniard]) continue;
                        // 7. The snail owner likes to go dancing.
                        if (pet[Snails] != hobby[Dancing]) continue;
                        // 11. The reader lives next to the person with the fox.
                        if (std::abs(hobby[Reading] - pet[Fox]) != 1) continue;
                        // 12. The painter's house is next to the house with the horse.
                        if (std::abs(hobby[Painting] - pet[Horse]) != 1) continue;

                        static const char* nationalityNames[5] = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

                        Solution s;
                        for (int n = 0; n < 5; ++n) {
                            if (nation[n] == drink[Water]) s.drinksWater = nationalityNames[n];
                            if (nation[n] == pet[Zebra]) s.ownsZebra = nationalityNames[n];
                        }
                        return s;

                    } while (std::next_permutation(pet.begin(), pet.end()));
                } while (std::next_permutation(hobby.begin(), hobby.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nation.begin(), nation.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Should never reach here for a well-posed puzzle.
    return Solution{};
}

}  // namespace zebra_puzzle

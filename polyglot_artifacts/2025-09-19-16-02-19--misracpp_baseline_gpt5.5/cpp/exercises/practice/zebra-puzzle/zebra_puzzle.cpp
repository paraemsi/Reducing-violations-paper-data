#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    enum Color { Red, Green, Ivory, Yellow, Blue };
    enum Nat { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum Pet { Dog, Snails, Fox, Horse, Zebra };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Hobby { Dancing, Painter, Reading, Football, Chess };

    auto next_to = [](int a, int b) { return std::abs(a - b) == 1; };

    std::array<int, 5> colors = {0, 1, 2, 3, 4};
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (colors[Green] != colors[Ivory] + 1) continue;

        std::array<int, 5> drinks = {0, 1, 2, 3, 4};
        do {
            // 9. The person in the middle house drinks milk.
            if (drinks[Milk] != 2) continue;
            // 4. The person in the green house drinks coffee.
            if (drinks[Coffee] != colors[Green]) continue;

            std::array<int, 5> hobbies = {0, 1, 2, 3, 4};
            do {
                // 8. The person in the yellow house is a painter.
                if (hobbies[Painter] != colors[Yellow]) continue;
                // 13. The person who plays football drinks orange juice.
                if (drinks[OrangeJuice] != hobbies[Football]) continue;

                std::array<int, 5> nats = {0, 1, 2, 3, 4};
                do {
                    // 10. The Norwegian lives in the first house.
                    if (nats[Norwegian] != 0) continue;
                    // 2. The Englishman lives in the red house.
                    if (nats[Englishman] != colors[Red]) continue;
                    // 5. The Ukrainian drinks tea.
                    if (nats[Ukrainian] != drinks[Tea]) continue;
                    // 14. The Japanese person plays chess.
                    if (nats[Japanese] != hobbies[Chess]) continue;
                    // 15. The Norwegian lives next to the blue house.
                    if (!next_to(nats[Norwegian], colors[Blue])) continue;

                    std::array<int, 5> pets = {0, 1, 2, 3, 4};
                    do {
                        // 3. The Spaniard owns the dog.
                        if (nats[Spaniard] != pets[Dog]) continue;
                        // 7. The snail owner likes to go dancing.
                        if (pets[Snails] != hobbies[Dancing]) continue;
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!next_to(hobbies[Reading], pets[Fox])) continue;
                        // 12. The painter's house is next to the house with the horse.
                        if (!next_to(hobbies[Painter], pets[Horse])) continue;

                        static const char* natNames[5] = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        int waterPos = drinks[Water];
                        int zebraPos = pets[Zebra];

                        int waterNat = -1;
                        int zebraNat = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (nats[i] == waterPos) waterNat = i;
                            if (nats[i] == zebraPos) zebraNat = i;
                        }

                        Solution s;
                        if (waterNat >= 0) s.drinksWater = natNames[waterNat];
                        if (zebraNat >= 0) s.ownsZebra = natNames[zebraNat];
                        return s;

                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(nats.begin(), nats.end()));
            } while (std::next_permutation(hobbies.begin(), hobbies.end()));
        } while (std::next_permutation(drinks.begin(), drinks.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    return Solution{};
}

}  // namespace zebra_puzzle

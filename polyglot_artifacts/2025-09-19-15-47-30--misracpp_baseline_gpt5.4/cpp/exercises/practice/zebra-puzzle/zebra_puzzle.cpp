#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

enum Color { Red, Green, Ivory, Yellow, Blue, ColorCount };
enum Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese, NationalityCount };
enum Pet { Dog, Snails, Fox, Horse, Zebra, PetCount };
enum Drink { Coffee, Tea, Milk, OrangeJuice, Water, DrinkCount };
enum Hobby { Dancing, Painter, Reading, Football, Chess, HobbyCount };

Solution solve() {
    using Arr = std::array<int, 5>;
    const Arr base = {0, 1, 2, 3, 4};

    Arr nat;
    Arr color;
    Arr drink;
    Arr pet;
    Arr hobby;

    const std::array<std::string, 5> natNames = {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    nat = base;
    do {
        // 10. The Norwegian lives in the first house.
        if (nat[Norwegian] != 0) continue;

        color = base;
        do {
            // 6. The green house is immediately to the right of the ivory house.
            if (color[Green] != color[Ivory] + 1) continue;
            // 2. The Englishman lives in the red house.
            if (nat[Englishman] != color[Red]) continue;
            // 15. The Norwegian lives next to the blue house.
            if (std::abs(nat[Norwegian] - color[Blue]) != 1) continue;

            drink = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (drink[Milk] != 2) continue;
                // 4. The person in the green house drinks coffee.
                if (color[Green] != drink[Coffee]) continue;
                // 5. The Ukrainian drinks tea.
                if (nat[Ukrainian] != drink[Tea]) continue;

                pet = base;
                do {
                    // 3. The Spaniard owns the dog.
                    if (nat[Spaniard] != pet[Dog]) continue;

                    hobby = base;
                    do {
                        // 8. The person in the yellow house is a painter.
                        if (color[Yellow] != hobby[Painter]) continue;
                        // 13. The person who plays football drinks orange juice.
                        if (hobby[Football] != drink[OrangeJuice]) continue;
                        // 14. The Japanese person plays chess.
                        if (nat[Japanese] != hobby[Chess]) continue;
                        // 7. The snail owner likes to go dancing.
                        if (pet[Snails] != hobby[Dancing]) continue;
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (std::abs(hobby[Reading] - pet[Fox]) != 1) continue;
                        // 12. The painter's house is next to the house with the horse.
                        if (std::abs(hobby[Painter] - pet[Horse]) != 1) continue;

                        // All constraints satisfied; build the solution.
                        Solution s;
                        int waterPos = drink[Water];
                        int zebraPos = pet[Zebra];

                        for (int i = 0; i < 5; ++i) {
                            if (nat[i] == waterPos) {
                                s.drinksWater = natNames[i];
                            }
                            if (nat[i] == zebraPos) {
                                s.ownsZebra = natNames[i];
                            }
                        }
                        return s;
                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(color.begin(), color.end()));
    } while (std::next_permutation(nat.begin(), nat.end()));

    // Should never reach here for a well-formed puzzle.
    return Solution{};
}

}  // namespace zebra_puzzle

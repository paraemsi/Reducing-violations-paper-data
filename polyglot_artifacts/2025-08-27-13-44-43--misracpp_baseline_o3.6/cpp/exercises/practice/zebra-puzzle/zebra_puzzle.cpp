#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    // Enumerations for each attribute
    enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Nat { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA };
    enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

    using std::array;
    using std::next_permutation;

    const array<int, 5> init = {0, 1, 2, 3, 4};

    array<int, 5> colorPos, natPos, petPos, drinkPos, hobbyPos;
    Solution result{};

    array<int, 5> colors = init;
    do {
        colorPos = colors;

        // 6. Green is immediately right of Ivory
        if (colorPos[GREEN] != colorPos[IVORY] + 1) continue;

        array<int, 5> nats = init;
        do {
            natPos = nats;

            // 10. Norwegian in first house
            if (natPos[NORWEGIAN] != 0) continue;

            // 2. Englishman lives in red house
            if (natPos[ENGLISHMAN] != colorPos[RED]) continue;

            // 15. Norwegian next to blue house
            if (std::abs(colorPos[BLUE] - natPos[NORWEGIAN]) != 1) continue;

            array<int, 5> drinks = init;
            do {
                drinkPos = drinks;

                // 4. Green house drinks coffee
                if (drinkPos[COFFEE] != colorPos[GREEN]) continue;

                // 5. Ukrainian drinks tea
                if (drinkPos[TEA] != natPos[UKRAINIAN]) continue;

                // 9. Middle house (index 2) drinks milk
                if (drinkPos[MILK] != 2) continue;

                array<int, 5> pets = init;
                do {
                    petPos = pets;

                    // 3. Spaniard owns dog
                    if (petPos[DOG] != natPos[SPANIARD]) continue;

                    array<int, 5> hobbies = init;
                    do {
                        hobbyPos = hobbies;

                        // 8. Yellow house is painter
                        if (hobbyPos[PAINTER] != colorPos[YELLOW]) continue;

                        // 7. Snail owner likes dancing
                        if (hobbyPos[DANCING] != petPos[SNAILS]) continue;

                        // 13. Football drinks orange juice
                        if (hobbyPos[FOOTBALL] != drinkPos[ORANGE_JUICE]) continue;

                        // 14. Japanese plays chess
                        if (hobbyPos[CHESS] != natPos[JAPANESE]) continue;

                        // 11. Reader lives next to fox
                        if (std::abs(hobbyPos[READING] - petPos[FOX]) != 1) continue;

                        // 12. Painter next to horse
                        if (std::abs(hobbyPos[PAINTER] - petPos[HORSE]) != 1) continue;

                        // All constraints satisfied – determine the required residents
                        int waterNat = -1, zebraNat = -1;
                        for (int n = 0; n < 5; ++n) {
                            if (natPos[n] == drinkPos[WATER]) waterNat = n;
                            if (natPos[n] == petPos[ZEBRA]) zebraNat = n;
                        }

                        static const array<std::string, 5> natNames{
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

                        result.drinksWater = natNames[waterNat];
                        result.ownsZebra  = natNames[zebraNat];
                        return result;

                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(nats.begin(), nats.end()));
    } while (next_permutation(colors.begin(), colors.end()));

    return result; // Should never reach here
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <array>
#include <algorithm>
#include <cstdlib>
#include <iterator>

namespace zebra_puzzle {

// Order of every attribute inside its own domain.
// Each id is therefore 0-based and unique inside the domain.
enum Color { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT };
enum Nation { ENGLISH, SPANISH, UKRAINIAN, NORWEGIAN, JAPANESE, NATION_COUNT };
enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA, PET_COUNT };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER, DRINK_COUNT };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS, HOBBY_COUNT };

// Convenient alias
using Permutation = std::array<int, 5>;

/* Generate the next permutation of indices [0,1,2,3,4] and return true
 * while there is another permutation left.  Wrapper added so we can use
 * std::next_permutation on std::array directly.
 */
inline bool next_perm(Permutation &p) {
    return std::next_permutation(p.begin(), p.end());
}

Solution solve() {
    // Initial “identity” permutation [0,1,2,3,4]
    Permutation colors{0, 1, 2, 3, 4};
    Permutation nations{0, 1, 2, 3, 4};
    Permutation drinks{0, 1, 2, 3, 4};
    Permutation pets{0, 1, 2, 3, 4};
    Permutation hobbies{0, 1, 2, 3, 4};

    // Iterate over all domains while pruning aggressively.
    do {
        // (6) Green is immediately to the right of ivory
        if (colors[GREEN] != colors[IVORY] + 1)
            continue;

        // pre-compute indices we will need often
        const int red_house   = colors[RED];
        const int green_house = colors[GREEN];
        const int yellow_house = colors[YELLOW];
        const int blue_house   = colors[BLUE];

        // Nationalities
        nations = {0, 1, 2, 3, 4};
        do {
            const int english_house   = nations[ENGLISH];
            const int spanish_house   = nations[SPANISH];
            const int ukrainian_house = nations[UKRAINIAN];
            const int norwegian_house = nations[NORWEGIAN];
            const int japanese_house  = nations[JAPANESE];

            // (2) Englishman lives in red house
            if (english_house != red_house)
                continue;
            // (10) Norwegian lives in first (index 0) house
            if (norwegian_house != 0)
                continue;
            // (15) Norwegian lives next to blue house
            if (std::abs(norwegian_house - blue_house) != 1)
                continue;

            // Drinks
            drinks = {0, 1, 2, 3, 4};
            do {
                const int coffee_house  = drinks[COFFEE];
                const int tea_house     = drinks[TEA];
                const int milk_house    = drinks[MILK];
                const int oj_house      = drinks[ORANGE_JUICE];
                const int water_house   = drinks[WATER];

                // (4) Green house drinks coffee
                if (coffee_house != green_house)
                    continue;
                // (5) Ukrainian drinks tea
                if (ukrainian_house != tea_house)
                    continue;
                // (9) Middle (index 2) house drinks milk
                if (milk_house != 2)
                    continue;

                // Pets
                pets = {0, 1, 2, 3, 4};
                do {
                    const int dog_house   = pets[DOG];
                    const int snail_house = pets[SNAIL];
                    const int fox_house   = pets[FOX];
                    const int horse_house = pets[HORSE];
                    const int zebra_house = pets[ZEBRA];

                    // (3) Spaniard owns the dog
                    if (spanish_house != dog_house)
                        continue;

                    // Hobbies
                    hobbies = {0, 1, 2, 3, 4};
                    do {
                        const int dancing_house  = hobbies[DANCING];
                        const int painting_house = hobbies[PAINTING];
                        const int reading_house  = hobbies[READING];
                        const int football_house = hobbies[FOOTBALL];
                        const int chess_house    = hobbies[CHESS];

                        // (7) Snail owner likes dancing
                        if (snail_house != dancing_house)
                            continue;
                        // (8) Yellow house painter
                        if (yellow_house != painting_house)
                            continue;
                        // (11) Reader lives next to fox
                        if (std::abs(reading_house - fox_house) != 1)
                            continue;
                        // (12) Painter next to horse
                        if (std::abs(painting_house - horse_house) != 1)
                            continue;
                        // (13) Football drinks orange juice
                        if (football_house != oj_house)
                            continue;
                        // (14) Japanese plays chess
                        if (japanese_house != chess_house)
                            continue;

                        // All constraints satisfied!
                        Solution sol;
                        sol.drinksWater = (water_house == english_house)   ? "Englishman"
                                         : (water_house == spanish_house)    ? "Spaniard"
                                         : (water_house == ukrainian_house)  ? "Ukrainian"
                                         : (water_house == norwegian_house)  ? "Norwegian"
                                         : "Japanese";

                        sol.ownsZebra = (zebra_house == english_house)   ? "Englishman"
                                      : (zebra_house == spanish_house)    ? "Spaniard"
                                      : (zebra_house == ukrainian_house)  ? "Ukrainian"
                                      : (zebra_house == norwegian_house)  ? "Norwegian"
                                      : "Japanese";

                        return sol;
                    } while (next_perm(hobbies));
                } while (next_perm(pets));
            } while (next_perm(drinks));
        } while (next_perm(nations));
    } while (next_perm(colors));

    // Should never reach here in the classic puzzle
    return {"", ""};
}

}  // namespace zebra_puzzle

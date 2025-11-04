#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>

namespace zebra_puzzle {

namespace {

// Enumerations for each category
enum Color { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT = 5 };
enum Nation { ENGLAND, SPAIN, UKRAINE, NORWAY, JAPAN, NATION_COUNT = 5 };
enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA, PET_COUNT = 5 };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER, DRINK_COUNT = 5 };
enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS, HOBBY_COUNT = 5 };

// For mapping indices back to human-readable nationality names.
static const char* kNationNames[NATION_COUNT] = {
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese",
};

inline bool adjacent(int a, int b) {
    return std::abs(a - b) == 1;
}

}  // namespace

Solution solve() {
    using std::array;
    const array<int, 5> base = {0, 1, 2, 3, 4};

    array<int, 5> posColor = base;
    do {
        // #6 The green house is immediately to the right of the ivory house.
        if (posColor[GREEN] != posColor[IVORY] + 1) continue;

        array<int, 5> posNation = base;
        do {
            // #10 The Norwegian lives in the first house.
            if (posNation[NORWAY] != 0) continue;

            // #2 The Englishman lives in the red house.
            if (posNation[ENGLAND] != posColor[RED]) continue;

            // #15 The Norwegian lives next to the blue house.
            if (!adjacent(posNation[NORWAY], posColor[BLUE])) continue;

            array<int, 5> posDrink = base;
            do {
                // #9 The person in the middle house drinks milk.
                if (posDrink[MILK] != 2) continue;

                // #4 The person in the green house drinks coffee.
                if (posDrink[COFFEE] != posColor[GREEN]) continue;

                // #5 The Ukrainian drinks tea.
                if (posNation[UKRAINE] != posDrink[TEA]) continue;

                array<int, 5> posHobby = base;
                do {
                    // #8 The person in the yellow house is a painter.
                    if (posHobby[PAINTER] != posColor[YELLOW]) continue;

                    // #14 The Japanese person plays chess.
                    if (posNation[JAPAN] != posHobby[CHESS]) continue;

                    // #13 The person who plays football drinks orange juice.
                    if (posHobby[FOOTBALL] != posDrink[ORANGE_JUICE]) continue;

                    array<int, 5> posPet = base;
                    do {
                        // #3 The Spaniard owns the dog.
                        if (posNation[SPAIN] != posPet[DOG]) continue;

                        // #7 The snail owner likes to go dancing.
                        if (posPet[SNAILS] != posHobby[DANCING]) continue;

                        // #11 Reading lives next to the fox.
                        if (!adjacent(posHobby[READING], posPet[FOX])) continue;

                        // #12 The painter's house is next to the house with the horse.
                        if (!adjacent(posHobby[PAINTER], posPet[HORSE])) continue;

                        // Found a consistent assignment. Extract answers.
                        const int waterPos = posDrink[WATER];
                        const int zebraPos = posPet[ZEBRA];

                        // Find nationalities at these positions.
                        int waterNation = -1;
                        int zebraNation = -1;
                        for (int n = 0; n < NATION_COUNT; ++n) {
                            if (posNation[n] == waterPos) waterNation = n;
                            if (posNation[n] == zebraPos) zebraNation = n;
                        }

                        Solution s;
                        s.drinksWater = kNationNames[waterNation];
                        s.ownsZebra = kNationNames[zebraNation];
                        return s;

                    } while (std::next_permutation(posPet.begin(), posPet.end()));

                } while (std::next_permutation(posHobby.begin(), posHobby.end()));

            } while (std::next_permutation(posDrink.begin(), posDrink.end()));

        } while (std::next_permutation(posNation.begin(), posNation.end()));

    } while (std::next_permutation(posColor.begin(), posColor.end()));

    // If no solution found (should not happen), return empty strings.
    return {};
}

}  // namespace zebra_puzzle

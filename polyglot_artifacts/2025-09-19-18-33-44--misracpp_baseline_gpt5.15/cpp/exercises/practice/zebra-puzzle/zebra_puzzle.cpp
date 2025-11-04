#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <string>

namespace zebra_puzzle {

namespace {

// Enumerations to index into arrays.
enum Color { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE, NATIONALITY_COUNT };
enum Drink { COFFEE, TEA, MILK, ORANGEJUICE, WATER, DRINK_COUNT };
enum Pet { DOG, FOX, SNAILS, HORSE, ZEBRA, PET_COUNT };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS, HOBBY_COUNT };

// Helper to check adjacency.
inline bool adjacent(int a, int b) {
    return (a == b + 1) || (b == a + 1);
}

}  // namespace

Solution solve() {
    using std::array;
    static const array<std::string, NATIONALITY_COUNT> kNationalityNames{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    // Position arrays map item -> house index (0..4 from left to right).
    array<int, COLOR_COUNT> posColor;
    array<int, NATIONALITY_COUNT> posNat;
    array<int, DRINK_COUNT> posDrink;
    array<int, PET_COUNT> posPet;
    array<int, HOBBY_COUNT> posHobby;

    // Base permutation for iteration.
    array<int, 5> base{0, 1, 2, 3, 4};

    // Colors
    posColor = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (posColor[GREEN] != posColor[IVORY] + 1) continue;

        // 15. The Norwegian lives next to the blue house.
        // Since the Norwegian is known to be in house 0 (see below),
        // the blue house must be at position 1 to be adjacent.
        if (posColor[BLUE] != 1) continue;

        // Nationalities
        posNat = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (posNat[NORWEGIAN] != 0) continue;

            // 2. The Englishman lives in the red house.
            if (posNat[ENGLISHMAN] != posColor[RED]) continue;

            // Drinks
            posDrink = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (posDrink[MILK] != 2) continue;

                // 4. The person in the green house drinks coffee.
                if (posDrink[COFFEE] != posColor[GREEN]) continue;

                // 5. The Ukrainian drinks tea.
                if (posDrink[TEA] != posNat[UKRAINIAN]) continue;

                // Hobbies
                posHobby = base;
                do {
                    // 8. The person in the yellow house is a painter.
                    if (posHobby[PAINTING] != posColor[YELLOW]) continue;

                    // 13. The person who plays football drinks orange juice.
                    if (posHobby[FOOTBALL] != posDrink[ORANGEJUICE]) continue;

                    // 14. The Japanese person plays chess.
                    if (posHobby[CHESS] != posNat[JAPANESE]) continue;

                    // Pets
                    posPet = base;
                    do {
                        // 3. The Spaniard owns the dog.
                        if (posPet[DOG] != posNat[SPANIARD]) continue;

                        // 7. The snail owner likes to go dancing.
                        if (posPet[SNAILS] != posHobby[DANCING]) continue;

                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!adjacent(posHobby[READING], posPet[FOX])) continue;

                        // 12. The painter's house is next to the house with the horse.
                        if (!adjacent(posHobby[PAINTING], posPet[HORSE])) continue;

                        // All constraints satisfied. Build solution.
                        auto nationality_at = [&](int house_pos) -> int {
                            for (int n = 0; n < NATIONALITY_COUNT; ++n) {
                                if (posNat[n] == house_pos) return n;
                            }
                            return -1;  // Should never happen if constraints satisfied.
                        };

                        Solution sol;
                        sol.drinksWater = kNationalityNames[nationality_at(posDrink[WATER])];
                        sol.ownsZebra = kNationalityNames[nationality_at(posPet[ZEBRA])];
                        return sol;

                    } while (std::next_permutation(posPet.begin(), posPet.end()));
                } while (std::next_permutation(posHobby.begin(), posHobby.end()));
            } while (std::next_permutation(posDrink.begin(), posDrink.end()));
        } while (std::next_permutation(posNat.begin(), posNat.end()));
    } while (std::next_permutation(posColor.begin(), posColor.end()));

    // If no solution found (should not happen), return empty strings.
    return Solution{};
}

}  // namespace zebra_puzzle

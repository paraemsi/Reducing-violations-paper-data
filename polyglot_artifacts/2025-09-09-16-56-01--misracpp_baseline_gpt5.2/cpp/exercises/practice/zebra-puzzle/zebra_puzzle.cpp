#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

enum Color { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE, NATIONALITY_COUNT };
enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA, PET_COUNT };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER, DRINK_COUNT };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS, HOBBY_COUNT };

static inline bool adjacent(int a, int b) { return std::abs(a - b) == 1; }

Solution solve() {
    // positions are indices 0..4 from left to right; arrays map attribute->position
    const std::array<int, 5> base = {0, 1, 2, 3, 4};

    std::array<int, 5> colors = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (colors[GREEN] != colors[IVORY] + 1) continue;

        std::array<int, 5> nations = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (nations[NORWEGIAN] != 0) continue;
            // 2. The Englishman lives in the red house.
            if (nations[ENGLISHMAN] != colors[RED]) continue;
            // 15. The Norwegian lives next to the blue house.
            if (!adjacent(nations[NORWEGIAN], colors[BLUE])) continue;

            std::array<int, 5> drinks = base;
            do {
                // 4. The person in the green house drinks coffee.
                if (drinks[COFFEE] != colors[GREEN]) continue;
                // 5. The Ukrainian drinks tea.
                if (drinks[TEA] != nations[UKRAINIAN]) continue;
                // 9. The person in the middle house drinks milk.
                if (drinks[MILK] != 2) continue;

                std::array<int, 5> pets = base;
                do {
                    // 3. The Spaniard owns the dog.
                    if (pets[DOG] != nations[SPANIARD]) continue;

                    std::array<int, 5> hobbies = base;
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (hobbies[DANCING] != pets[SNAILS]) continue;
                        // 8. The person in the yellow house is a painter.
                        if (hobbies[PAINTING] != colors[YELLOW]) continue;
                        // 14. The Japanese person plays chess.
                        if (hobbies[CHESS] != nations[JAPANESE]) continue;
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!adjacent(hobbies[READING], pets[FOX])) continue;
                        // 12. The painter's house is next to the house with the horse.
                        if (!adjacent(hobbies[PAINTING], pets[HORSE])) continue;
                        // 13. The person who plays football drinks orange juice.
                        if (hobbies[FOOTBALL] != drinks[ORANGE_JUICE]) continue;

                        // Found a consistent assignment; extract answers.
                        static const std::array<std::string, 5> nationalityNames = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        int waterPos = drinks[WATER];
                        int zebraPos = pets[ZEBRA];

                        int waterNat = -1;
                        int zebraNat = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (nations[i] == waterPos) waterNat = i;
                            if (nations[i] == zebraPos) zebraNat = i;
                        }

                        Solution s;
                        s.drinksWater = nationalityNames[waterNat];
                        s.ownsZebra = nationalityNames[zebraNat];
                        return s;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Should never reach here for a well-posed puzzle; return empty if not found.
    return Solution{};
}

}  // namespace zebra_puzzle

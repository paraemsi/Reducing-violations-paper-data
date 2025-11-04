#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {

enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nation { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS };

constexpr std::array<const char *, 5> nation_names{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

}  // namespace

Solution solve() {
    using Perm = std::array<int, 5>;
    Perm base{0, 1, 2, 3, 4};

    Perm colors, nations, pets, drinks, hobbies;

    // Enumerate nations first; constrain Norwegian in first house
    nations = base;
    do {
        if (nations[0] != NORWEGIAN) continue;

        // Enumerate colors; apply color-specific constraints early
        colors = base;
        do {
            // 6. Green to the right of Ivory
            int idx_green = std::find(colors.begin(), colors.end(), GREEN) - colors.begin();
            int idx_ivory = std::find(colors.begin(), colors.end(), IVORY) - colors.begin();
            if (idx_green != idx_ivory + 1) continue;

            // 15. Norwegian lives next to blue house
            int idx_blue = std::find(colors.begin(), colors.end(), BLUE) - colors.begin();
            if (std::abs(idx_blue - 0) != 1) continue;

            // 2. Englishman -> red
            bool ok = true;
            for (int h = 0; h < 5 && ok; ++h)
                if (nations[h] == ENGLISHMAN && colors[h] != RED) ok = false;
            if (!ok) continue;

            // Enumerate drinks; 9. milk in middle
            drinks = base;
            do {
                if (drinks[2] != MILK) continue;

                // 4. green -> coffee
                if (drinks[idx_green] != COFFEE) continue;

                // 5. Ukrainian -> tea
                int idx_ukrainian = std::find(nations.begin(), nations.end(), UKRAINIAN) - nations.begin();
                if (drinks[idx_ukrainian] != TEA) continue;

                // Enumerate hobbies
                hobbies = base;
                do {
                    // 8. yellow -> painter
                    int idx_yellow = std::find(colors.begin(), colors.end(), YELLOW) - colors.begin();
                    if (hobbies[idx_yellow] != PAINTING) continue;

                    // 14. Japanese -> chess
                    int idx_japanese = std::find(nations.begin(), nations.end(), JAPANESE) - nations.begin();
                    if (hobbies[idx_japanese] != CHESS) continue;

                    // 13. football -> orange juice
                    bool good = true;
                    for (int h = 0; h < 5 && good; ++h)
                        if (hobbies[h] == FOOTBALL && drinks[h] != ORANGE_JUICE) good = false;
                    if (!good) continue;

                    // Enumerate pets
                    pets = base;
                    do {
                        // 3. Spaniard -> dog
                        int idx_spaniard = std::find(nations.begin(), nations.end(), SPANIARD) - nations.begin();
                        if (pets[idx_spaniard] != DOG) continue;

                        // 7. snail -> dancing
                        bool ok2 = true;
                        for (int h = 0; h < 5 && ok2; ++h)
                            if (pets[h] == SNAIL && hobbies[h] != DANCING) ok2 = false;
                        if (!ok2) continue;

                        // 11. reading next to fox
                        for (int h = 0; h < 5 && ok2; ++h)
                            if (hobbies[h] == READING) {
                                bool fox_adjacent = (h > 0 && pets[h - 1] == FOX) ||
                                                    (h < 4 && pets[h + 1] == FOX);
                                ok2 = fox_adjacent;
                            }
                        if (!ok2) continue;

                        // 12. painter next to horse
                        for (int h = 0; h < 5 && ok2; ++h)
                            if (hobbies[h] == PAINTING) {
                                bool horse_adjacent = (h > 0 && pets[h - 1] == HORSE) ||
                                                      (h < 4 && pets[h + 1] == HORSE);
                                ok2 = horse_adjacent;
                            }
                        if (!ok2) continue;

                        // All constraints satisfied: build solution
                        int idx_water = std::find(drinks.begin(), drinks.end(), WATER) - drinks.begin();
                        int idx_zebra = std::find(pets.begin(), pets.end(), ZEBRA) - pets.begin();

                        Solution sol;
                        sol.drinksWater = nation_names[nations[idx_water]];
                        sol.ownsZebra = nation_names[nations[idx_zebra]];
                        return sol;
                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(colors.begin(), colors.end()));
    } while (std::next_permutation(nations.begin(), nations.end()));

    // Should never reach here for a well-formed puzzle
    return {};
}

}  // namespace zebra_puzzle

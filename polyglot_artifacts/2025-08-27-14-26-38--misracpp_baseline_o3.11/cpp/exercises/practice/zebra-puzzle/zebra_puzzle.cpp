#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>

namespace zebra_puzzle {

namespace {

/* Enumerations for each attribute set */
enum Color   { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT };
enum Nation  { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE, NATION_COUNT };
enum Pet     { DOG, SNAILS, FOX, HORSE, ZEBRA, PET_COUNT };
enum Drink   { COFFEE, TEA, MILK, ORANGE_JUICE, WATER, DRINK_COUNT };
enum Hobby   { DANCING, PAINTING, READING, FOOTBALL, CHESS, HOBBY_COUNT };

template <typename Arr, typename T>
inline int index_of(const Arr& a, T value) {
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        if (a[i] == value) return i;
    }
    return -1; // should never happen in valid permutations
}

} // namespace

Solution solve() {
    using Array = std::array<int, 5>;
    Array colors{RED, GREEN, IVORY, YELLOW, BLUE};
    Array nations{ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE};
    Array pets{DOG, SNAILS, FOX, HORSE, ZEBRA};
    Array drinks{COFFEE, TEA, MILK, ORANGE_JUICE, WATER};
    Array hobbies{DANCING, PAINTING, READING, FOOTBALL, CHESS};

    /* Permute colors first and apply color-only constraints */
    std::sort(colors.begin(), colors.end());
    do {
        int green = index_of(colors, GREEN);
        int ivory = index_of(colors, IVORY);
        /* 6. The green house is immediately to the right of the ivory house. */
        if (green != ivory + 1) continue;

        /* Permute nations next. */
        std::sort(nations.begin(), nations.end());
        do {
            /* 10. The Norwegian lives in the first house. */
            if (nations[0] != NORWEGIAN) continue;
            /* 2. The Englishman lives in the red house. */
            if (colors[index_of(nations, ENGLISHMAN)] != RED) continue;
            /* 15. The Norwegian lives next to the blue house. */
            if (std::abs(index_of(colors, BLUE) - 0) != 1) continue;

            /* Permute pets. */
            std::sort(pets.begin(), pets.end());
            do {
                /* 3. The Spaniard owns the dog. */
                if (index_of(nations, SPANIARD) != index_of(pets, DOG)) continue;

                /* Permute drinks. */
                std::sort(drinks.begin(), drinks.end());
                do {
                    /* 9. The person in the middle house drinks milk. */
                    if (drinks[2] != MILK) continue;
                    /* 4. The person in the green house drinks coffee. */
                    if (drinks[green] != COFFEE) continue;
                    /* 5. The Ukrainian drinks tea. */
                    if (drinks[index_of(nations, UKRAINIAN)] != TEA) continue;
                    /* 13. The person who plays football drinks orange juice. */
                    /* can't test yet – need hobbies */

                    /* Permute hobbies. */
                    std::sort(hobbies.begin(), hobbies.end());
                    do {
                        /* 7. The snail owner likes to go dancing. */
                        if (hobbies[index_of(pets, SNAILS)] != DANCING) continue;
                        /* 8. The person in the yellow house is a painter. */
                        if (hobbies[index_of(colors, YELLOW)] != PAINTING) continue;
                        /* 12. The painter's house is next to the house with the horse. */
                        if (std::abs(index_of(hobbies, PAINTING) - index_of(pets, HORSE)) != 1) continue;
                        /* 11. The person who enjoys reading lives in the house next to the person with the fox. */
                        if (std::abs(index_of(hobbies, READING) - index_of(pets, FOX)) != 1) continue;
                        /* 13. The person who plays football drinks orange juice. */
                        if (drinks[index_of(hobbies, FOOTBALL)] != ORANGE_JUICE) continue;
                        /* 14. The Japanese person plays chess. */
                        if (hobbies[index_of(nations, JAPANESE)] != CHESS) continue;

                        /* All constraints satisfied – build solution */
                        std::string nation_names[NATION_COUNT]{
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        Solution sol;
                        sol.drinksWater = nation_names[nations[index_of(drinks, WATER)]];
                        sol.ownsZebra   = nation_names[nations[index_of(pets, ZEBRA)]];
                        return sol;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(drinks.begin(), drinks.end()));
            } while (std::next_permutation(pets.begin(), pets.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    /* No solution found – should never happen for this puzzle */
    return {};
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>  // for std::abs(int) overload

namespace zebra_puzzle {

// Return the position of `value` inside `arr` (0-based index).
template <typename T, std::size_t N>
static int index_of(const std::array<T, N>& arr, T value) {
    return static_cast<int>(std::find(arr.begin(), arr.end(), value) - arr.begin());
}

Solution solve() {
    enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Color       { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Pet         { DOG, SNAIL, FOX, HORSE, ZEBRA };
    enum Drink       { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    enum Hobby       { PAINTING, READING, DANCING, FOOTBALL, CHESS };

    const std::array<std::string, 5> nat_name{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    std::array<int, 5> nationality{}, color{}, drink{}, pet{}, hobby{};

    // 1. Nationality permutations (Norwegian fixed in first house).
    std::vector<int> nat_perm{ENGLISHMAN, SPANIARD, UKRAINIAN, JAPANESE};
    std::sort(nat_perm.begin(), nat_perm.end());
    do {
        nationality[0] = NORWEGIAN;
        for (int i = 0; i < 4; ++i) nationality[i + 1] = nat_perm[i];

        // 2. Colors.
        std::vector<int> col_perm{RED, GREEN, IVORY, YELLOW, BLUE};
        std::sort(col_perm.begin(), col_perm.end());
        do {
            for (int i = 0; i < 5; ++i) color[i] = col_perm[i];

            // 2. Englishman lives in red house.
            if (color[index_of(nationality, static_cast<int>(ENGLISHMAN))] != RED) continue;

            // 6. Green immediately right of ivory.
            int green = index_of(color, static_cast<int>(GREEN));
            if (green != index_of(color, static_cast<int>(IVORY)) + 1) continue;

            // 15. Norwegian next to blue.
            if (std::abs(index_of(color, static_cast<int>(BLUE)) - 0) != 1) continue;

            // 3. Drinks.
            std::vector<int> drink_perm{COFFEE, TEA, MILK, ORANGE_JUICE, WATER};
            std::sort(drink_perm.begin(), drink_perm.end());
            do {
                for (int i = 0; i < 5; ++i) drink[i] = drink_perm[i];

                if (drink[green] != COFFEE) continue;                         // 4
                if (drink[index_of(nationality, static_cast<int>(UKRAINIAN))] != TEA) continue; // 5
                if (drink[2] != MILK) continue;                               // 9

                // 4. Pets.
                std::vector<int> pet_perm{DOG, SNAIL, FOX, HORSE, ZEBRA};
                std::sort(pet_perm.begin(), pet_perm.end());
                do {
                    for (int i = 0; i < 5; ++i) pet[i] = pet_perm[i];

                    if (pet[index_of(nationality, static_cast<int>(SPANIARD))] != DOG) continue; // 3

                    // 5. Hobbies.
                    std::vector<int> hob_perm{PAINTING, READING, DANCING, FOOTBALL, CHESS};
                    std::sort(hob_perm.begin(), hob_perm.end());
                    do {
                        for (int i = 0; i < 5; ++i) hobby[i] = hob_perm[i];

                        if (hobby[index_of(color, static_cast<int>(YELLOW))] != PAINTING) continue;        // 8
                        if (hobby[index_of(pet, static_cast<int>(SNAIL))] != DANCING) continue;            // 7
                        if (drink[index_of(hobby, static_cast<int>(FOOTBALL))] != ORANGE_JUICE) continue;  // 13
                        if (hobby[index_of(nationality, static_cast<int>(JAPANESE))] != CHESS) continue;   // 14
                        if (std::abs(index_of(hobby, static_cast<int>(READING)) - index_of(pet, static_cast<int>(FOX))) != 1) continue; // 11
                        if (std::abs(index_of(hobby, static_cast<int>(PAINTING)) - index_of(pet, static_cast<int>(HORSE))) != 1) continue; //12

                        Solution s;
                        s.drinksWater = nat_name[nationality[index_of(drink, static_cast<int>(WATER))]];
                        s.ownsZebra   = nat_name[nationality[index_of(pet, static_cast<int>(ZEBRA))]];
                        return s;
                    } while (std::next_permutation(hob_perm.begin(), hob_perm.end()));
                } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));
            } while (std::next_permutation(drink_perm.begin(), drink_perm.end()));
        } while (std::next_permutation(col_perm.begin(), col_perm.end()));
    } while (std::next_permutation(nat_perm.begin(), nat_perm.end()));

    return {}; // Should never reach here.
}

} // namespace zebra_puzzle

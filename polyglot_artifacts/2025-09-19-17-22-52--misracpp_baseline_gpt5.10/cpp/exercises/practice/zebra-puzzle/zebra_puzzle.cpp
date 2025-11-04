#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>

namespace zebra_puzzle {

namespace {

constexpr int N = 5;

enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nation { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

inline bool adjacent(int a, int b) {
    int d = a - b;
    return d == 1 || d == -1;
}

inline const char* nation_name(int n) {
    switch (n) {
        case ENGLISHMAN: return "Englishman";
        case SPANIARD: return "Spaniard";
        case UKRAINIAN: return "Ukrainian";
        case NORWEGIAN: return "Norwegian";
        case JAPANESE: return "Japanese";
        default: return "";
    }
}

}  // namespace

Solution solve() {
    using std::array;

    array<int, N> base = {0, 1, 2, 3, 4};

    array<int, N> color, nation, drink, hobby, pet;

    // Colors with rule 6 (green immediately right of ivory)
    color = base;
    do {
        if (color[GREEN] != color[IVORY] + 1) continue;

        // Nations with rules 2, 10, 15
        nation = base;
        do {
            if (nation[NORWEGIAN] != 0) continue;                           // 10
            if (nation[ENGLISHMAN] != color[RED]) continue;                 // 2
            if (!adjacent(nation[NORWEGIAN], color[BLUE])) continue;        // 15

            // Drinks with rules 4, 5, 9
            drink = base;
            do {
                if (drink[MILK] != 2) continue;                             // 9
                if (drink[COFFEE] != color[GREEN]) continue;                // 4
                if (drink[TEA] != nation[UKRAINIAN]) continue;              // 5

                // Hobbies with rules 8, 13, 14
                hobby = base;
                do {
                    if (hobby[PAINTER] != color[YELLOW]) continue;          // 8
                    if (hobby[CHESS] != nation[JAPANESE]) continue;         // 14
                    if (hobby[FOOTBALL] != drink[ORANGE_JUICE]) continue;   // 13

                    // Pets with rules 3, 7, 11, 12
                    pet = base;
                    do {
                        if (pet[DOG] != nation[SPANIARD]) continue;         // 3
                        if (pet[SNAILS] != hobby[DANCING]) continue;        // 7
                        if (!adjacent(hobby[READING], pet[FOX])) continue;  // 11
                        if (!adjacent(hobby[PAINTER], pet[HORSE])) continue;// 12

                        // Found solution
                        int water_pos = drink[WATER];
                        int zebra_pos = pet[ZEBRA];

                        int water_nation = -1;
                        int zebra_nation = -1;
                        for (int i = 0; i < N; ++i) {
                            if (nation[i] == water_pos) water_nation = i;
                            if (nation[i] == zebra_pos) zebra_nation = i;
                        }

                        Solution s;
                        s.drinksWater = nation_name(water_nation);
                        s.ownsZebra = nation_name(zebra_nation);
                        return s;

                    } while (std::next_permutation(pet.begin(), pet.end()));
                } while (std::next_permutation(hobby.begin(), hobby.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nation.begin(), nation.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // No solution found (should not happen for the classic puzzle)
    return Solution{};
}

}  // namespace zebra_puzzle

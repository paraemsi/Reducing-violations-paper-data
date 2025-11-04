#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cmath>
#include <string>

namespace zebra_puzzle {

enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, JAPANESE, NORWEGIAN };
enum Pet { DOG, FOX, ZEBRA, HORSE, SNAILS };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS };

static const char* kNationalityNames[5] = {
    "Englishman", "Spaniard", "Ukrainian", "Japanese", "Norwegian"};

static inline bool next_to(int a, int b) { return std::abs(a - b) == 1; }

Solution solve() {
    using Arr = std::array<int, 5>;

    // Base permutation [0,1,2,3,4]
    Arr base = {0, 1, 2, 3, 4};

    // Iterate over color placements (value -> position)
    Arr color = base;
    do {
        // Constraint 6: green is immediately to the right of ivory
        if (color[GREEN] != color[IVORY] + 1) continue;

        // Iterate over nationalities
        Arr nat = base;
        do {
            // Constraint 10: Norwegian in the first house (index 0)
            if (nat[NORWEGIAN] != 0) continue;

            // Constraint 2: Englishman lives in the red house
            if (nat[ENGLISHMAN] != color[RED]) continue;

            // Constraint 15: Norwegian lives next to the blue house
            if (!next_to(nat[NORWEGIAN], color[BLUE])) continue;

            // Drinks setup
            // Constraint 9: Middle house (index 2) drinks milk
            // Constraint 4: Green house drinks coffee
            // Constraint 5: Ukrainian drinks tea
            int drink_pos[5] = {-1, -1, -1, -1, -1};
            bool used_pos[5] = {false, false, false, false, false};

            auto mark_pos = [&](int p) -> bool {
                if (p < 0 || p >= 5 || used_pos[p]) return false;
                used_pos[p] = true;
                return true;
            };

            drink_pos[MILK] = 2;
            if (!mark_pos(drink_pos[MILK])) continue;

            drink_pos[COFFEE] = color[GREEN];
            if (!mark_pos(drink_pos[COFFEE])) continue;

            drink_pos[TEA] = nat[UKRAINIAN];
            if (!mark_pos(drink_pos[TEA])) continue;

            // Remaining positions go to ORANGE_JUICE and WATER
            int rem_pos[2];
            int rsz = 0;
            for (int p = 0; p < 5; ++p) {
                if (!used_pos[p]) rem_pos[rsz++] = p;
            }
            if (rsz != 2) continue;

            for (int swap = 0; swap < 2; ++swap) {
                int pos_oj = rem_pos[swap];
                int pos_water = rem_pos[1 - swap];

                drink_pos[ORANGE_JUICE] = pos_oj;
                drink_pos[WATER] = pos_water;

                // Hobbies setup with constraints:
                // 8: Yellow house -> painter
                // 14: Japanese -> chess
                // 13: Football -> orange juice
                int hobby_pos[5] = {-1, -1, -1, -1, -1};
                bool h_used[5] = {false, false, false, false, false};

                auto mark_h = [&](int p) -> bool {
                    if (p < 0 || p >= 5 || h_used[p]) return false;
                    h_used[p] = true;
                    return true;
                };

                hobby_pos[PAINTING] = color[YELLOW];
                if (!mark_h(hobby_pos[PAINTING])) continue;

                hobby_pos[CHESS] = nat[JAPANESE];
                if (!mark_h(hobby_pos[CHESS])) continue;

                hobby_pos[FOOTBALL] = drink_pos[ORANGE_JUICE];
                if (!mark_h(hobby_pos[FOOTBALL])) continue;

                // Remaining two hobbies: DANCING and READING
                int h_rem_pos[2];
                int hsz = 0;
                for (int p = 0; p < 5; ++p) {
                    if (!h_used[p]) h_rem_pos[hsz++] = p;
                }
                if (hsz != 2) continue;

                for (int hswap = 0; hswap < 2; ++hswap) {
                    hobby_pos[DANCING] = h_rem_pos[hswap];
                    hobby_pos[READING] = h_rem_pos[1 - hswap];

                    // Pets permutations with constraints:
                    // 3: Spaniard owns the dog
                    // 7: Snail owner likes dancing
                    // 11: Reader next to fox
                    // 12: Painter next to horse
                    Arr pet = base;
                    do {
                        if (pet[DOG] != nat[SPANIARD]) continue;
                        if (pet[SNAILS] != hobby_pos[DANCING]) continue;
                        if (!next_to(hobby_pos[READING], pet[FOX])) continue;
                        if (!next_to(hobby_pos[PAINTING], pet[HORSE])) continue;

                        // Found valid solution
                        // Determine nationality who drinks water
                        int water_pos = drink_pos[WATER];
                        int zebra_pos = pet[ZEBRA];

                        int water_nat = -1;
                        int zebra_nat = -1;
                        for (int i = 0; i < 5; ++i) {
                            if (nat[i] == water_pos) water_nat = i;
                            if (nat[i] == zebra_pos) zebra_nat = i;
                        }

                        Solution sol;
                        sol.drinksWater = kNationalityNames[water_nat];
                        sol.ownsZebra = kNationalityNames[zebra_nat];
                        return sol;

                    } while (std::next_permutation(pet.begin(), pet.end()));
                }
            }

        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Should never reach here for a well-formed puzzle; return empty if no solution.
    return Solution{};
}

}  // namespace zebra_puzzle

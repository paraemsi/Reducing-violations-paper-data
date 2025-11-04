#include "zebra_puzzle.h"

#include <array>
#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace zebra_puzzle {

namespace {

// Enumerations for attribute indices
enum Color { RED, GREEN, IVORY, YELLOW, BLUE, COLOR_COUNT };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE, NATIONALITY_COUNT };
enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA, PET_COUNT };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER, DRINK_COUNT };
enum Hobby { PAINTER, DANCING, READING, FOOTBALL, CHESS, HOBBY_COUNT };

template <std::size_t N>
using Permutation = std::array<int, N>;

// Helper to iterate over all permutations of 0..4 with early-exit support
template <std::size_t N, typename Func>
bool for_each_permutation(Func &&func) {
    Permutation<N> perm{0, 1, 2, 3, 4};
    do {
        if (func(perm)) {
            return true;  // stop when func returns true
        }
    } while (std::next_permutation(perm.begin(), perm.end()));
    return false;
}

inline bool is_next_to(int a, int b) { return std::abs(a - b) == 1; }

}  // namespace

Solution solve() {
    Solution result;

    // 1st loop: colours (only 24 permutations satisfy #6)
    for_each_permutation<COLOR_COUNT>([&](const Permutation<COLOR_COUNT> &color_pos) {
        // 6. Green is immediately to the right of Ivory
        if (color_pos[GREEN] != color_pos[IVORY] + 1) return false;

        // 2nd loop: nationalities
        return for_each_permutation<NATIONALITY_COUNT>(
            [&](const Permutation<NATIONALITY_COUNT> &nat_pos) {
                // 2. Englishman lives in red house
                if (nat_pos[ENGLISHMAN] != color_pos[RED]) return false;
                // 10. Norwegian in the first house
                if (nat_pos[NORWEGIAN] != 0) return false;
                // 15. Norwegian next to blue house
                if (!is_next_to(nat_pos[NORWEGIAN], color_pos[BLUE])) return false;

                // 3rd loop: drinks
                return for_each_permutation<DRINK_COUNT>(
                    [&](const Permutation<DRINK_COUNT> &drink_pos) {
                        // 4. Green house drinks coffee
                        if (drink_pos[COFFEE] != color_pos[GREEN]) return false;
                        // 5. Ukrainian drinks tea
                        if (drink_pos[TEA] != nat_pos[UKRAINIAN]) return false;
                        // 9. Middle house drinks milk
                        if (drink_pos[MILK] != 2) return false;

                        // 4th loop: pets
                        return for_each_permutation<PET_COUNT>(
                            [&](const Permutation<PET_COUNT> &pet_pos) {
                                // 3. Spaniard owns the dog
                                if (pet_pos[DOG] != nat_pos[SPANIARD]) return false;

                                // 5th loop: hobbies
                                return for_each_permutation<HOBBY_COUNT>(
                                    [&](const Permutation<HOBBY_COUNT> &hobby_pos) {
                                        // 8. Yellow house's inhabitant is a painter
                                        if (hobby_pos[PAINTER] != color_pos[YELLOW])
                                            return false;
                                        // 7. Snail owner likes dancing
                                        if (hobby_pos[DANCING] != pet_pos[SNAILS]) return false;
                                        // 13. Football player drinks orange juice
                                        if (drink_pos[ORANGE_JUICE] !=
                                            hobby_pos[FOOTBALL])
                                            return false;
                                        // 14. Japanese plays chess
                                        if (hobby_pos[CHESS] != nat_pos[JAPANESE]) return false;
                                        // 11. Reader lives next to fox owner
                                        if (!is_next_to(hobby_pos[READING], pet_pos[FOX]))
                                            return false;
                                        // 12. Painter lives next to horse owner
                                        if (!is_next_to(hobby_pos[PAINTER], pet_pos[HORSE]))
                                            return false;

                                        // All constraints satisfied – derive answer
                                        static const std::array<std::string, NATIONALITY_COUNT>
                                            nat_name{{"Englishman", "Spaniard", "Ukrainian",
                                                      "Norwegian", "Japanese"}};

                                        int water_house = drink_pos[WATER];
                                        int zebra_house = pet_pos[ZEBRA];

                                        for (int i = 0; i < NATIONALITY_COUNT; ++i) {
                                            if (nat_pos[i] == water_house)
                                                result.drinksWater = nat_name[i];
                                            if (nat_pos[i] == zebra_house)
                                                result.ownsZebra = nat_name[i];
                                        }

                                        return true;  // propagate success to break all loops
                                    });
                            });
                    });
            });
    });

    return result;
}

}  // namespace zebra_puzzle

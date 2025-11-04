#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>

namespace zebra_puzzle {

namespace {
constexpr std::size_t HOUSES = static_cast<std::size_t>(5U);

// Indices for categories
// Nationalities
constexpr std::size_t ENG = static_cast<std::size_t>(0U);
constexpr std::size_t SPA = static_cast<std::size_t>(1U);
constexpr std::size_t UKR = static_cast<std::size_t>(2U);
constexpr std::size_t NOR = static_cast<std::size_t>(3U);
constexpr std::size_t JAP = static_cast<std::size_t>(4U);

// Colors
constexpr std::size_t RED    = static_cast<std::size_t>(0U);
constexpr std::size_t GREEN  = static_cast<std::size_t>(1U);
constexpr std::size_t IVORY  = static_cast<std::size_t>(2U);
constexpr std::size_t YELLOW = static_cast<std::size_t>(3U);
constexpr std::size_t BLUE   = static_cast<std::size_t>(4U);

// Pets
constexpr std::size_t DOG   = static_cast<std::size_t>(0U);
constexpr std::size_t SNAIL = static_cast<std::size_t>(1U);
constexpr std::size_t FOX   = static_cast<std::size_t>(2U);
constexpr std::size_t HORSE = static_cast<std::size_t>(3U);
constexpr std::size_t ZEBRA = static_cast<std::size_t>(4U);

// Drinks
constexpr std::size_t COFFEE = static_cast<std::size_t>(0U);
constexpr std::size_t TEA    = static_cast<std::size_t>(1U);
constexpr std::size_t MILK   = static_cast<std::size_t>(2U);
constexpr std::size_t OJ     = static_cast<std::size_t>(3U);
constexpr std::size_t WATER  = static_cast<std::size_t>(4U);

// Hobbies
constexpr std::size_t DANCING  = static_cast<std::size_t>(0U);
constexpr std::size_t PAINTING = static_cast<std::size_t>(1U);
constexpr std::size_t READING  = static_cast<std::size_t>(2U);
constexpr std::size_t CHESS    = static_cast<std::size_t>(3U);
constexpr std::size_t FOOTBALL = static_cast<std::size_t>(4U);

using PosMap = std::array<std::size_t, HOUSES>;

inline std::size_t abs_diff(const std::size_t a, const std::size_t b) {
    return (a > b) ? (a - b) : (b - a);
}

inline std::size_t find_index_at_pos(const PosMap& pos_map, const std::size_t target_pos) {
    for (std::size_t i = static_cast<std::size_t>(0U); (i < HOUSES); ++i) {
        if (pos_map[i] == target_pos) {
            return i;
        }
    }
    return HOUSES;
}

}  // namespace

Solution solve() {
    // Names for final answers (nationalities)
    static const std::array<std::string, HOUSES> kNationalityNames = {
        std::string("Englishman"),
        std::string("Spaniard"),
        std::string("Ukrainian"),
        std::string("Norwegian"),
        std::string("Japanese")
    };

    // Position maps: value -> house index (0..4)
    PosMap pos_color{};
    PosMap pos_drink{};
    PosMap pos_hobby{};
    PosMap pos_pet{};
    PosMap pos_nation{};

    // Pre-assignments from constraints:
    // 10. Norwegian lives in the first house.
    pos_nation[NOR] = static_cast<std::size_t>(0U);

    // 15. Norwegian lives next to the blue house -> with NOR at 0, BLUE must be at 1.
    pos_color[BLUE] = static_cast<std::size_t>(1U);

    // 6. Green is immediately to the right of Ivory -> only possible ivory positions are 2 or 3 (since BLUE is at 1).
    for (std::size_t ivory_pos = static_cast<std::size_t>(2U); (ivory_pos <= static_cast<std::size_t>(3U)); ++ivory_pos) {
        pos_color[IVORY] = ivory_pos;
        pos_color[GREEN] = (ivory_pos + static_cast<std::size_t>(1U));

        // Build used positions for colors
        std::array<bool, HOUSES> used_color_pos{};
        for (std::size_t i = static_cast<std::size_t>(0U); (i < HOUSES); ++i) {
            used_color_pos[i] = false;
        }
        used_color_pos[pos_color[BLUE]] = true;
        used_color_pos[pos_color[IVORY]] = true;
        used_color_pos[pos_color[GREEN]] = true;

        // Assign RED and YELLOW to the remaining two positions
        for (std::size_t red_pos = static_cast<std::size_t>(0U); (red_pos < HOUSES); ++red_pos) {
            if (used_color_pos[red_pos]) {
                continue;
            }
            pos_color[RED] = red_pos;

            used_color_pos[red_pos] = true;
            for (std::size_t yellow_pos = static_cast<std::size_t>(0U); (yellow_pos < HOUSES); ++yellow_pos) {
                if (used_color_pos[yellow_pos]) {
                    continue;
                }
                pos_color[YELLOW] = yellow_pos;

                // Drinks:
                // 9. Middle house drinks milk.
                pos_drink[MILK] = static_cast<std::size_t>(2U);
                // 4. Green house drinks coffee.
                pos_drink[COFFEE] = pos_color[GREEN];

                // Used positions for drinks
                std::array<bool, HOUSES> used_drink_pos{};
                for (std::size_t i = static_cast<std::size_t>(0U); (i < HOUSES); ++i) {
                    used_drink_pos[i] = false;
                }
                used_drink_pos[pos_drink[MILK]] = true;
                used_drink_pos[pos_drink[COFFEE]] = true;

                // Assign TEA, OJ, WATER to remaining positions (3! = 6 permutations)
                for (std::size_t tea_pos = static_cast<std::size_t>(0U); (tea_pos < HOUSES); ++tea_pos) {
                    if (used_drink_pos[tea_pos]) {
                        continue;
                    }
                    pos_drink[TEA] = tea_pos;

                    used_drink_pos[tea_pos] = true;
                    for (std::size_t oj_pos = static_cast<std::size_t>(0U); (oj_pos < HOUSES); ++oj_pos) {
                        if (used_drink_pos[oj_pos]) {
                            continue;
                        }
                        pos_drink[OJ] = oj_pos;

                        used_drink_pos[oj_pos] = true;
                        for (std::size_t water_pos = static_cast<std::size_t>(0U); (water_pos < HOUSES); ++water_pos) {
                            if (used_drink_pos[water_pos]) {
                                continue;
                            }
                            pos_drink[WATER] = water_pos;

                            // Hobbies:
                            // 8. Yellow house is a painter.
                            pos_hobby[PAINTING] = pos_color[YELLOW];
                            // 13. Football player drinks orange juice.
                            pos_hobby[FOOTBALL] = pos_drink[OJ];

                            // Used positions for hobbies
                            std::array<bool, HOUSES> used_hobby_pos{};
                            for (std::size_t i = static_cast<std::size_t>(0U); (i < HOUSES); ++i) {
                                used_hobby_pos[i] = false;
                            }
                            used_hobby_pos[pos_hobby[PAINTING]] = true;
                            used_hobby_pos[pos_hobby[FOOTBALL]] = true;

                            // Assign DANCING, READING, CHESS to remaining positions
                            for (std::size_t dancing_pos = static_cast<std::size_t>(0U); (dancing_pos < HOUSES); ++dancing_pos) {
                                if (used_hobby_pos[dancing_pos]) {
                                    continue;
                                }
                                pos_hobby[DANCING] = dancing_pos;

                                used_hobby_pos[dancing_pos] = true;
                                for (std::size_t reading_pos = static_cast<std::size_t>(0U); (reading_pos < HOUSES); ++reading_pos) {
                                    if (used_hobby_pos[reading_pos]) {
                                        continue;
                                    }
                                    pos_hobby[READING] = reading_pos;

                                    used_hobby_pos[reading_pos] = true;
                                    for (std::size_t chess_pos = static_cast<std::size_t>(0U); (chess_pos < HOUSES); ++chess_pos) {
                                        if (used_hobby_pos[chess_pos]) {
                                            continue;
                                        }
                                        pos_hobby[CHESS] = chess_pos;

                                        // Pets: iterate all permutations via positions array {0,1,2,3,4}
                                        std::array<std::size_t, HOUSES> pet_perm = {
                                            static_cast<std::size_t>(0U),
                                            static_cast<std::size_t>(1U),
                                            static_cast<std::size_t>(2U),
                                            static_cast<std::size_t>(3U),
                                            static_cast<std::size_t>(4U)
                                        };

                                        do {
                                            // Map permutation to pet positions
                                            pos_pet[DOG]   = pet_perm[DOG];
                                            pos_pet[SNAIL] = pet_perm[SNAIL];
                                            pos_pet[FOX]   = pet_perm[FOX];
                                            pos_pet[HORSE] = pet_perm[HORSE];
                                            pos_pet[ZEBRA] = pet_perm[ZEBRA];

                                            // 11. Reader lives next to fox.
                                            if (abs_diff(pos_hobby[READING], pos_pet[FOX]) != static_cast<std::size_t>(1U)) {
                                                continue;
                                            }
                                            // 12. Painter's house is next to the house with the horse.
                                            if (abs_diff(pos_hobby[PAINTING], pos_pet[HORSE]) != static_cast<std::size_t>(1U)) {
                                                continue;
                                            }
                                            // 7. Snail owner likes to go dancing.
                                            if (pos_pet[SNAIL] != pos_hobby[DANCING]) {
                                                continue;
                                            }

                                            // Nationalities mapping with constraints
                                            // Ensure uniqueness of positions
                                            std::array<bool, HOUSES> used_nat_pos{};
                                            for (std::size_t i = static_cast<std::size_t>(0U); (i < HOUSES); ++i) {
                                                used_nat_pos[i] = false;
                                            }

                                            pos_nation[NOR] = static_cast<std::size_t>(0U);
                                            used_nat_pos[pos_nation[NOR]] = true;

                                            // 2. Englishman lives in the red house.
                                            pos_nation[ENG] = pos_color[RED];
                                            if (used_nat_pos[pos_nation[ENG]]) {
                                                continue;
                                            }
                                            used_nat_pos[pos_nation[ENG]] = true;

                                            // 5. Ukrainian drinks tea.
                                            pos_nation[UKR] = pos_drink[TEA];
                                            if (used_nat_pos[pos_nation[UKR]]) {
                                                continue;
                                            }
                                            used_nat_pos[pos_nation[UKR]] = true;

                                            // 14. Japanese person plays chess.
                                            pos_nation[JAP] = pos_hobby[CHESS];
                                            if (used_nat_pos[pos_nation[JAP]]) {
                                                continue;
                                            }
                                            used_nat_pos[pos_nation[JAP]] = true;

                                            // 3. Spaniard owns the dog.
                                            pos_nation[SPA] = pos_pet[DOG];
                                            if (used_nat_pos[pos_nation[SPA]]) {
                                                continue;
                                            }
                                            used_nat_pos[pos_nation[SPA]] = true;

                                            // 15. Norwegian lives next to the blue house. (Re-check)
                                            if (abs_diff(pos_nation[NOR], pos_color[BLUE]) != static_cast<std::size_t>(1U)) {
                                                continue;
                                            }

                                            // 4 already enforced via drinks/green
                                            // All constraints satisfied; build solution.
                                            const std::size_t water_pos = pos_drink[WATER];
                                            const std::size_t zebra_pos = pos_pet[ZEBRA];

                                            const std::size_t water_nat = find_index_at_pos(pos_nation, water_pos);
                                            const std::size_t zebra_nat = find_index_at_pos(pos_nation, zebra_pos);

                                            if ((water_nat < HOUSES) && (zebra_nat < HOUSES)) {
                                                if ((water_nat == NOR)) {
                                                    Solution sol{};
                                                    sol.drinksWater = kNationalityNames[water_nat];
                                                    sol.ownsZebra = kNationalityNames[zebra_nat];
                                                    return sol;
                                                }
                                            }
                                        } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));
                                    }
                                    used_hobby_pos[reading_pos] = false;
                                }
                                used_hobby_pos[dancing_pos] = false;
                            }
                        }
                        used_drink_pos[oj_pos] = false;
                    }
                    used_drink_pos[tea_pos] = false;
                }
            }
            used_color_pos[red_pos] = false;
        }
    }

    // Fallback (should not happen for this puzzle)
    Solution empty{};
    empty.drinksWater = std::string();
    empty.ownsZebra = std::string();
    return empty;
}

}  // namespace zebra_puzzle

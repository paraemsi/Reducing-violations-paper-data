#include "zebra_puzzle.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {

 // Use a fixed-width unsigned type per MISRA for indices 0..4.
using Index = std::uint32_t;
using Perm = std::array<Index, 5U>;

static constexpr Index HOUSES = static_cast<Index>(5U);

// Attribute indices (kept as Index constants to avoid implicit signed/unsigned conversions).
// Colors
static constexpr Index RED = static_cast<Index>(0U);
static constexpr Index GREEN = static_cast<Index>(1U);
static constexpr Index IVORY = static_cast<Index>(2U);
static constexpr Index YELLOW = static_cast<Index>(3U);
static constexpr Index BLUE = static_cast<Index>(4U);

// Nationalities
static constexpr Index ENGLISH = static_cast<Index>(0U);
static constexpr Index SPANIARD = static_cast<Index>(1U);
static constexpr Index UKRAINIAN = static_cast<Index>(2U);
static constexpr Index NORWEGIAN = static_cast<Index>(3U);
static constexpr Index JAPANESE = static_cast<Index>(4U);

// Drinks
static constexpr Index COFFEE = static_cast<Index>(0U);
static constexpr Index TEA = static_cast<Index>(1U);
static constexpr Index MILK = static_cast<Index>(2U);
static constexpr Index ORANGE_JUICE = static_cast<Index>(3U);
static constexpr Index WATER = static_cast<Index>(4U);

// Pets
static constexpr Index DOG = static_cast<Index>(0U);
static constexpr Index SNAILS = static_cast<Index>(1U);
static constexpr Index FOX = static_cast<Index>(2U);
static constexpr Index HORSE = static_cast<Index>(3U);
static constexpr Index ZEBRA = static_cast<Index>(4U);

// Hobbies
static constexpr Index READING = static_cast<Index>(0U);
static constexpr Index DANCING = static_cast<Index>(1U);
static constexpr Index PAINTING = static_cast<Index>(2U);
static constexpr Index FOOTBALL = static_cast<Index>(3U);
static constexpr Index CHESS = static_cast<Index>(4U);

static constexpr Index FIRST_POS = static_cast<Index>(0U);
static constexpr Index SECOND_POS = static_cast<Index>(1U);
static constexpr Index MIDDLE_POS = static_cast<Index>(2U);

// Absolute difference for Index (size_t) without going negative.
inline Index absdiff(Index const a, Index const b) {
    if (a > b) {
        return (a - b);
    } else {
        return (b - a);
    }
}

// Generate all permutations of [0,1,2,3,4] as arrays where perm[value] = position.
void gen_all_perms_rec(Index pos, Perm &cur, std::array<bool, 5U> &used, std::vector<Perm> &out) {
    if (pos == HOUSES) {
        out.push_back(cur);
        return;
    }
    for (Index i = static_cast<Index>(0U); i < HOUSES; ++i) {
        if (!used[i]) {
            used[i] = true;
            cur[pos] = i;
            gen_all_perms_rec(static_cast<Index>(pos + static_cast<Index>(1U)), cur, used, out);
            used[i] = false;
        }
    }
}

std::vector<Perm> gen_all_perms() {
    std::vector<Perm> out;
    out.reserve(120U);
    Perm cur{};
    std::array<bool, 5U> used{};
    for (Index i = static_cast<Index>(0U); i < HOUSES; ++i) {
        used[i] = false;
    }
    gen_all_perms_rec(static_cast<Index>(0U), cur, used, out);
    return out;
}

// Helper to map nationality index to its name.
const std::array<const char *, 5U> &nationality_names() {
    static const std::array<const char *, 5U> names = {
        "Englishman",
        "Spaniard",
        "Ukrainian",
        "Norwegian",
        "Japanese"
    };
    return names;
}

}  // namespace

Solution solve() {
    // Precompute all permutations once.
    const std::vector<Perm> all_perms = gen_all_perms();

    // Filter colors: green immediately right of ivory, and blue is at position 1 (due to Norwegian in first house).
    std::vector<Perm> color_perms;
    for (const Perm &c : all_perms) {
        if ((c[GREEN] == (c[IVORY] + static_cast<Index>(1U))) && (c[BLUE] == SECOND_POS)) {
            color_perms.push_back(c);
        }
    }

    // Filter nationalities: Norwegian lives in the first house.
    std::vector<Perm> nat_perms;
    for (const Perm &n : all_perms) {
        if (n[NORWEGIAN] == FIRST_POS) {
            nat_perms.push_back(n);
        }
    }

    // Filter drinks: Milk in the middle house.
    std::vector<Perm> drink_perms;
    for (const Perm &d : all_perms) {
        if (d[MILK] == MIDDLE_POS) {
            drink_perms.push_back(d);
        }
    }

    // Pets and hobbies use all permutations; constraints applied later.
    const std::vector<Perm> &pet_perms = all_perms;
    const std::vector<Perm> &hobby_perms = all_perms;

    // Now search with incremental pruning across categories.
    for (const Perm &colors : color_perms) {
        const Index red_pos = colors[RED];
        const Index green_pos = colors[GREEN];
        const Index yellow_pos = colors[YELLOW];
        const Index blue_pos = colors[BLUE];

        for (const Perm &nats : nat_perms) {
            // 2. The Englishman lives in the red house.
            if (nats[ENGLISH] != red_pos) {
                continue;
            }
            // 15. The Norwegian lives next to the blue house.
            if (absdiff(nats[NORWEGIAN], blue_pos) != static_cast<Index>(1U)) {
                continue;
            }

            for (const Perm &drinks : drink_perms) {
                // 4. The person in the green house drinks coffee.
                if (drinks[COFFEE] != green_pos) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                if (drinks[TEA] != nats[UKRAINIAN]) {
                    continue;
                }

                for (const Perm &pets : pet_perms) {
                    // 3. The Spaniard owns the dog.
                    if (pets[DOG] != nats[SPANIARD]) {
                        continue;
                    }

                    for (const Perm &hobbies : hobby_perms) {
                        // 7. The snail owner likes to go dancing.
                        if (hobbies[DANCING] != pets[SNAILS]) {
                            continue;
                        }
                        // 8. The person in the yellow house is a painter.
                        if (hobbies[PAINTING] != yellow_pos) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (absdiff(hobbies[READING], pets[FOX]) != static_cast<Index>(1U)) {
                            continue;
                        }
                        // 12. The painter's house is next to the house with the horse.
                        if (absdiff(hobbies[PAINTING], pets[HORSE]) != static_cast<Index>(1U)) {
                            continue;
                        }
                        // 13. The person who plays football drinks orange juice.
                        if (drinks[ORANGE_JUICE] != hobbies[FOOTBALL]) {
                            continue;
                        }
                        // 14. The Japanese person plays chess.
                        if (nats[JAPANESE] != hobbies[CHESS]) {
                            continue;
                        }

                        // All constraints satisfied -> extract solution.
                        const Index water_pos = drinks[WATER];
                        const Index zebra_pos = pets[ZEBRA];

                        // Find nationalities at those positions.
                        Index water_nat = static_cast<Index>(0U);
                        Index zebra_nat = static_cast<Index>(0U);
                        for (Index ni = static_cast<Index>(0U); ni < HOUSES; ++ni) {
                            if (nats[ni] == water_pos) {
                                water_nat = ni;
                            }
                            if (nats[ni] == zebra_pos) {
                                zebra_nat = ni;
                            }
                        }

                        const auto &names = nationality_names();
                        Solution sol{};
                        sol.drinksWater = std::string(names[water_nat]);
                        sol.ownsZebra = std::string(names[zebra_nat]);
                        return sol;
                    }
                }
            }
        }
    }

    // If not found (should not happen for a correct puzzle), return empty strings.
    Solution fallback{};
    fallback.drinksWater = std::string();
    fallback.ownsZebra = std::string();
    return fallback;
}

}  // namespace zebra_puzzle

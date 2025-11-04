#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {
using u8 = std::uint8_t;
constexpr u8 N = static_cast<u8>(5U);

using Perm = std::array<u8, static_cast<std::size_t>(N)>;

// Indices for each category (0..4)
constexpr u8 EN = static_cast<u8>(0U);
constexpr u8 SP = static_cast<u8>(1U);
constexpr u8 UA = static_cast<u8>(2U);
constexpr u8 NO = static_cast<u8>(3U);
constexpr u8 JA = static_cast<u8>(4U);

constexpr u8 RE = static_cast<u8>(0U);
constexpr u8 GR = static_cast<u8>(1U);
constexpr u8 IV = static_cast<u8>(2U);
constexpr u8 YE = static_cast<u8>(3U);
constexpr u8 BL = static_cast<u8>(4U);

constexpr u8 CF = static_cast<u8>(0U);
constexpr u8 TE = static_cast<u8>(1U);
constexpr u8 MK = static_cast<u8>(2U);
constexpr u8 OJ = static_cast<u8>(3U);
constexpr u8 WA = static_cast<u8>(4U);

constexpr u8 DG = static_cast<u8>(0U);
constexpr u8 SN = static_cast<u8>(1U);
constexpr u8 FX = static_cast<u8>(2U);
constexpr u8 HS = static_cast<u8>(3U);
constexpr u8 ZB = static_cast<u8>(4U);

constexpr u8 DN = static_cast<u8>(0U);
constexpr u8 PT = static_cast<u8>(1U);
constexpr u8 RD = static_cast<u8>(2U);
constexpr u8 FB = static_cast<u8>(3U);
constexpr u8 CH = static_cast<u8>(4U);

inline bool is_adjacent(u8 a, u8 b) {
    // Return true if positions a and b are exactly 1 apart
    return ((a > b) ? ((static_cast<u8>(a - b)) == static_cast<u8>(1U))
                    : ((static_cast<u8>(b - a)) == static_cast<u8>(1U)));
}

inline Perm invert(const Perm& m) {
    Perm inv = {0U, 0U, 0U, 0U, 0U};
    for (u8 i = static_cast<u8>(0U); i < static_cast<u8>(5U); i = static_cast<u8>(i + static_cast<u8>(1U))) {
        inv[static_cast<std::size_t>(m[static_cast<std::size_t>(i)])] = i;
    }
    return inv;
}

}  // namespace

Solution solve() {
    // Base permutation [0,1,2,3,4]
    Perm base = {static_cast<u8>(0U), static_cast<u8>(1U), static_cast<u8>(2U),
                 static_cast<u8>(3U), static_cast<u8>(4U)};

    // Names for output mapping from nationality index to string
    const std::array<std::string, 5U> natNames = {
        std::string("Englishman"),
        std::string("Spaniard"),
        std::string("Ukrainian"),
        std::string("Norwegian"),
        std::string("Japanese"),
    };

    // Colors
    Perm colors = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!(colors[static_cast<std::size_t>(GR)] == static_cast<u8>(colors[static_cast<std::size_t>(IV)] + static_cast<u8>(1U)))) {
            continue;
        }

        // Nationalities
        Perm nat = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (!(nat[static_cast<std::size_t>(NO)] == static_cast<u8>(0U))) {
                continue;
            }
            // 2. The Englishman lives in the red house.
            if (!(nat[static_cast<std::size_t>(EN)] == colors[static_cast<std::size_t>(RE)])) {
                continue;
            }
            // 15. The Norwegian lives next to the blue house.
            if (!is_adjacent(nat[static_cast<std::size_t>(NO)], colors[static_cast<std::size_t>(BL)])) {
                continue;
            }

            // Drinks
            Perm drinks = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (!(drinks[static_cast<std::size_t>(MK)] == static_cast<u8>(2U))) {
                    continue;
                }
                // 4. The person in the green house drinks coffee.
                if (!(colors[static_cast<std::size_t>(GR)] == drinks[static_cast<std::size_t>(CF)])) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                if (!(nat[static_cast<std::size_t>(UA)] == drinks[static_cast<std::size_t>(TE)])) {
                    continue;
                }

                // Pets
                Perm pets = base;
                do {
                    // 3. The Spaniard owns the dog.
                    if (!(nat[static_cast<std::size_t>(SP)] == pets[static_cast<std::size_t>(DG)])) {
                        continue;
                    }

                    // Hobbies
                    Perm hobbies = base;
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (!(pets[static_cast<std::size_t>(SN)] == hobbies[static_cast<std::size_t>(DN)])) {
                            continue;
                        }
                        // 8. The person in the yellow house is a painter.
                        if (!(colors[static_cast<std::size_t>(YE)] == hobbies[static_cast<std::size_t>(PT)])) {
                            continue;
                        }
                        // 13. The person who plays football drinks orange juice.
                        if (!(hobbies[static_cast<std::size_t>(FB)] == drinks[static_cast<std::size_t>(OJ)])) {
                            continue;
                        }
                        // 14. The Japanese person plays chess.
                        if (!(nat[static_cast<std::size_t>(JA)] == hobbies[static_cast<std::size_t>(CH)])) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!is_adjacent(hobbies[static_cast<std::size_t>(RD)], pets[static_cast<std::size_t>(FX)])) {
                            continue;
                        }
                        // 12. The painter's house is next to the house with the horse.
                        if (!is_adjacent(hobbies[static_cast<std::size_t>(PT)], pets[static_cast<std::size_t>(HS)])) {
                            continue;
                        }

                        // Found solution
                        const u8 waterPos = drinks[static_cast<std::size_t>(WA)];
                        const u8 zebraPos = pets[static_cast<std::size_t>(ZB)];
                        const Perm posToNat = invert(nat);

                        const u8 waterNatIdx = posToNat[static_cast<std::size_t>(waterPos)];
                        const u8 zebraNatIdx = posToNat[static_cast<std::size_t>(zebraPos)];

                        Solution sol{};
                        sol.drinksWater = natNames[static_cast<std::size_t>(waterNatIdx)];
                        sol.ownsZebra = natNames[static_cast<std::size_t>(zebraNatIdx)];
                        return sol;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Should never reach here; return default if constraints somehow fail.
    Solution sol{};
    sol.drinksWater = std::string();
    sol.ownsZebra = std::string();
    return sol;
}

}  // namespace zebra_puzzle

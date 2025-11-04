#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {
inline bool is_next(const std::uint32_t a, const std::uint32_t b) noexcept
{
    return (((a > 0U) && ((a - 1U) == b)) || (((a + 1U) < 5U) && ((a + 1U) == b)));
}

inline std::string nationality_name(const std::uint32_t idx)
{
    switch (idx) {
        case 0U: {
            return "Englishman";
        }
        case 1U: {
            return "Spaniard";
        }
        case 2U: {
            return "Ukrainian";
        }
        case 3U: {
            return "Norwegian";
        }
        case 4U: {
            return "Japanese";
        }
        default: {
            return "";
        }
    }
}
}  // namespace

Solution solve()
{
    using std::array;

    // Indices for each category
    constexpr std::uint32_t ENGLISH = 0U;
    constexpr std::uint32_t SPANIARD = 1U;
    constexpr std::uint32_t UKRAINIAN = 2U;
    constexpr std::uint32_t NORWEGIAN = 3U;
    constexpr std::uint32_t JAPANESE = 4U;

    constexpr std::uint32_t RED = 0U;
    constexpr std::uint32_t GREEN = 1U;
    constexpr std::uint32_t IVORY = 2U;
    constexpr std::uint32_t YELLOW = 3U;
    constexpr std::uint32_t BLUE = 4U;

    constexpr std::uint32_t COFFEE = 0U;
    constexpr std::uint32_t TEA = 1U;
    constexpr std::uint32_t MILK = 2U;
    constexpr std::uint32_t ORANGEJUICE = 3U;
    constexpr std::uint32_t WATER = 4U;

    constexpr std::uint32_t DOG = 0U;
    constexpr std::uint32_t SNAILS = 1U;
    constexpr std::uint32_t FOX = 2U;
    constexpr std::uint32_t HORSE = 3U;
    constexpr std::uint32_t ZEBRA = 4U;

    constexpr std::uint32_t DANCING = 0U;
    constexpr std::uint32_t PAINTING = 1U;
    constexpr std::uint32_t READING = 2U;
    constexpr std::uint32_t FOOTBALL = 3U;
    constexpr std::uint32_t CHESS = 4U;

    array<std::uint32_t, 5U> col{{0U, 1U, 2U, 3U, 4U}};
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!((col[GREEN] == (col[IVORY] + 1U)))) {
            continue;
        }

        array<std::uint32_t, 5U> nat{{0U, 1U, 2U, 3U, 4U}};
        do {
            // 10. The Norwegian lives in the first house.
            if (!((nat[NORWEGIAN] == 0U))) {
                continue;
            }
            // 2. The Englishman lives in the red house.
            if (!((nat[ENGLISH] == col[RED]))) {
                continue;
            }
            // 15. The Norwegian lives next to the blue house.
            if (!(is_next(nat[NORWEGIAN], col[BLUE]))) {
                continue;
            }

            array<std::uint32_t, 5U> bev{{0U, 1U, 2U, 3U, 4U}};
            do {
                // 9. The person in the middle house drinks milk.
                if (!((bev[MILK] == 2U))) {
                    continue;
                }
                // 4. The person in the green house drinks coffee.
                if (!((col[GREEN] == bev[COFFEE]))) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                if (!((nat[UKRAINIAN] == bev[TEA]))) {
                    continue;
                }

                array<std::uint32_t, 5U> pet{{0U, 1U, 2U, 3U, 4U}};
                do {
                    // 3. The Spaniard owns the dog.
                    if (!((nat[SPANIARD] == pet[DOG]))) {
                        continue;
                    }

                    array<std::uint32_t, 5U> hob{{0U, 1U, 2U, 3U, 4U}};
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (!((pet[SNAILS] == hob[DANCING]))) {
                            continue;
                        }
                        // 8. The person in the yellow house is a painter.
                        if (!((col[YELLOW] == hob[PAINTING]))) {
                            continue;
                        }
                        // 13. The person who plays football drinks orange juice.
                        if (!((hob[FOOTBALL] == bev[ORANGEJUICE]))) {
                            continue;
                        }
                        // 14. The Japanese person plays chess.
                        if (!((nat[JAPANESE] == hob[CHESS]))) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!(is_next(hob[READING], pet[FOX]))) {
                            continue;
                        }
                        // 12. The painter's house is next to the house with the horse.
                        if (!(is_next(hob[PAINTING], pet[HORSE]))) {
                            continue;
                        }

                        // All constraints satisfied
                        const std::uint32_t pos_water = bev[WATER];
                        const std::uint32_t pos_zebra = pet[ZEBRA];

                        std::uint32_t who_water = 0U;
                        std::uint32_t who_zebra = 0U;

                        for (std::uint32_t n = 0U; (n < 5U); n += 1U) {
                            if ((nat[n] == pos_water)) {
                                who_water = n;
                            }
                            if ((nat[n] == pos_zebra)) {
                                who_zebra = n;
                            }
                        }

                        Solution s{};
                        s.drinksWater = nationality_name(who_water);
                        s.ownsZebra = nationality_name(who_zebra);
                        return s;
                    } while (std::next_permutation(hob.begin(), hob.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(bev.begin(), bev.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(col.begin(), col.end()));

    // Fallback (should never happen if the puzzle is consistent)
    Solution s{};
    s.drinksWater = "";
    s.ownsZebra = "";
    return s;
}

}  // namespace zebra_puzzle

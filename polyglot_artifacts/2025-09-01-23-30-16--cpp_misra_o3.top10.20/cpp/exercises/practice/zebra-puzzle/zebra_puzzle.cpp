#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {

/* Number of houses in the puzzle */
static constexpr std::int32_t HOUSE_COUNT{5};

/* Helpers ----------------------------------------------------------------- */

/* Return true if the two house indices are adjacent */
static bool is_adjacent(std::int32_t a, std::int32_t b) noexcept
{
    return ( ( (a > b) ? (a - b) : (b - a) ) == 1 );
}

/* Convert nationality enum index to its string representation */
static std::string nationality_name(std::int32_t idx)
{
    static const std::array<std::string, HOUSE_COUNT> names{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
    return names[static_cast<std::size_t>(idx)];
}

/* Produce all 5! permutations of {0,1,2,3,4} */
static std::vector<std::array<std::int32_t, HOUSE_COUNT>> permutations()
{
    std::array<std::int32_t, HOUSE_COUNT> base{{0, 1, 2, 3, 4}};
    std::vector<std::array<std::int32_t, HOUSE_COUNT>> result{};
    result.reserve(120);
    std::array<std::int32_t, HOUSE_COUNT> p{base};
    do
    {
        result.push_back(p);
    } while (std::next_permutation(p.begin(), p.end()));
    return result;
}

}  // namespace

/* Public API -------------------------------------------------------------- */
Solution solve()
{
    /* Enumerations encoded as fixed indices --------------------------------
       The index positions for every attribute category are fixed:
       Colours      : 0-red, 1-green, 2-ivory, 3-yellow, 4-blue
       Nationalities: 0-English, 1-Spaniard, 2-Ukrainian, 3-Norwegian, 4-Japanese
       Pets         : 0-dog, 1-snail, 2-fox, 3-horse, 4-zebra
       Drinks       : 0-coffee, 1-tea, 2-milk, 3-orange-juice, 4-water
       Hobbies      : 0-dancing, 1-painting, 2-reading, 3-chess, 4-football
    ----------------------------------------------------------------------- */
    const auto perms{permutations()};

    for (const auto& colour : perms)
    {
        /* 6. The green house is immediately to the right of the ivory house. */
        if (colour[1] != (colour[2] + 1))
        {
            continue;
        }

        for (const auto& nationality : perms)
        {
            /* 2. Englishman lives in the red house. */
            if (nationality[0] != colour[0])
            {
                continue;
            }

            /* 10. Norwegian lives in the first house (index 0). */
            if (nationality[3] != 0)
            {
                continue;
            }

            /* 15. Norwegian lives next to the blue house. */
            if (!is_adjacent(nationality[3], colour[4]))
            {
                continue;
            }

            for (const auto& drink : perms)
            {
                /* 4. Green house drinks coffee. */
                if (drink[0] != colour[1])
                {
                    continue;
                }

                /* 5. Ukrainian drinks tea. */
                if (drink[1] != nationality[2])
                {
                    continue;
                }

                /* 9. Middle house (index 2) drinks milk. */
                if (drink[2] != 2)
                {
                    continue;
                }

                for (const auto& pet : perms)
                {
                    /* 3. Spaniard owns the dog. */
                    if (pet[0] != nationality[1])
                    {
                        continue;
                    }

                    for (const auto& hobby : perms)
                    {
                        /* 7. Snail owner likes dancing. */
                        if (hobby[0] != pet[1])
                        {
                            continue;
                        }

                        /* 8. Yellow house is a painter. */
                        if (hobby[1] != colour[3])
                        {
                            continue;
                        }

                        /* 11. Reading is next to fox. */
                        if (!is_adjacent(hobby[2], pet[2]))
                        {
                            continue;
                        }

                        /* 12. Painter next to horse. */
                        if (!is_adjacent(hobby[1], pet[3]))
                        {
                            continue;
                        }

                        /* 13. Football drinks orange juice. */
                        if (hobby[4] != drink[3])
                        {
                            continue;
                        }

                        /* 14. Japanese plays chess. */
                        if (hobby[3] != nationality[4])
                        {
                            continue;
                        }

                        /* ----- All constraints satisfied, build solution ---- */
                        const std::int32_t water_house{drink[4]};
                        const std::int32_t zebra_house{pet[4]};

                        std::string drinksWater{};
                        std::string ownsZebra{};

                        for (std::int32_t i{0}; i < HOUSE_COUNT; ++i)
                        {
                            if (nationality[static_cast<std::size_t>(i)] == water_house)
                            {
                                drinksWater = nationality_name(i);
                            }

                            if (nationality[static_cast<std::size_t>(i)] == zebra_house)
                            {
                                ownsZebra = nationality_name(i);
                            }
                        }

                        return Solution{drinksWater, ownsZebra};
                    }
                }
            }
        }
    }

    /* The puzzle has a unique solution; reaching here would mean failure. */
    return Solution{};
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>

namespace zebra_puzzle {

auto solve() -> Solution
{
    using index_type = std::int32_t;
    constexpr index_type house_count { 5 };

    /*  Enumerations for every attribute – the underlying type is fixed-width
     *  to respect MISRA rules that disallow plain ‘int’.
     */
    enum Nationality : index_type { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum Color       : index_type { Red, Green, Ivory, Yellow, Blue };
    enum Pet         : index_type { Dog, Snail, Fox, Horse, Zebra };
    enum Drink       : index_type { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Hobby       : index_type { Dancing, Painting, Reading, Football, Chess };

    /*  Helper arrays to translate enumeration values back to strings.       */
    constexpr std::array<const char *, house_count> nationality_name {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    /*  Convenience lambdas                                                  */
    const auto position =
        [](const std::array<index_type, house_count> &a, index_type v) -> index_type
        {
            for (index_type i { 0 }; i < house_count; ++i)
            {
                if (a[static_cast<std::size_t>(i)] == v)
                {
                    return i;
                }
            }
            return static_cast<index_type>(-1); /* unreachable for correct input */
        };

    const auto is_next =
        [](index_type p1, index_type p2) -> bool
        {
            return ((p1 == (p2 + static_cast<index_type>(1))) ||
                    (p2 == (p1 + static_cast<index_type>(1))));
        };

    /*  Initial canonical permutations for std::next_permutation             */
    std::array<index_type, house_count> colors        { Red, Green, Ivory, Yellow, Blue };
    std::array<index_type, house_count> nationalities { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    std::array<index_type, house_count> drinks        { Coffee, Tea, Milk, OrangeJuice, Water };
    std::array<index_type, house_count> pets          { Dog, Snail, Fox, Horse, Zebra };
    std::array<index_type, house_count> hobbies       { Dancing, Painting, Reading, Football, Chess };

    /*  Ensure canonical ordering before first permutation call              */
    std::sort(colors.begin(),        colors.end());
    std::sort(nationalities.begin(), nationalities.end());
    std::sort(drinks.begin(),        drinks.end());
    std::sort(pets.begin(),          pets.end());
    std::sort(hobbies.begin(),       hobbies.end());

    /*  Brute-force with aggressive pruning                                  */
    do
    {
        /*  #6  Green immediately to the right of Ivory                      */
        if (position(colors, Green) != (position(colors, Ivory) + static_cast<index_type>(1)))
        {
            continue;
        }

        /*  #15 Norwegian lives next to the blue house – depends on colors   */
        /*  (nationalities not yet fixed, but we know final nationality pos) */

        do
        {
            /*  #2  Englishman lives in the red house                        */
            if (position(nationalities, Englishman) != position(colors, Red))
            {
                continue;
            }

            /*  #10 Norwegian lives in the first house                       */
            if (position(nationalities, Norwegian) != static_cast<index_type>(0))
            {
                continue;
            }

            /*  #15 Norwegian lives next to the blue house                   */
            if (!is_next(position(nationalities, Norwegian), position(colors, Blue)))
            {
                continue;
            }

            do
            {
                /*  #4  Green house drinks coffee                            */
                if (position(drinks, Coffee) != position(colors, Green))
                {
                    continue;
                }

                /*  #5  Ukrainian drinks tea                                 */
                if (position(drinks, Tea) != position(nationalities, Ukrainian))
                {
                    continue;
                }

                /*  #9  Middle house (index 2) drinks milk                   */
                if (drinks[static_cast<std::size_t>(2)] != Milk)
                {
                    continue;
                }

                do
                {
                    /*  #3  Spaniard owns dog                                */
                    if (position(pets, Dog) != position(nationalities, Spaniard))
                    {
                        continue;
                    }

                    do
                    {
                        /*  #7  Snail owner likes dancing                    */
                        if (position(hobbies, Dancing) != position(pets, Snail))
                        {
                            continue;
                        }

                        /*  #8  Yellow house painter                         */
                        if (position(hobbies, Painting) != position(colors, Yellow))
                        {
                            continue;
                        }

                        /*  #11 Reader lives next to fox owner               */
                        if (!is_next(position(hobbies, Reading), position(pets, Fox)))
                        {
                            continue;
                        }

                        /*  #12 Painter next to horse owner                  */
                        if (!is_next(position(hobbies, Painting), position(pets, Horse)))
                        {
                            continue;
                        }

                        /*  #13 Football drinks orange juice                 */
                        if (position(hobbies, Football) != position(drinks, OrangeJuice))
                        {
                            continue;
                        }

                        /*  #14 Japanese plays chess                         */
                        if (position(hobbies, Chess) != position(nationalities, Japanese))
                        {
                            continue;
                        }

                        /*  All constraints satisfied – build solution       */
                        const index_type water_drinker { position(drinks, Water) };
                        const index_type zebra_owner   { position(pets, Zebra)  };

                        Solution sol;
                        sol.drinksWater =
                            nationality_name[static_cast<std::size_t>(
                                nationalities[static_cast<std::size_t>(water_drinker)])];
                        sol.ownsZebra   =
                            nationality_name[static_cast<std::size_t>(
                                nationalities[static_cast<std::size_t>(zebra_owner)])];
                        return sol;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    /*  No solution found – should never happen for the classic puzzle       */
    return Solution { "", "" };
}

}   /* namespace zebra_puzzle */

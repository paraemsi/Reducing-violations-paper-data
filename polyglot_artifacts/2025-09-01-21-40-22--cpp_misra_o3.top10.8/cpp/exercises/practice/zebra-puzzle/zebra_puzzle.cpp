#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <string>

namespace zebra_puzzle {

namespace {
/* Fixed-width house index. */
using HouseIndex = std::uint8_t;
constexpr HouseIndex HOUSE_COUNT {5U};

/* Enumerations for every attribute – the numeric value is irrelevant,
 * only uniqueness matters.
 */
enum class Colour       : HouseIndex { Red, Green, Ivory, Yellow, Blue };
enum class Pet          : HouseIndex { Dog, Snail, Fox, Horse, Zebra };
enum class Drink        : HouseIndex { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby        : HouseIndex { Reading, Painting, Dancing, Football, Chess };

/* Convert nationality enum to a readable string. */
auto to_string(Nationality nat) -> std::string
{
    switch (nat)
    {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard  : return "Spaniard";
        case Nationality::Ukrainian : return "Ukrainian";
        case Nationality::Norwegian : return "Norwegian";
        case Nationality::Japanese  : return "Japanese";
        default                     : return "";
    }
}

/* Helper to find the house position of a given attribute value. */
template <typename T>
auto index_of(const std::array<T, HOUSE_COUNT>& arr, T value) -> HouseIndex
{
    return static_cast<HouseIndex>(std::distance(arr.begin(),
                                                 std::find(arr.begin(), arr.end(), value)));
}

/* Helper – check whether two houses are adjacent. */
auto is_adjacent(HouseIndex a, HouseIndex b) -> bool
{
    return (a == (b + static_cast<HouseIndex>(1U))) ||
           (b == (a + static_cast<HouseIndex>(1U)));
}

} // namespace

auto solve() -> Solution
{
    /* The puzzle is always solved by permuting attribute arrays; an explicit
     * reference permutation array is not required.
     */

    std::array<Nationality, HOUSE_COUNT> nationality {};
    std::array<Colour,       HOUSE_COUNT> colour {};
    std::array<Drink,        HOUSE_COUNT> drink {};
    std::array<Pet,          HOUSE_COUNT> pet {};
    std::array<Hobby,        HOUSE_COUNT> hobby {};

    /* Fill nationality with initial ordering. */
    for (HouseIndex i {0U}; i < HOUSE_COUNT; ++i)
    {
        nationality[i] = static_cast<Nationality>(i);
        colour[i]      = static_cast<Colour>(i);
        drink[i]       = static_cast<Drink>(i);
        pet[i]         = static_cast<Pet>(i);
        hobby[i]       = static_cast<Hobby>(i);
    }

    /* Enumerate nationalities first – rule 10 prunes heavily. */
    do
    {
        if (index_of(nationality, Nationality::Norwegian) != static_cast<HouseIndex>(0U))
        {
            continue; /* Rule 10 – Norwegian lives in first house. */
        }

        /* Enumerate colours – rules 2,6,15 prune. */
        do
        {
            if (index_of(colour, Colour::Red) != index_of(nationality, Nationality::Englishman))
            {
                continue; /* Rule 2. */
            }

            HouseIndex greenPos { index_of(colour, Colour::Green) };
            HouseIndex ivoryPos { index_of(colour, Colour::Ivory) };
            if (greenPos != (ivoryPos + static_cast<HouseIndex>(1U)))
            {
                continue; /* Rule 6 – green is immediately right of ivory. */
            }

            if (!is_adjacent(index_of(colour, Colour::Blue),
                             index_of(nationality, Nationality::Norwegian)))
            {
                continue; /* Rule 15. */
            }

            /* Enumerate drinks – rules 4,5,9,13 prune. */
            do
            {
                if (index_of(drink, Drink::Coffee) != greenPos)
                {
                    continue; /* Rule 4. */
                }
                if (index_of(drink, Drink::Tea) != index_of(nationality, Nationality::Ukrainian))
                {
                    continue; /* Rule 5. */
                }
                if (drink[static_cast<HouseIndex>(2U)] != Drink::Milk)
                {
                    continue; /* Rule 9 – middle house (index 2) drinks milk. */
                }

                /* Enumerate pets – rules 3 will prune. */
                do
                {
                    if (index_of(pet, Pet::Dog) != index_of(nationality, Nationality::Spaniard))
                    {
                        continue; /* Rule 3. */
                    }

                    /* Enumerate hobbies at the innermost level – remaining rules. */
                    do
                    {
                        if (index_of(pet, Pet::Snail) != index_of(hobby, Hobby::Dancing))
                        {
                            continue; /* Rule 7. */
                        }
                        if (index_of(colour, Colour::Yellow) != index_of(hobby, Hobby::Painting))
                        {
                            continue; /* Rule 8. */
                        }
                        if (!is_adjacent(index_of(hobby, Hobby::Reading), index_of(pet, Pet::Fox)))
                        {
                            continue; /* Rule 11. */
                        }
                        if (!is_adjacent(index_of(hobby, Hobby::Painting), index_of(pet, Pet::Horse)))
                        {
                            continue; /* Rule 12. */
                        }
                        if (index_of(hobby, Hobby::Football) != index_of(drink, Drink::OrangeJuice))
                        {
                            continue; /* Rule 13. */
                        }
                        if (index_of(nationality, Nationality::Japanese) != index_of(hobby, Hobby::Chess))
                        {
                            continue; /* Rule 14. */
                        }

                        /* All constraints satisfied – prepare the solution. */
                        Solution sol {};
                        sol.drinksWater = to_string(nationality[index_of(drink, Drink::Water)]);
                        sol.ownsZebra   = to_string(nationality[index_of(pet, Pet::Zebra)]);

                        return sol; /* Puzzle solved – exit all loops. */

                    } while (std::next_permutation(hobby.begin(), hobby.end()));

                } while (std::next_permutation(pet.begin(), pet.end()));

            } while (std::next_permutation(drink.begin(), drink.end()));

        } while (std::next_permutation(colour.begin(), colour.end()));

    } while (std::next_permutation(nationality.begin(), nationality.end()));

    /* Control should never reach here – the puzzle has a unique solution. */
    return Solution {};
}

} // namespace zebra_puzzle

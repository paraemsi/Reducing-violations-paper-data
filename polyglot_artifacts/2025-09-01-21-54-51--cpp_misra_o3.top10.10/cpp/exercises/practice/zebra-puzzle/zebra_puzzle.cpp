#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle
{

/*  Type aliases compliant with the fixed–width requirement.
 *  Five houses therefore a signed 8-bit value is sufficient. */
using Index = std::int8_t;

/*  Enumerations – the underlying type is Index so we can store the
 *  enumerator values directly inside Index arrays without conversions. */
enum class Nat : Index
{
    Englishman,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};

enum class Col : Index
{
    Red,
    Green,
    Ivory,
    Yellow,
    Blue
};

enum class Pet : Index
{
    Dog,
    Snails,
    Fox,
    Horse,
    Zebra
};

enum class Drink : Index
{
    Coffee,
    Tea,
    Milk,
    OrangeJuice,
    Water
};

enum class Hobby : Index
{
    Dancing,
    Painting,
    Reading,
    Football,
    Chess
};

/*  Helper to find the house index of a particular value. */
template <typename T>
static auto find_house(const std::array<T, 5U>& houses, T value) -> Index
{
    for (Index i {0}; i < static_cast<Index>(5); ++i)
    {
        if (houses[static_cast<std::size_t>(i)] == value)
        {
            return i;
        }
    }
    return static_cast<Index>(-1); /* unreachable in valid search */
}

auto solve() -> Solution
{
    /*  Each array maps house-index -> attribute. Start with the identity
     *  permutation {0,1,2,3,4}. */
    std::array<Index, 5U> nat {{0, 1, 2, 3, 4}};
    std::array<Index, 5U> col {{0, 1, 2, 3, 4}};
    std::array<Index, 5U> pet {{0, 1, 2, 3, 4}};
    std::array<Index, 5U> drink {{0, 1, 2, 3, 4}};
    std::array<Index, 5U> hobby {{0, 1, 2, 3, 4}};

    /*  Enumeration values for readability. */
    constexpr Index ENGLISHMAN {static_cast<Index>(Nat::Englishman)};
    constexpr Index SPANIARD   {static_cast<Index>(Nat::Spaniard)};
    constexpr Index UKRAINIAN  {static_cast<Index>(Nat::Ukrainian)};
    constexpr Index NORWEGIAN  {static_cast<Index>(Nat::Norwegian)};
    constexpr Index JAPANESE   {static_cast<Index>(Nat::Japanese)};

    constexpr Index RED   {static_cast<Index>(Col::Red)};
    constexpr Index GREEN {static_cast<Index>(Col::Green)};
    constexpr Index IVORY {static_cast<Index>(Col::Ivory)};
    constexpr Index YELLOW{static_cast<Index>(Col::Yellow)};
    constexpr Index BLUE  {static_cast<Index>(Col::Blue)};

    constexpr Index DOG    {static_cast<Index>(Pet::Dog)};
    constexpr Index SNAILS {static_cast<Index>(Pet::Snails)};
    constexpr Index FOX    {static_cast<Index>(Pet::Fox)};
    constexpr Index HORSE  {static_cast<Index>(Pet::Horse)};
    constexpr Index ZEBRA  {static_cast<Index>(Pet::Zebra)};

    constexpr Index COFFEE {static_cast<Index>(Drink::Coffee)};
    constexpr Index TEA    {static_cast<Index>(Drink::Tea)};
    constexpr Index MILK   {static_cast<Index>(Drink::Milk)};
    constexpr Index OJ     {static_cast<Index>(Drink::OrangeJuice)};
    constexpr Index WATER  {static_cast<Index>(Drink::Water)};

    constexpr Index DANCING {static_cast<Index>(Hobby::Dancing)};
    constexpr Index PAINTING{static_cast<Index>(Hobby::Painting)};
    constexpr Index READING {static_cast<Index>(Hobby::Reading)};
    constexpr Index FOOTBALL{static_cast<Index>(Hobby::Football)};
    constexpr Index CHESS   {static_cast<Index>(Hobby::Chess)};

    do
    {
        /* Constraint 10: Norwegian in first house. */
        if (!(nat[0] == NORWEGIAN))
        {
            continue;
        }

        do
        {
            /* Constraint 2: Englishman lives in red house. */
            Index english_house {find_house(nat, ENGLISHMAN)};
            if (!(col[static_cast<std::size_t>(english_house)] == RED))
            {
                continue;
            }

            /* Constraint 6: Green is immediately right of Ivory. */
            Index ivory_house {find_house(col, IVORY)};
            Index green_house {find_house(col, GREEN)};
            if (!(green_house == (ivory_house + 1)))
            {
                continue;
            }

            /* Constraint 15: Norwegian next to blue house. */
            Index blue_house {find_house(col, BLUE)};
            Index norwegian_house {0}; /* already known */
            if (!((blue_house == (norwegian_house + 1)) ||
                  (norwegian_house == (blue_house + 1))))
            {
                continue;
            }

            do
            {
                /* Constraint 4: Coffee drunk in green house. */
                if (!(drink[static_cast<std::size_t>(green_house)] == COFFEE))
                {
                    continue;
                }

                /* Constraint 5: Ukrainian drinks tea. */
                Index ukrainian_house {find_house(nat, UKRAINIAN)};
                if (!(drink[static_cast<std::size_t>(ukrainian_house)] == TEA))
                {
                    continue;
                }

                /* Constraint 9: Middle house drinks milk. */
                if (!(drink[2U] == MILK))
                {
                    continue;
                }

                do
                {
                    /* Constraint 3: Spaniard owns dog. */
                    Index spaniard_house {find_house(nat, SPANIARD)};
                    if (!(pet[static_cast<std::size_t>(spaniard_house)] == DOG))
                    {
                        continue;
                    }

                    do
                    {
                        /* Constraint 7: Snail owner likes dancing. */
                        Index snail_house {find_house(pet, SNAILS)};
                        if (!(hobby[static_cast<std::size_t>(snail_house)] == DANCING))
                        {
                            continue;
                        }

                        /* Constraint 8: Yellow house painter. */
                        Index yellow_house {find_house(col, YELLOW)};
                        if (!(hobby[static_cast<std::size_t>(yellow_house)] == PAINTING))
                        {
                            continue;
                        }

                        /* Constraint 11: Reading next to fox. */
                        Index reading_house {find_house(hobby, READING)};
                        Index fox_house {find_house(pet, FOX)};
                        if (!((reading_house == (fox_house + 1)) ||
                              (fox_house == (reading_house + 1))))
                        {
                            continue;
                        }

                        /* Constraint 12: Painter next to horse. */
                        Index painter_house {yellow_house};
                        Index horse_house {find_house(pet, HORSE)};
                        if (!((painter_house == (horse_house + 1)) ||
                              (horse_house == (painter_house + 1))))
                        {
                            continue;
                        }

                        /* Constraint 13: Football drinks orange juice. */
                        Index football_house {find_house(hobby, FOOTBALL)};
                        if (!(drink[static_cast<std::size_t>(football_house)] == OJ))
                        {
                            continue;
                        }

                        /* Constraint 14: Japanese plays chess. */
                        Index japanese_house {find_house(nat, JAPANESE)};
                        if (!(hobby[static_cast<std::size_t>(japanese_house)] == CHESS))
                        {
                            continue;
                        }

                        /* All constraints satisfied – build the solution. */
                        Index water_house {find_house(drink, WATER)};
                        Index zebra_house {find_house(pet, ZEBRA)};

                        static const std::array<std::string, 5U> NAT_STR {{
                            "Englishman",
                            "Spaniard",
                            "Ukrainian",
                            "Norwegian",
                            "Japanese"
                        }};

                        Solution result {};
                        result.drinksWater =
                            NAT_STR[static_cast<std::size_t>(nat[static_cast<std::size_t>(water_house)])];
                        result.ownsZebra   =
                            NAT_STR[static_cast<std::size_t>(nat[static_cast<std::size_t>(zebra_house)])];
                        return result;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(col.begin(), col.end()));
    } while (std::next_permutation(nat.begin(), nat.end()));

    /* Control can reach here only if the puzzle is inconsistent,
     * which should never happen with the canonical Zebra clues. */
    return Solution{};
}

} // namespace zebra_puzzle

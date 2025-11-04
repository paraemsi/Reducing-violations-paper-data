#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {

using Index = std::int32_t;
static constexpr Index NUM_HOUSES = 5;

/* Nationalities */
static constexpr Index ENGLISH   = 0;
static constexpr Index SPANIARD  = 1;
static constexpr Index UKRAINIAN = 2;
static constexpr Index NORWEGIAN = 3;
static constexpr Index JAPANESE  = 4;

/* House colours */
static constexpr Index RED    = 0;
static constexpr Index GREEN  = 1;
static constexpr Index IVORY  = 2;
static constexpr Index YELLOW = 3;
static constexpr Index BLUE   = 4;

/* Pets */
static constexpr Index DOG    = 0;
static constexpr Index SNAILS = 1;
static constexpr Index FOX    = 2;
static constexpr Index HORSE  = 3;
static constexpr Index ZEBRA  = 4;

/* Drinks */
static constexpr Index COFFEE       = 0;
static constexpr Index TEA          = 1;
static constexpr Index MILK         = 2;
static constexpr Index ORANGE_JUICE = 3;
static constexpr Index WATER        = 4;

/* Hobbies */
static constexpr Index DANCING  = 0;
static constexpr Index PAINTING = 1;
static constexpr Index READING  = 2;
static constexpr Index FOOTBALL = 3;
static constexpr Index CHESS    = 4;

/* Helper: find the house index of a given value */
template <typename T, std::size_t N>
auto find_position(const std::array<T, N>& arr, T value) -> Index
{
    for (Index i = 0; i < static_cast<Index>(N); ++i)
    {
        if (arr[static_cast<std::size_t>(i)] == value)
        {
            return i;
        }
    }
    return -1;
}

}  // unnamed namespace

auto solve() -> Solution
{
    const std::array<std::string, NUM_HOUSES> NAT_NAMES = {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    const std::array<Index, NUM_HOUSES> BASE = {0, 1, 2, 3, 4};

    std::array<Index, NUM_HOUSES> nationality{};
    std::array<Index, NUM_HOUSES> colour{};
    std::array<Index, NUM_HOUSES> pet{};
    std::array<Index, NUM_HOUSES> drink{};
    std::array<Index, NUM_HOUSES> hobby{};

    std::array<Index, NUM_HOUSES> nat_perm = BASE;
    do
    {
        nationality = nat_perm;

        /* Rule 10: Norwegian lives in the first house */
        if (nationality[0] != NORWEGIAN)
        {
            continue;
        }

        std::array<Index, NUM_HOUSES> col_perm = BASE;
        do
        {
            colour = col_perm;

            /* Rule 2: Englishman lives in the red house */
            const Index english_house = find_position(nationality, ENGLISH);
            if (colour[static_cast<std::size_t>(english_house)] != RED)
            {
                continue;
            }

            /* Rule 6: green is immediately to the right of ivory */
            const Index ivory_house = find_position(colour, IVORY);
            const Index green_house = find_position(colour, GREEN);
            if (green_house != (ivory_house + 1))
            {
                continue;
            }

            /* Rule 15: Norwegian lives next to the blue house */
            const Index norwegian_house = find_position(nationality, NORWEGIAN);
            const Index blue_house      = find_position(colour, BLUE);
            if (std::abs(static_cast<int>(blue_house - norwegian_house)) != 1)
            {
                continue;
            }

            std::array<Index, NUM_HOUSES> drink_perm = BASE;
            do
            {
                drink = drink_perm;

                /* Rule 4: green-house drinks coffee */
                if (drink[static_cast<std::size_t>(green_house)] != COFFEE)
                {
                    continue;
                }

                /* Rule 5: Ukrainian drinks tea */
                const Index ukrainian_house = find_position(nationality, UKRAINIAN);
                if (drink[static_cast<std::size_t>(ukrainian_house)] != TEA)
                {
                    continue;
                }

                /* Rule 9: middle house drinks milk */
                if (drink[2] != MILK)
                {
                    continue;
                }

                std::array<Index, NUM_HOUSES> pet_perm = BASE;
                do
                {
                    pet = pet_perm;

                    /* Rule 3: Spaniard owns the dog */
                    const Index spaniard_house = find_position(nationality, SPANIARD);
                    if (pet[static_cast<std::size_t>(spaniard_house)] != DOG)
                    {
                        continue;
                    }

                    std::array<Index, NUM_HOUSES> hobby_perm = BASE;
                    do
                    {
                        hobby = hobby_perm;

                        /* Rule 7: snail owner likes dancing */
                        const Index snail_house = find_position(pet, SNAILS);
                        if (hobby[static_cast<std::size_t>(snail_house)] != DANCING)
                        {
                            continue;
                        }

                        /* Rule 8: yellow house is painter */
                        const Index yellow_house = find_position(colour, YELLOW);
                        if (hobby[static_cast<std::size_t>(yellow_house)] != PAINTING)
                        {
                            continue;
                        }

                        /* Rule 11: reader lives next to fox */
                        const Index reading_house = find_position(hobby, READING);
                        const Index fox_house     = find_position(pet, FOX);
                        if (std::abs(static_cast<int>(reading_house - fox_house)) != 1)
                        {
                            continue;
                        }

                        /* Rule 12: painter next to horse */
                        const Index painter_house = find_position(hobby, PAINTING);
                        const Index horse_house   = find_position(pet, HORSE);
                        if (std::abs(static_cast<int>(painter_house - horse_house)) != 1)
                        {
                            continue;
                        }

                        /* Rule 13: football drinks orange juice */
                        const Index football_house = find_position(hobby, FOOTBALL);
                        if (drink[static_cast<std::size_t>(football_house)] != ORANGE_JUICE)
                        {
                            continue;
                        }

                        /* Rule 14: Japanese plays chess */
                        const Index japanese_house = find_position(nationality, JAPANESE);
                        if (hobby[static_cast<std::size_t>(japanese_house)] != CHESS)
                        {
                            continue;
                        }

                        /* Found the unique solution */
                        const Index water_house = find_position(drink, WATER);
                        const Index zebra_house = find_position(pet, ZEBRA);

                        Solution sol{};
                        sol.drinksWater = NAT_NAMES[static_cast<std::size_t>(
                            nationality[static_cast<std::size_t>(water_house)])];
                        sol.ownsZebra   = NAT_NAMES[static_cast<std::size_t>(
                            nationality[static_cast<std::size_t>(zebra_house)])];
                        return sol;

                    } while (std::next_permutation(
                        hobby_perm.begin(), hobby_perm.end()));

                } while (std::next_permutation(
                    pet_perm.begin(), pet_perm.end()));

            } while (std::next_permutation(
                drink_perm.begin(), drink_perm.end()));

        } while (std::next_permutation(
            col_perm.begin(), col_perm.end()));

    } while (std::next_permutation(
        nat_perm.begin(), nat_perm.end()));

    /* Control should never reach here */
    return Solution{};
}

}  // namespace zebra_puzzle

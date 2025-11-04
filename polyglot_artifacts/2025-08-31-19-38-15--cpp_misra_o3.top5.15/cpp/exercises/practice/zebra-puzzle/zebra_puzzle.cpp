#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {

/* Number of houses */
static constexpr std::int32_t HOUSE_COUNT = 5;

/* Colours */
static constexpr std::int32_t RED    = 0;
static constexpr std::int32_t GREEN  = 1;
static constexpr std::int32_t IVORY  = 2;
static constexpr std::int32_t YELLOW = 3;
static constexpr std::int32_t BLUE   = 4;

/* Nationalities */
static constexpr std::int32_t ENGLISHMAN = 0;
static constexpr std::int32_t SPANIARD   = 1;
static constexpr std::int32_t UKRAINIAN  = 2;
static constexpr std::int32_t NORWEGIAN  = 3;
static constexpr std::int32_t JAPANESE   = 4;

/* Pets */
static constexpr std::int32_t DOG    = 0;
static constexpr std::int32_t SNAILS = 1;
static constexpr std::int32_t FOX    = 2;
static constexpr std::int32_t HORSE  = 3;
static constexpr std::int32_t ZEBRA  = 4;

/* Drinks */
static constexpr std::int32_t COFFEE       = 0;
static constexpr std::int32_t TEA          = 1;
static constexpr std::int32_t MILK         = 2;
static constexpr std::int32_t ORANGE_JUICE = 3;
static constexpr std::int32_t WATER        = 4;

/* Hobbies */
static constexpr std::int32_t DANCING  = 0;
static constexpr std::int32_t PAINTING = 1;
static constexpr std::int32_t READING  = 2;
static constexpr std::int32_t FOOTBALL = 3;
static constexpr std::int32_t CHESS    = 4;

/* Get index of value in array */
template<typename T>
static auto index_of(const std::array<T, HOUSE_COUNT>& arr, T value) -> std::int32_t
{
    for(std::int32_t i = 0; i < HOUSE_COUNT; ++i)
    {
        if(arr[static_cast<std::size_t>(i)] == value)
        {
            return i;
        }
    }
    return -1;
}

/* Convert nationality id to string */
static auto nationality_to_string(std::int32_t nat) -> std::string
{
    switch(nat)
    {
        case ENGLISHMAN: { return "Englishman"; }
        case SPANIARD:   { return "Spaniard"; }
        case UKRAINIAN:  { return "Ukrainian"; }
        case NORWEGIAN:  { return "Norwegian"; }
        case JAPANESE:   { return "Japanese"; }
        default:         { return {}; }
    }
}

} /* unnamed namespace */

auto solve() -> Solution
{
    std::array<std::int32_t, HOUSE_COUNT> colours       = { RED, GREEN, IVORY, YELLOW, BLUE };
    std::array<std::int32_t, HOUSE_COUNT> nationalities = { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    std::array<std::int32_t, HOUSE_COUNT> pets          = { DOG, SNAILS, FOX, HORSE, ZEBRA };
    std::array<std::int32_t, HOUSE_COUNT> drinks        = { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    std::array<std::int32_t, HOUSE_COUNT> hobbies       = { DANCING, PAINTING, READING, FOOTBALL, CHESS };

    do
    {
        /* 6: green right of ivory */
        const std::int32_t green_idx = index_of(colours, GREEN);
        const std::int32_t ivory_idx = index_of(colours, IVORY);
        if((green_idx != (ivory_idx + 1)))
        {
            continue;
        }

        /* 15 with 10: Norwegian (house 0) next to blue -> blue at house 1 */
        if((colours[1] != BLUE))
        {
            continue;
        }

        do
        {
            /* 10: Norwegian in first house */
            if((index_of(nationalities, NORWEGIAN) != 0))
            {
                continue;
            }

            /* 2: Englishman lives in red */
            if((colours[index_of(nationalities, ENGLISHMAN)] != RED))
            {
                continue;
            }

            do
            {
                /* 3: Spaniard owns dog */
                if((index_of(nationalities, SPANIARD) != index_of(pets, DOG)))
                {
                    continue;
                }

                do
                {
                    /* 4: green drinks coffee */
                    if((index_of(colours, GREEN) != index_of(drinks, COFFEE)))
                    {
                        continue;
                    }

                    /* 5: Ukrainian drinks tea */
                    if((index_of(nationalities, UKRAINIAN) != index_of(drinks, TEA)))
                    {
                        continue;
                    }

                    /* 9: middle house (2) drinks milk */
                    if((drinks[2] != MILK))
                    {
                        continue;
                    }

                    do
                    {
                        /* 7: snails -> dancing */
                        if((index_of(pets, SNAILS) != index_of(hobbies, DANCING)))
                        {
                            continue;
                        }

                        /* 8: yellow -> painter */
                        if((hobbies[index_of(colours, YELLOW)] != PAINTING))
                        {
                            continue;
                        }

                        /* 13: football -> orange juice */
                        if((index_of(hobbies, FOOTBALL) != index_of(drinks, ORANGE_JUICE)))
                        {
                            continue;
                        }

                        /* 14: Japanese -> chess */
                        if((hobbies[index_of(nationalities, JAPANESE)] != CHESS))
                        {
                            continue;
                        }

                        /* 11: reading next to fox */
                        if((std::abs(index_of(hobbies, READING) - index_of(pets, FOX)) != 1))
                        {
                            continue;
                        }

                        /* 12: painter next to horse */
                        if((std::abs(index_of(hobbies, PAINTING) - index_of(pets, HORSE)) != 1))
                        {
                            continue;
                        }

                        /* All constraints satisfied */
                        const std::string drinksWater = nationality_to_string(
                            nationalities[static_cast<std::size_t>(index_of(drinks, WATER))]
                        );

                        const std::string ownsZebra = nationality_to_string(
                            nationalities[static_cast<std::size_t>(index_of(pets, ZEBRA))]
                        );

                        return Solution{ drinksWater, ownsZebra };

                    } while(std::next_permutation(hobbies.begin(), hobbies.end()));

                } while(std::next_permutation(drinks.begin(), drinks.end()));

            } while(std::next_permutation(pets.begin(), pets.end()));

        } while(std::next_permutation(nationalities.begin(), nationalities.end()));

    } while(std::next_permutation(colours.begin(), colours.end()));

    /* Unreachable – puzzle has unique solution */
    return Solution{};
}

} /* namespace zebra_puzzle */

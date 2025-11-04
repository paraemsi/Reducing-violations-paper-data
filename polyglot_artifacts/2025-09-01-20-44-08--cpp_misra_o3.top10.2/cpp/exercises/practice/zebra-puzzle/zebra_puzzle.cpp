#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {
/* Return the index of `value` in `arr` (length 5). 5U if not found. */
template <typename T>
constexpr std::uint8_t index_of(const std::array<T, 5U> & arr, const T value) noexcept
{
    for (std::uint8_t i = static_cast<std::uint8_t>(0U); i < static_cast<std::uint8_t>(5U); ++i)
    {
        if (arr[static_cast<std::size_t>(i)] == value)
        {
            return i;
        }
    }
    return static_cast<std::uint8_t>(5U);
}

/* Absolute distance of two indices (0-4). */
constexpr std::uint8_t diff(const std::uint8_t a, const std::uint8_t b) noexcept
{
    return (a > b) ? static_cast<std::uint8_t>(a - b) : static_cast<std::uint8_t>(b - a);
}
} // unnamed namespace

enum class Color : std::uint8_t { red, green, ivory, yellow, blue };
enum class Nationality : std::uint8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet : std::uint8_t { dog, snail, fox, horse, zebra };
enum class Drink : std::uint8_t { coffee, tea, milk, orange_juice, water };
enum class Hobby : std::uint8_t { painting, dancing, reading, football, chess };

static std::string to_string(const Nationality nat)
{
    switch (nat)
    {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard:   return "Spaniard";
        case Nationality::Ukrainian:  return "Ukrainian";
        case Nationality::Norwegian:  return "Norwegian";
        case Nationality::Japanese:   return "Japanese";
        default:                      return {};
    }
}

Solution solve()
{
    /* Canonical (sorted) attribute lists. */
    const std::array<Color, 5U>       colors_base   = { Color::red, Color::green, Color::ivory, Color::yellow, Color::blue };
    const std::array<Nationality, 5U> nations_base  = { Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian,
                                                        Nationality::Norwegian, Nationality::Japanese };
    const std::array<Pet, 5U>         pets_base     = { Pet::dog, Pet::snail, Pet::fox, Pet::horse, Pet::zebra };
    const std::array<Drink, 5U>       drinks_base   = { Drink::coffee, Drink::tea, Drink::milk, Drink::orange_juice, Drink::water };
    const std::array<Hobby, 5U>       hobbies_base  = { Hobby::painting, Hobby::dancing, Hobby::reading, Hobby::football, Hobby::chess };

    Solution result{};
    bool      found = false;

    std::array<Color, 5U> colors = colors_base;
    do
    {
        /* Rule 6: green is immediately right of ivory. */
        const std::uint8_t green_idx = index_of(colors, Color::green);
        const std::uint8_t ivory_idx = index_of(colors, Color::ivory);
        if (green_idx != static_cast<std::uint8_t>(ivory_idx + static_cast<std::uint8_t>(1U)))
        {
            continue;
        }

        std::array<Nationality, 5U> nations = nations_base;
        do
        {
            /* Rule 10: Norwegian in first house. */
            if (index_of(nations, Nationality::Norwegian) != static_cast<std::uint8_t>(0U))
            {
                continue;
            }
            /* Rule 2: Englishman in red. */
            if (index_of(nations, Nationality::Englishman) != index_of(colors, Color::red))
            {
                continue;
            }
            /* Rule 15: Norwegian next to blue. */
            if (diff(index_of(nations, Nationality::Norwegian), index_of(colors, Color::blue)) != static_cast<std::uint8_t>(1U))
            {
                continue;
            }

            std::array<Drink, 5U> drinks = drinks_base;
            do
            {
                /* Rule 4: green drinks coffee. */
                if (index_of(colors, Color::green) != index_of(drinks, Drink::coffee))
                {
                    continue;
                }
                /* Rule 5: Ukrainian drinks tea. */
                if (index_of(nations, Nationality::Ukrainian) != index_of(drinks, Drink::tea))
                {
                    continue;
                }
                /* Rule 9: middle house drinks milk. */
                if (index_of(drinks, Drink::milk) != static_cast<std::uint8_t>(2U))
                {
                    continue;
                }

                std::array<Pet, 5U> pets = pets_base;
                do
                {
                    /* Rule 3: Spaniard owns dog. */
                    if (index_of(nations, Nationality::Spaniard) != index_of(pets, Pet::dog))
                    {
                        continue;
                    }

                    std::array<Hobby, 5U> hobbies = hobbies_base;
                    do
                    {
                        /* Rule 8: yellow house painter. */
                        if (index_of(colors, Color::yellow) != index_of(hobbies, Hobby::painting))
                        {
                            continue;
                        }
                        /* Rule 7: snail owner dances. */
                        if (index_of(pets, Pet::snail) != index_of(hobbies, Hobby::dancing))
                        {
                            continue;
                        }
                        /* Rule 12: painter next to horse. */
                        if (diff(index_of(hobbies, Hobby::painting), index_of(pets, Pet::horse)) != static_cast<std::uint8_t>(1U))
                        {
                            continue;
                        }
                        /* Rule 11: reader next to fox. */
                        if (diff(index_of(hobbies, Hobby::reading), index_of(pets, Pet::fox)) != static_cast<std::uint8_t>(1U))
                        {
                            continue;
                        }
                        /* Rule 13: football drinks OJ. */
                        if (index_of(hobbies, Hobby::football) != index_of(drinks, Drink::orange_juice))
                        {
                            continue;
                        }
                        /* Rule 14: Japanese plays chess. */
                        if (index_of(nations, Nationality::Japanese) != index_of(hobbies, Hobby::chess))
                        {
                            continue;
                        }

                        /* All constraints satisfied. */
                        result.drinksWater = to_string(nations[index_of(drinks, Drink::water)]);
                        result.ownsZebra  = to_string(nations[index_of(pets,  Pet::zebra)]);
                        found             = true;
                    } while ((!found) && std::next_permutation(hobbies.begin(), hobbies.end()));
                } while ((!found) && std::next_permutation(pets.begin(), pets.end()));
            } while ((!found) && std::next_permutation(drinks.begin(), drinks.end()));
        } while ((!found) && std::next_permutation(nations.begin(), nations.end()));
    } while ((!found) && std::next_permutation(colors.begin(), colors.end()));

    return result;
}

} // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

/* Number of houses */
constexpr std::uint32_t houseCount{5U};

/* Enumerations for every attribute */
enum class Nationality : std::uint8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color       : std::uint8_t { Red, Green, Ivory, Yellow, Blue };
enum class Pet         : std::uint8_t { Dog, Snails, Fox, Horse, Zebra };
enum class Drink       : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby       : std::uint8_t { Reading, Painting, Dancing, Football, Chess };

/* Helper – convert enum value to std::string (specialised for Nationality) */
[[nodiscard]] std::string to_string(Nationality value)
{
    switch (value) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard  : return "Spaniard";
        case Nationality::Ukrainian : return "Ukrainian";
        case Nationality::Norwegian : return "Norwegian";
        case Nationality::Japanese  : return "Japanese";
        default                     : return {};
    }
}

/* Index finder */
template <typename T>
[[nodiscard]] std::uint32_t index_of(const std::array<T, houseCount>& arr, T value)
{
    for (std::uint32_t i{0U}; i < houseCount; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return houseCount;   /* unreachable for correct inputs */
}

/* Absolute distance of two indices – helper for “next-to” rules */
[[nodiscard]] std::uint32_t distance(std::uint32_t a, std::uint32_t b)
{
    return (a > b) ? (a - b) : (b - a);
}

}   // namespace

Solution solve()
{
    /* Initialise ordered base arrays for permutation */
    std::array<Nationality, houseCount> nationalities{
        Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian,
        Nationality::Norwegian, Nationality::Japanese};

    std::array<Color, houseCount> colors{
        Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};

    std::array<Drink, houseCount> drinks{
        Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};

    std::array<Pet, houseCount> pets{
        Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};

    std::array<Hobby, houseCount> hobbies{
        Hobby::Reading, Hobby::Painting, Hobby::Dancing, Hobby::Football, Hobby::Chess};

    /* Sort arrays to satisfy std::next_permutation pre-condition */
    std::sort(nationalities.begin(), nationalities.end(),
              [](Nationality a, Nationality b) { return static_cast<std::uint8_t>(a) < static_cast<std::uint8_t>(b); });
    std::sort(colors.begin(), colors.end(),
              [](Color a, Color b) { return static_cast<std::uint8_t>(a) < static_cast<std::uint8_t>(b); });
    std::sort(drinks.begin(), drinks.end(),
              [](Drink a, Drink b) { return static_cast<std::uint8_t>(a) < static_cast<std::uint8_t>(b); });
    std::sort(pets.begin(), pets.end(),
              [](Pet a, Pet b) { return static_cast<std::uint8_t>(a) < static_cast<std::uint8_t>(b); });
    std::sort(hobbies.begin(), hobbies.end(),
              [](Hobby a, Hobby b) { return static_cast<std::uint8_t>(a) < static_cast<std::uint8_t>(b); });

    /* Enumerate permutations with progressive constraint checking */
    do {    /* Nationalities */
        if (nationalities[0U] != Nationality::Norwegian) {
            continue;
        }

        const std::uint32_t englishIdx{index_of(nationalities, Nationality::Englishman)};
        const std::uint32_t norwegianIdx{0U};

        do {    /* Colors */

            const std::uint32_t redIdx{index_of(colors, Color::Red)};
            if (englishIdx != redIdx) {
                continue;
            }

            const std::uint32_t blueIdx{index_of(colors, Color::Blue)};
            if (distance(blueIdx, norwegianIdx) != 1U) {
                continue;
            }

            const std::uint32_t greenIdx{index_of(colors, Color::Green)};
            const std::uint32_t ivoryIdx{index_of(colors, Color::Ivory)};
            if (greenIdx != (ivoryIdx + 1U)) {
                continue;
            }

            do {    /* Drinks */

                if (drinks[2U] != Drink::Milk) {            /* middle house */
                    continue;
                }
                if (drinks[greenIdx] != Drink::Coffee) {    /* rule 4 */
                    continue;
                }
                const std::uint32_t ukrIdx{index_of(nationalities, Nationality::Ukrainian)};
                if (drinks[ukrIdx] != Drink::Tea) {         /* rule 5 */
                    continue;
                }

                do {    /* Pets */

                    const std::uint32_t spaniardIdx{index_of(nationalities, Nationality::Spaniard)};
                    if (pets[spaniardIdx] != Pet::Dog) {    /* rule 3 */
                        continue;
                    }

                    do {    /* Hobbies */

                        const std::uint32_t snailIdx{index_of(pets, Pet::Snails)};
                        if (hobbies[snailIdx] != Hobby::Dancing) {  /* rule 7 */
                            continue;
                        }

                        const std::uint32_t yellowIdx{index_of(colors, Color::Yellow)};
                        if (hobbies[yellowIdx] != Hobby::Painting) {    /* rule 8 */
                            continue;
                        }

                        const std::uint32_t footballIdx{index_of(hobbies, Hobby::Football)};
                        if (drinks[footballIdx] != Drink::OrangeJuice) {    /* rule 13 */
                            continue;
                        }

                        const std::uint32_t japaneseIdx{index_of(nationalities, Nationality::Japanese)};
                        if (hobbies[japaneseIdx] != Hobby::Chess) {        /* rule 14 */
                            continue;
                        }

                        const std::uint32_t readingIdx{index_of(hobbies, Hobby::Reading)};
                        const std::uint32_t foxIdx{index_of(pets, Pet::Fox)};
                        if (distance(readingIdx, foxIdx) != 1U) {          /* rule 11 */
                            continue;
                        }

                        const std::uint32_t horseIdx{index_of(pets, Pet::Horse)};
                        if (distance(horseIdx, yellowIdx) != 1U) {         /* rule 12 */
                            continue;
                        }

                        /* All constraints satisfied – build solution */
                        const std::uint32_t waterIdx{index_of(drinks, Drink::Water)};
                        const std::uint32_t zebraIdx{index_of(pets, Pet::Zebra)};

                        Solution sol{};
                        sol.drinksWater = to_string(nationalities[waterIdx]);
                        sol.ownsZebra   = to_string(nationalities[zebraIdx]);
                        return sol;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));

                } while (std::next_permutation(pets.begin(), pets.end()));

            } while (std::next_permutation(drinks.begin(), drinks.end()));

        } while (std::next_permutation(colors.begin(), colors.end()));

    } while (std::next_permutation(nationalities.begin(), nationalities.end()));

    /* Should never reach here – return empty result to satisfy all control paths */
    return Solution{};
}

}   // namespace zebra_puzzle

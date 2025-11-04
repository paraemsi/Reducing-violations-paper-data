#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

/* Fixed-width enumeration values (5 per category) */
enum class Color  : std::uint8_t { Red, Green, Ivory, Yellow, Blue,  Count };
enum class Nation : std::uint8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese, Count };
enum class Pet    : std::uint8_t { Dog, Snail, Fox, Horse, Zebra,    Count };
enum class Drink  : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water, Count };
enum class Hobby  : std::uint8_t { Reading, Painting, Dancing, Football, Chess, Count };

using Positions = std::array<std::uint8_t, 5U>;
constexpr std::uint8_t HOUSE_COUNT { 5U };

/* Absolute distance between two house indices */
constexpr auto distance(std::uint8_t lhs, std::uint8_t rhs) noexcept -> std::uint8_t
{
    return (lhs > rhs) ? (lhs - rhs) : (rhs - lhs);
}

/* Convert Nation to std::string */
auto to_string(Nation nation) -> std::string
{
    switch (nation) {
        case Nation::Englishman: return "Englishman";
        case Nation::Spaniard:   return "Spaniard";
        case Nation::Ukrainian:  return "Ukrainian";
        case Nation::Norwegian:  return "Norwegian";
        case Nation::Japanese:   return "Japanese";
        default:                 return {};
    }
}

}   // unnamed namespace

auto solve() -> Solution
{
    Positions color { 0U, 1U, 2U, 3U, 4U };

    /* 1st level: colours (early prune with rule-6) */
    do {
        if (color[static_cast<std::uint8_t>(Color::Green)]
            != (color[static_cast<std::uint8_t>(Color::Ivory)] + 1U)) {
            continue;
        }

        Positions nation { 0U, 1U, 2U, 3U, 4U };
        /* 2nd level: nationalities */
        do {
            if (nation[static_cast<std::uint8_t>(Nation::Englishman)]
                != color[static_cast<std::uint8_t>(Color::Red)]) {
                continue;
            }
            if (nation[static_cast<std::uint8_t>(Nation::Norwegian)] != 0U) {
                continue;
            }
            if (distance(nation[static_cast<std::uint8_t>(Nation::Norwegian)],
                         color[static_cast<std::uint8_t>(Color::Blue)]) != 1U) {
                continue;
            }

            Positions drink { 0U, 1U, 2U, 3U, 4U };
            /* 3rd level: beverages */
            do {
                if (drink[static_cast<std::uint8_t>(Drink::Coffee)]
                    != color[static_cast<std::uint8_t>(Color::Green)]) {
                    continue;
                }
                if (drink[static_cast<std::uint8_t>(Drink::Tea)]
                    != nation[static_cast<std::uint8_t>(Nation::Ukrainian)]) {
                    continue;
                }
                if (drink[static_cast<std::uint8_t>(Drink::Milk)] != 2U) {
                    continue;
                }

                Positions pet { 0U, 1U, 2U, 3U, 4U };
                /* 4th level: pets */
                do {
                    if (pet[static_cast<std::uint8_t>(Pet::Dog)]
                        != nation[static_cast<std::uint8_t>(Nation::Spaniard)]) {
                        continue;
                    }

                    Positions hobby { 0U, 1U, 2U, 3U, 4U };
                    /* 5th level: hobbies */
                    do {
                        if (hobby[static_cast<std::uint8_t>(Hobby::Dancing)]
                            != pet[static_cast<std::uint8_t>(Pet::Snail)]) {
                            continue;
                        }
                        if (hobby[static_cast<std::uint8_t>(Hobby::Painting)]
                            != color[static_cast<std::uint8_t>(Color::Yellow)]) {
                            continue;
                        }
                        if (distance(hobby[static_cast<std::uint8_t>(Hobby::Reading)],
                                     pet[static_cast<std::uint8_t>(Pet::Fox)]) != 1U) {
                            continue;
                        }
                        if (distance(hobby[static_cast<std::uint8_t>(Hobby::Painting)],
                                     pet[static_cast<std::uint8_t>(Pet::Horse)]) != 1U) {
                            continue;
                        }
                        if (hobby[static_cast<std::uint8_t>(Hobby::Football)]
                            != drink[static_cast<std::uint8_t>(Drink::OrangeJuice)]) {
                            continue;
                        }
                        if (hobby[static_cast<std::uint8_t>(Hobby::Chess)]
                            != nation[static_cast<std::uint8_t>(Nation::Japanese)]) {
                            continue;
                        }

                        /* All constraints satisfied – extract answers */
                        const std::uint8_t water_house
                            = drink[static_cast<std::uint8_t>(Drink::Water)];
                        const std::uint8_t zebra_house
                            = pet[static_cast<std::uint8_t>(Pet::Zebra)];

                        Nation water_drinker { Nation::Count };
                        Nation zebra_owner   { Nation::Count };

                        for (std::uint8_t idx = 0U; idx < HOUSE_COUNT; ++idx) {
                            if (nation[idx] == water_house) {
                                water_drinker = static_cast<Nation>(idx);
                            }
                            if (nation[idx] == zebra_house) {
                                zebra_owner = static_cast<Nation>(idx);
                            }
                        }

                        Solution result {};
                        result.drinksWater = to_string(water_drinker);
                        result.ownsZebra   = to_string(zebra_owner);
                        return result;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nation.begin(), nation.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    /* Should never reach here */
    return Solution {};
}

}   // namespace zebra_puzzle

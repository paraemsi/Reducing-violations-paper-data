#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

/*  Enumerations for the five possible values of every category.
 *  The explicit underlying type avoids violating the “no plain int” rule.
 */
enum class Color : std::uint8_t { Red, Green, Ivory, Yellow, Blue };
enum class Nationality : std::uint8_t { English, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet : std::uint8_t { Dog, Snail, Fox, Horse, Zebra };
enum class Drink : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby : std::uint8_t { Reading, Dancing, Football, Painting, Chess };

constexpr std::size_t houseCount {5U};

/* Utility: find the index of a particular value inside an array */
template <typename T>
constexpr std::size_t index_of(const std::array<T, houseCount>& arr, T value)
{
    for (std::size_t i {0U}; i < houseCount; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return houseCount; /* unreachable for valid data */
}

/* Convert enumeration to std::string for the public Solution */
std::string to_string(Nationality nat)
{
    switch (nat) {
        case Nationality::English:    return "Englishman";
        case Nationality::Spaniard:   return "Spaniard";
        case Nationality::Ukrainian:  return "Ukrainian";
        case Nationality::Norwegian:  return "Norwegian";
        case Nationality::Japanese:   return "Japanese";
        default:                      return "";
    }
}

} // unnamed namespace

Solution solve()
{
    /* canonical permutation seed {0,1,2,3,4} */
    std::array<std::uint8_t, houseCount> base {{0U, 1U, 2U, 3U, 4U}};

    std::array<Color, houseCount>      colors {};
    std::array<Nationality, houseCount>nations {};
    std::array<Pet, houseCount>        pets {};
    std::array<Drink, houseCount>      drinks {};
    std::array<Hobby, houseCount>      hobbies {};

    /* iterate over colour permutations first; apply strong colour-related constraints */
    std::array<std::uint8_t, houseCount> cPerm {base};
    do {
        for (std::size_t i {0U}; i < houseCount; ++i) {
            colors[i] = static_cast<Color>(cPerm[i]);
        }

        /* 6: green immediately right of ivory */
        const std::size_t idxGreen {index_of(colors, Color::Green)};
        const std::size_t idxIvory {index_of(colors, Color::Ivory)};
        if (idxGreen != (idxIvory + 1U)) {
            continue;
        }

        /* iterate over nationality permutations */
        std::array<std::uint8_t, houseCount> nPerm {base};
        do {
            for (std::size_t i {0U}; i < houseCount; ++i) {
                nations[i] = static_cast<Nationality>(nPerm[i]);
            }

            /* 10: Norwegian in first house */
            if (nations[0U] != Nationality::Norwegian) {
                continue;
            }

            /* 2: Englishman lives in red house */
            if (index_of(nations, Nationality::English) != index_of(colors, Color::Red)) {
                continue;
            }

            /* 15: Norwegian next to blue house */
            const std::size_t idxBlue {index_of(colors, Color::Blue)};
            const std::size_t idxNorwegian {0U};
            if (!(((idxBlue + 1U) == idxNorwegian) || ((idxBlue == (idxNorwegian + 1U))))) {
                continue;
            }

            /* iterate over drink permutations */
            std::array<std::uint8_t, houseCount> dPerm {base};
            do {
                for (std::size_t i {0U}; i < houseCount; ++i) {
                    drinks[i] = static_cast<Drink>(dPerm[i]);
                }

                /* 4: green -> coffee */
                if (index_of(drinks, Drink::Coffee) != idxGreen) {
                    continue;
                }
                /* 5: Ukrainian drinks tea */
                if (index_of(nations, Nationality::Ukrainian) != index_of(drinks, Drink::Tea)) {
                    continue;
                }
                /* 9: middle house drinks milk (house index 2) */
                if (drinks[2U] != Drink::Milk) {
                    continue;
                }

                /* iterate over hobby permutations */
                std::array<std::uint8_t, houseCount> hPerm {base};
                do {
                    for (std::size_t i {0U}; i < houseCount; ++i) {
                        hobbies[i] = static_cast<Hobby>(hPerm[i]);
                    }

                    /* 8: yellow house -> painter */
                    if (hobbies[index_of(colors, Color::Yellow)] != Hobby::Painting) {
                        continue;
                    }
                    /* 13: football drinks orange juice */
                    if (index_of(hobbies, Hobby::Football) != index_of(drinks, Drink::OrangeJuice)) {
                        continue;
                    }
                    /* 14: Japanese plays chess */
                    if (hobbies[index_of(nations, Nationality::Japanese)] != Hobby::Chess) {
                        continue;
                    }
                    /* 7: snail owner likes dancing  -> handled when pets are set */

                    /* iterate over pet permutations last */
                    std::array<std::uint8_t, houseCount> pPerm {base};
                    do {
                        for (std::size_t i {0U}; i < houseCount; ++i) {
                            pets[i] = static_cast<Pet>(pPerm[i]);
                        }

                        /* 3: Spaniard owns dog */
                        if (index_of(nations, Nationality::Spaniard) != index_of(pets, Pet::Dog)) {
                            continue;
                        }
                        /* 7: snail owner likes dancing */
                        if (hobbies[index_of(pets, Pet::Snail)] != Hobby::Dancing) {
                            continue;
                        }
                        /* 11: reader next to fox */
                        const std::size_t idxReader {index_of(hobbies, Hobby::Reading)};
                        const std::size_t idxFox {index_of(pets, Pet::Fox)};
                        if (!(((idxReader + 1U) == idxFox) || ((idxFox + 1U) == idxReader))) {
                            continue;
                        }
                        /* 12: painter next to horse */
                        const std::size_t idxPainter {index_of(hobbies, Hobby::Painting)};
                        const std::size_t idxHorse {index_of(pets, Pet::Horse)};
                        if (!(((idxPainter + 1U) == idxHorse) || ((idxHorse + 1U) == idxPainter))) {
                            continue;
                        }

                        /* All constraints satisfied – build and return solution */
                        const std::size_t idxWaterDrinker {index_of(drinks, Drink::Water)};
                        const std::size_t idxZebraOwner {index_of(pets, Pet::Zebra)};

                        Solution sol {};
                        sol.drinksWater = to_string(nations[idxWaterDrinker]);
                        sol.ownsZebra   = to_string(nations[idxZebraOwner]);
                        return sol;

                    } while (std::next_permutation(pPerm.begin(), pPerm.end()));
                } while (std::next_permutation(hPerm.begin(), hPerm.end()));
            } while (std::next_permutation(dPerm.begin(), dPerm.end()));
        } while (std::next_permutation(nPerm.begin(), nPerm.end()));
    } while (std::next_permutation(cPerm.begin(), cPerm.end()));

    /* The puzzle always has a unique solution; reaching here means failure */
    return Solution {};
}

} // namespace zebra_puzzle

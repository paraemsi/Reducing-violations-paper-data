#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <string>

namespace zebra_puzzle {

namespace {

using IndexArray = std::array<std::int32_t, 5>;

constexpr std::int32_t HOUSE_COUNT {5};

constexpr bool is_adjacent(std::int32_t lhs, std::int32_t rhs) noexcept
{
    return (std::abs(lhs - rhs) == 1);
}

constexpr bool is_immediately_right(std::int32_t left, std::int32_t right) noexcept
{
    return ((right - left) == 1);
}

template <typename T>
constexpr std::int32_t find_house(const std::array<T, 5>& arr,
                                  T value) noexcept
{
    for (std::int32_t idx {0}; idx < HOUSE_COUNT; ++idx) {
        if (arr[static_cast<std::size_t>(idx)] == value) {
            return idx;
        }
    }
    return -1;
}

}  // namespace

auto solve() -> Solution
{
    enum Color : std::int32_t { red, green, ivory, yellow, blue };
    enum Nationality : std::int32_t { english, spaniard, ukrainian, norwegian, japanese };
    enum Pet : std::int32_t { dog, fox, snails, horse, zebra };
    enum Drink : std::int32_t { coffee, tea, milk, orange_juice, water };
    enum Hobby : std::int32_t { reading, painting, dancing, chess, football };

    IndexArray base {0, 1, 2, 3, 4};

    IndexArray colors {0, 1, 2, 3, 4};
    IndexArray nationalities {};
    IndexArray drinks {};
    IndexArray pets {};
    IndexArray hobbies {};

    do {

        const std::int32_t idxIvory {find_house(colors, static_cast<std::int32_t>(ivory))};
        const std::int32_t idxGreen {find_house(colors, static_cast<std::int32_t>(green))};
        if (!is_immediately_right(idxIvory, idxGreen)) {
            continue;
        }

        do {
            nationalities = base;

            if (nationalities[0] != norwegian) {
                continue;
            }

            const std::int32_t idxRed {find_house(colors, static_cast<std::int32_t>(red))};
            const std::int32_t idxEnglish {find_house(nationalities, static_cast<std::int32_t>(english))};
            if (idxEnglish != idxRed) {
                continue;
            }

            const std::int32_t idxBlue {find_house(colors, static_cast<std::int32_t>(blue))};
            const std::int32_t idxNorwegian {0};
            if (!is_adjacent(idxNorwegian, idxBlue)) {
                continue;
            }

            do {
                drinks = base;

                if (drinks[idxGreen] != coffee) {
                    continue;
                }

                const std::int32_t idxUkrainian {find_house(nationalities, static_cast<std::int32_t>(ukrainian))};
                if (drinks[idxUkrainian] != tea) {
                    continue;
                }

                if (drinks[2] != milk) {
                    continue;
                }

                do {
                    pets = base;

                    const std::int32_t idxSpaniard {find_house(nationalities, static_cast<std::int32_t>(spaniard))};
                    if (pets[idxSpaniard] != dog) {
                        continue;
                    }

                    do {
                        hobbies = base;

                        const std::int32_t idxSnails {find_house(pets, static_cast<std::int32_t>(snails))};
                        const std::int32_t idxDancing {find_house(hobbies, static_cast<std::int32_t>(dancing))};
                        if (idxSnails != idxDancing) {
                            continue;
                        }

                        const std::int32_t idxYellow {find_house(colors, static_cast<std::int32_t>(yellow))};
                        const std::int32_t idxPainting {find_house(hobbies, static_cast<std::int32_t>(painting))};
                        if (idxYellow != idxPainting) {
                            continue;
                        }

                        const std::int32_t idxHorse {find_house(pets, static_cast<std::int32_t>(horse))};
                        if (!is_adjacent(idxPainting, idxHorse)) {
                            continue;
                        }

                        const std::int32_t idxFootball {find_house(hobbies, static_cast<std::int32_t>(football))};
                        if (drinks[idxFootball] != orange_juice) {
                            continue;
                        }

                        const std::int32_t idxJapanese {find_house(nationalities, static_cast<std::int32_t>(japanese))};
                        if (hobbies[idxJapanese] != chess) {
                            continue;
                        }

                        const std::int32_t idxReading {find_house(hobbies, static_cast<std::int32_t>(reading))};
                        const std::int32_t idxFox {find_house(pets, static_cast<std::int32_t>(fox))};
                        if (!is_adjacent(idxReading, idxFox)) {
                            continue;
                        }

                        const std::int32_t idxWater {find_house(drinks, static_cast<std::int32_t>(water))};
                        const std::int32_t idxZebra {find_house(pets, static_cast<std::int32_t>(zebra))};

                        const std::string names[5] = {
                            "Englishman",
                            "Spaniard",
                            "Ukrainian",
                            "Norwegian",
                            "Japanese"
                        };

                        Solution solution {};
                        solution.drinksWater = names[nationalities[idxWater]];
                        solution.ownsZebra  = names[nationalities[idxZebra]];
                        return solution;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));

                } while (std::next_permutation(pets.begin(), pets.end()));

            } while (std::next_permutation(drinks.begin(), drinks.end()));

        } while (std::next_permutation(nationalities.begin(), nationalities.end()));

    } while (std::next_permutation(colors.begin(), colors.end()));

    return {};
}

}  // namespace zebra_puzzle

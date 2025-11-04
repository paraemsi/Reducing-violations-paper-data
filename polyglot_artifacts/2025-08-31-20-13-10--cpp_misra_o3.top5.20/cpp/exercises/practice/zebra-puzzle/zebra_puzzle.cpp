#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {

/* Enumerations representing the five values of each category */
enum class Color : std::uint32_t { Red, Green, Ivory, Yellow, Blue };
enum class Nationality : std::uint32_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet : std::uint32_t { Dog, Snails, Fox, Horse, Zebra };
enum class Drink : std::uint32_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby : std::uint32_t { Dancing, Painter, Reading, Football, Chess };

/* Helper table for converting the enumeration value to its string name */
constexpr std::array<const char *, 5U> NATIONALITY_NAMES{{
    "Englishman",
    "Spaniard",
    "Ukrainian",
    "Norwegian",
    "Japanese"
}};

}  // namespace

auto solve() -> Solution
{
    /* Canonical permutation {0,1,2,3,4} used as a starting point for every loop */
    const std::array<std::uint32_t, 5U> canonical{{0U, 1U, 2U, 3U, 4U}};

    /* ---- Iterate over all colour permutations ---- */
    std::array<std::uint32_t, 5U> colours = canonical;
    do {
        /* 6. The green house is immediately to the right of the ivory house. */
        if ((colours[static_cast<std::uint32_t>(Color::Green)] !=
             (colours[static_cast<std::uint32_t>(Color::Ivory)] + 1U))) {
            continue;
        }

        /* ---- Iterate over all nationality permutations ---- */
        std::array<std::uint32_t, 5U> nationalities = canonical;
        do {
            /* 10. The Norwegian lives in the first house. */
            if (nationalities[static_cast<std::uint32_t>(Nationality::Norwegian)] != 0U) {
                continue;
            }

            /* 2. The Englishman lives in the red house. */
            if (nationalities[static_cast<std::uint32_t>(Nationality::Englishman)] !=
                colours[static_cast<std::uint32_t>(Color::Red)]) {
                continue;
            }

            /* 15. The Norwegian lives next to the blue house. */
            if (std::abs(static_cast<std::int32_t>(
                              nationalities[static_cast<std::uint32_t>(Nationality::Norwegian)])
                          - static_cast<std::int32_t>(
                              colours[static_cast<std::uint32_t>(Color::Blue)])) != 1) {
                continue;
            }

            /* ---- Iterate over all drink permutations ---- */
            std::array<std::uint32_t, 5U> drinks = canonical;
            do {
                /* 9. The person in the middle house drinks milk. */
                if (drinks[static_cast<std::uint32_t>(Drink::Milk)] != 2U) {
                    continue;
                }

                /* 4. The person in the green house drinks coffee. */
                if (drinks[static_cast<std::uint32_t>(Drink::Coffee)] !=
                    colours[static_cast<std::uint32_t>(Color::Green)]) {
                    continue;
                }

                /* 5. The Ukrainian drinks tea. */
                if (drinks[static_cast<std::uint32_t>(Drink::Tea)] !=
                    nationalities[static_cast<std::uint32_t>(Nationality::Ukrainian)]) {
                    continue;
                }

                /* ---- Iterate over all pet permutations ---- */
                std::array<std::uint32_t, 5U> pets = canonical;
                do {
                    /* 3. The Spaniard owns the dog. */
                    if (pets[static_cast<std::uint32_t>(Pet::Dog)] !=
                        nationalities[static_cast<std::uint32_t>(Nationality::Spaniard)]) {
                        continue;
                    }

                    /* ---- Iterate over all hobby permutations ---- */
                    std::array<std::uint32_t, 5U> hobbies = canonical;
                    do {
                        /* 7. The snail owner likes to go dancing. */
                        if (hobbies[static_cast<std::uint32_t>(Hobby::Dancing)] !=
                            pets[static_cast<std::uint32_t>(Pet::Snails)]) {
                            continue;
                        }

                        /* 8. The person in the yellow house is a painter. */
                        if (hobbies[static_cast<std::uint32_t>(Hobby::Painter)] !=
                            colours[static_cast<std::uint32_t>(Color::Yellow)]) {
                            continue;
                        }

                        /* 11. The reader lives next to the fox owner. */
                        if (std::abs(static_cast<std::int32_t>(
                                         hobbies[static_cast<std::uint32_t>(Hobby::Reading)])
                                     - static_cast<std::int32_t>(
                                         pets[static_cast<std::uint32_t>(Pet::Fox)])) != 1) {
                            continue;
                        }

                        /* 12. The painter's house is next to the house with the horse. */
                        if (std::abs(static_cast<std::int32_t>(
                                         hobbies[static_cast<std::uint32_t>(Hobby::Painter)])
                                     - static_cast<std::int32_t>(
                                         pets[static_cast<std::uint32_t>(Pet::Horse)])) != 1) {
                            continue;
                        }

                        /* 13. The football player drinks orange juice. */
                        if (hobbies[static_cast<std::uint32_t>(Hobby::Football)] !=
                            drinks[static_cast<std::uint32_t>(Drink::OrangeJuice)]) {
                            continue;
                        }

                        /* 14. The Japanese person plays chess. */
                        if (hobbies[static_cast<std::uint32_t>(Hobby::Chess)] !=
                            nationalities[static_cast<std::uint32_t>(Nationality::Japanese)]) {
                            continue;
                        }

                        /* ---- All constraints satisfied: construct the solution ---- */
                        std::uint32_t const water_house =
                            drinks[static_cast<std::uint32_t>(Drink::Water)];
                        std::uint32_t const zebra_house =
                            pets[static_cast<std::uint32_t>(Pet::Zebra)];

                        Solution solved{};

                        for (std::uint32_t i = 0U; i < 5U; ++i) {
                            if (nationalities[i] == water_house) {
                                solved.drinksWater = NATIONALITY_NAMES[i];
                            }
                            if (nationalities[i] == zebra_house) {
                                solved.ownsZebra = NATIONALITY_NAMES[i];
                            }
                        }
                        return solved;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colours.begin(), colours.end()));

    /* Control should never reach here, but return an empty solution defensively. */
    return Solution{};
}

}  // namespace zebra_puzzle

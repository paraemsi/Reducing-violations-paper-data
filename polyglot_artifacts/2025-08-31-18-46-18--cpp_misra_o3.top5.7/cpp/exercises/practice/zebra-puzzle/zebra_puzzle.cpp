#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>

namespace zebra_puzzle {

using HouseIndex = std::uint32_t;
constexpr HouseIndex HOUSE_COUNT = 5U;

/* Attribute indices */
enum class Color : std::uint32_t { Red, Green, Ivory, Yellow, Blue };
enum class Nationality : std::uint32_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink : std::uint32_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet : std::uint32_t { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby : std::uint32_t { Dancing, Painting, Reading, Football, Chess };

/* Helper: check whether two houses are adjacent */
static bool is_next_to(HouseIndex const a, HouseIndex const b)
{
    return (((a + 1U) == b) || ((b + 1U) == a));
}

Solution solve()
{
    std::array<HouseIndex, HOUSE_COUNT> const base_perm = {0U, 1U, 2U, 3U, 4U};

    std::array<HouseIndex, HOUSE_COUNT> colors = base_perm;
    do {
        /* (6) Green is immediately to the right of Ivory. */
        if (colors[static_cast<std::uint32_t>(Color::Green)] !=
            (colors[static_cast<std::uint32_t>(Color::Ivory)] + 1U)) {
            continue;
        }

        std::array<HouseIndex, HOUSE_COUNT> nationalities = base_perm;
        do {
            /* (2) Englishman lives in the Red house. */
            if (nationalities[static_cast<std::uint32_t>(Nationality::Englishman)] !=
                colors[static_cast<std::uint32_t>(Color::Red)]) {
                continue;
            }
            /* (10) Norwegian lives in the first house (index 0). */
            if (nationalities[static_cast<std::uint32_t>(Nationality::Norwegian)] != 0U) {
                continue;
            }
            /* (15) Norwegian lives next to the Blue house. */
            if (!is_next_to(
                    nationalities[static_cast<std::uint32_t>(Nationality::Norwegian)],
                    colors[static_cast<std::uint32_t>(Color::Blue)])) {
                continue;
            }

            std::array<HouseIndex, HOUSE_COUNT> drinks = base_perm;
            do {
                /* (9) Milk is drunk in the middle house (index 2). */
                if (drinks[static_cast<std::uint32_t>(Drink::Milk)] != 2U) {
                    continue;
                }
                /* (4) Green-house resident drinks Coffee. */
                if (colors[static_cast<std::uint32_t>(Color::Green)] !=
                    drinks[static_cast<std::uint32_t>(Drink::Coffee)]) {
                    continue;
                }
                /* (5) Ukrainian drinks Tea. */
                if (nationalities[static_cast<std::uint32_t>(Nationality::Ukrainian)] !=
                    drinks[static_cast<std::uint32_t>(Drink::Tea)]) {
                    continue;
                }

                std::array<HouseIndex, HOUSE_COUNT> pets = base_perm;
                do {
                    /* (3) Spaniard owns the Dog. */
                    if (nationalities[static_cast<std::uint32_t>(Nationality::Spaniard)] !=
                        pets[static_cast<std::uint32_t>(Pet::Dog)]) {
                        continue;
                    }

                    std::array<HouseIndex, HOUSE_COUNT> hobbies = base_perm;
                    do {
                        /* (7) Snail owner likes Dancing. */
                        if (pets[static_cast<std::uint32_t>(Pet::Snails)] !=
                            hobbies[static_cast<std::uint32_t>(Hobby::Dancing)]) {
                            continue;
                        }
                        /* (8) Yellow-house resident is the Painter. */
                        if (colors[static_cast<std::uint32_t>(Color::Yellow)] !=
                            hobbies[static_cast<std::uint32_t>(Hobby::Painting)]) {
                            continue;
                        }
                        /* (11) Reader lives next to Fox owner. */
                        if (!is_next_to(
                                hobbies[static_cast<std::uint32_t>(Hobby::Reading)],
                                pets[static_cast<std::uint32_t>(Pet::Fox)])) {
                            continue;
                        }
                        /* (12) Painter lives next to Horse owner. */
                        if (!is_next_to(
                                hobbies[static_cast<std::uint32_t>(Hobby::Painting)],
                                pets[static_cast<std::uint32_t>(Pet::Horse)])) {
                            continue;
                        }
                        /* (13) Football player drinks Orange Juice. */
                        if (hobbies[static_cast<std::uint32_t>(Hobby::Football)] !=
                            drinks[static_cast<std::uint32_t>(Drink::OrangeJuice)]) {
                            continue;
                        }
                        /* (14) Japanese plays Chess. */
                        if (nationalities[static_cast<std::uint32_t>(Nationality::Japanese)] !=
                            hobbies[static_cast<std::uint32_t>(Hobby::Chess)]) {
                            continue;
                        }

                        /* --- All constraints satisfied: build the answer --- */
                        HouseIndex const water_house =
                            drinks[static_cast<std::uint32_t>(Drink::Water)];
                        HouseIndex const zebra_house =
                            pets[static_cast<std::uint32_t>(Pet::Zebra)];

                        Solution solution;

                        for (std::uint32_t i = 0U; i < HOUSE_COUNT; ++i) {
                            /* Who drinks water? */
                            if (nationalities[i] == water_house) {
                                switch (static_cast<Nationality>(i)) {
                                    case Nationality::Englishman:
                                        solution.drinksWater = "Englishman";
                                        break;
                                    case Nationality::Spaniard:
                                        solution.drinksWater = "Spaniard";
                                        break;
                                    case Nationality::Ukrainian:
                                        solution.drinksWater = "Ukrainian";
                                        break;
                                    case Nationality::Norwegian:
                                        solution.drinksWater = "Norwegian";
                                        break;
                                    case Nationality::Japanese:
                                        solution.drinksWater = "Japanese";
                                        break;
                                }
                            }
                            /* Who owns the Zebra? */
                            if (nationalities[i] == zebra_house) {
                                switch (static_cast<Nationality>(i)) {
                                    case Nationality::Englishman:
                                        solution.ownsZebra = "Englishman";
                                        break;
                                    case Nationality::Spaniard:
                                        solution.ownsZebra = "Spaniard";
                                        break;
                                    case Nationality::Ukrainian:
                                        solution.ownsZebra = "Ukrainian";
                                        break;
                                    case Nationality::Norwegian:
                                        solution.ownsZebra = "Norwegian";
                                        break;
                                    case Nationality::Japanese:
                                        solution.ownsZebra = "Japanese";
                                        break;
                                }
                            }
                        }
                        return solution;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    /* Should never reach here: puzzle guarantees a unique solution. */
    return Solution{};
}

}  // namespace zebra_puzzle

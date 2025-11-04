#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

// Strongly-typed categories with fixed underlying types to comply with rules.
enum class Color : std::uint8_t { red = 0U, green = 1U, ivory = 2U, yellow = 3U, blue = 4U };
enum class Nation : std::uint8_t { Englishman = 0U, Spaniard = 1U, Ukrainian = 2U, Norwegian = 3U, Japanese = 4U };
enum class Drink : std::uint8_t { coffee = 0U, tea = 1U, milk = 2U, orange_juice = 3U, water = 4U };
enum class Pet : std::uint8_t { dog = 0U, snails = 1U, fox = 2U, horse = 3U, zebra = 4U };
enum class Hobby : std::uint8_t { dancing = 0U, painter = 1U, reading = 2U, football = 3U, chess = 4U };

template <typename E>
constexpr std::uint8_t toU(E e) noexcept
{
    return static_cast<std::uint8_t>(e);
}

constexpr std::array<std::uint8_t, 5U> basePermutation() noexcept
{
    return {static_cast<std::uint8_t>(0U),
            static_cast<std::uint8_t>(1U),
            static_cast<std::uint8_t>(2U),
            static_cast<std::uint8_t>(3U),
            static_cast<std::uint8_t>(4U)};
}

std::uint8_t find_by_pos(const std::array<std::uint8_t, 5U> &arr, std::uint8_t pos) noexcept
{
    std::uint8_t i = static_cast<std::uint8_t>(0U);
    while (i < static_cast<std::uint8_t>(5U)) {
        if (arr[static_cast<std::size_t>(i)] == pos) {
            return i;
        } else {
            i = static_cast<std::uint8_t>(i + static_cast<std::uint8_t>(1U));
        }
    }
    // Should never happen for valid inputs; return 0 as a safe default.
    return static_cast<std::uint8_t>(0U);
}

}  // namespace

Solution solve()
{
    // Names for output mapping
    const std::array<std::string, 5U> nation_names = {
        std::string("Englishman"),
        std::string("Spaniard"),
        std::string("Ukrainian"),
        std::string("Norwegian"),
        std::string("Japanese"),
    };

    // Prepare base permutations
    const std::array<std::uint8_t, 5U> base = basePermutation();

    std::array<std::uint8_t, 5U> colors = base;
    do {
        // Constraint 6: green immediately to the right of ivory
        const std::uint32_t pos_green = static_cast<std::uint32_t>(colors[static_cast<std::size_t>(toU(Color::green))]);
        const std::uint32_t pos_ivory = static_cast<std::uint32_t>(colors[static_cast<std::size_t>(toU(Color::ivory))]);
        if (!(pos_green == (pos_ivory + 1U))) {
            continue;
        }

        std::array<std::uint8_t, 5U> nations = base;
        do {
            // Constraint 10: Norwegian lives in the first house (index 0)
            if (!(nations[static_cast<std::size_t>(toU(Nation::Norwegian))] == static_cast<std::uint8_t>(0U))) {
                continue;
            }
            // Constraint 2: Englishman lives in the red house
            if (!(nations[static_cast<std::size_t>(toU(Nation::Englishman))] == colors[static_cast<std::size_t>(toU(Color::red))])) {
                continue;
            }
            // Constraint 15: Norwegian lives next to the blue house
            {
                const std::uint32_t pos_norwegian =
                    static_cast<std::uint32_t>(nations[static_cast<std::size_t>(toU(Nation::Norwegian))]);
                const std::uint32_t pos_blue =
                    static_cast<std::uint32_t>(colors[static_cast<std::size_t>(toU(Color::blue))]);
                if (!(((pos_norwegian + 1U) == pos_blue) || ((pos_blue + 1U) == pos_norwegian))) {
                    continue;
                }
            }

            std::array<std::uint8_t, 5U> drinks = base;
            do {
                // Constraint 9: Middle house (index 2) drinks milk
                if (!(drinks[static_cast<std::size_t>(toU(Drink::milk))] == static_cast<std::uint8_t>(2U))) {
                    continue;
                }
                // Constraint 4: Green house drinks coffee
                if (!(colors[static_cast<std::size_t>(toU(Color::green))] == drinks[static_cast<std::size_t>(toU(Drink::coffee))])) {
                    continue;
                }
                // Constraint 5: Ukrainian drinks tea
                if (!(nations[static_cast<std::size_t>(toU(Nation::Ukrainian))] == drinks[static_cast<std::size_t>(toU(Drink::tea))])) {
                    continue;
                }

                std::array<std::uint8_t, 5U> pets = base;
                do {
                    // Constraint 3: Spaniard owns the dog
                    if (!(nations[static_cast<std::size_t>(toU(Nation::Spaniard))] == pets[static_cast<std::size_t>(toU(Pet::dog))])) {
                        continue;
                    }

                    std::array<std::uint8_t, 5U> hobbies = base;
                    do {
                        // Constraint 7: Snail owner likes dancing
                        if (!(pets[static_cast<std::size_t>(toU(Pet::snails))] == hobbies[static_cast<std::size_t>(toU(Hobby::dancing))])) {
                            continue;
                        }
                        // Constraint 8: Yellow house -> painter
                        if (!(colors[static_cast<std::size_t>(toU(Color::yellow))] == hobbies[static_cast<std::size_t>(toU(Hobby::painter))])) {
                            continue;
                        }
                        // Constraint 12: Painter's house is next to the house with the horse
                        {
                            const std::uint32_t pos_painter =
                                static_cast<std::uint32_t>(hobbies[static_cast<std::size_t>(toU(Hobby::painter))]);
                            const std::uint32_t pos_horse =
                                static_cast<std::uint32_t>(pets[static_cast<std::size_t>(toU(Pet::horse))]);
                            if (!(((pos_painter + 1U) == pos_horse) || ((pos_horse + 1U) == pos_painter))) {
                                continue;
                            }
                        }
                        // Constraint 13: Football player drinks orange juice
                        if (!(hobbies[static_cast<std::size_t>(toU(Hobby::football))] ==
                              drinks[static_cast<std::size_t>(toU(Drink::orange_juice))])) {
                            continue;
                        }
                        // Constraint 11: Reader lives next to the fox
                        {
                            const std::uint32_t pos_reader =
                                static_cast<std::uint32_t>(hobbies[static_cast<std::size_t>(toU(Hobby::reading))]);
                            const std::uint32_t pos_fox =
                                static_cast<std::uint32_t>(pets[static_cast<std::size_t>(toU(Pet::fox))]);
                            if (!(((pos_reader + 1U) == pos_fox) || ((pos_fox + 1U) == pos_reader))) {
                                continue;
                            }
                        }
                        // Constraint 14: Japanese plays chess
                        if (!(nations[static_cast<std::size_t>(toU(Nation::Japanese))] ==
                              hobbies[static_cast<std::size_t>(toU(Hobby::chess))])) {
                            continue;
                        }

                        // All constraints satisfied: derive answers
                        const std::uint8_t water_pos =
                            drinks[static_cast<std::size_t>(toU(Drink::water))];
                        const std::uint8_t zebra_pos =
                            pets[static_cast<std::size_t>(toU(Pet::zebra))];

                        const std::uint8_t water_nat_index = find_by_pos(nations, water_pos);
                        const std::uint8_t zebra_nat_index = find_by_pos(nations, zebra_pos);

                        Solution s{};
                        s.drinksWater = nation_names[static_cast<std::size_t>(water_nat_index)];
                        s.ownsZebra = nation_names[static_cast<std::size_t>(zebra_nat_index)];
                        return s;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Fallback (should never be reached)
    Solution s{};
    s.drinksWater = std::string();
    s.ownsZebra = std::string();
    return s;
}

}  // namespace zebra_puzzle

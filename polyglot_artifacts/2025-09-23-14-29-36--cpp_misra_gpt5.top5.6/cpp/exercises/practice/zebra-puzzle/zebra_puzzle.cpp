#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {
using Index = std::uint32_t;
static constexpr Index HOUSE_COUNT = 5U;

// Colors
static constexpr Index RED = 0U;
static constexpr Index GREEN = 1U;
static constexpr Index IVORY = 2U;
static constexpr Index YELLOW = 3U;
static constexpr Index BLUE = 4U;

// Nationalities
static constexpr Index ENGLISHMAN = 0U;
static constexpr Index SPANIARD = 1U;
static constexpr Index UKRAINIAN = 2U;
static constexpr Index NORWEGIAN = 3U;
static constexpr Index JAPANESE = 4U;

// Drinks
static constexpr Index COFFEE = 0U;
static constexpr Index TEA = 1U;
static constexpr Index MILK = 2U;
static constexpr Index ORANGE_JUICE = 3U;
static constexpr Index WATER = 4U;

// Pets
static constexpr Index DOG = 0U;
static constexpr Index SNAILS = 1U;
static constexpr Index FOX = 2U;
static constexpr Index HORSE = 3U;
static constexpr Index ZEBRA = 4U;

// Hobbies
static constexpr Index DANCING = 0U;
static constexpr Index PAINTING = 1U;
static constexpr Index READING = 2U;
static constexpr Index FOOTBALL = 3U;
static constexpr Index CHESS = 4U;

static Index find_index(const std::array<Index, HOUSE_COUNT>& arr, Index value)
{
    for (Index i = 0U; (i < HOUSE_COUNT); ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return HOUSE_COUNT;
}

static bool is_next_to(Index a, Index b)
{
    const bool left = ((a > 0U) && ((a - 1U) == b));
    const bool right = (((a + 1U) < HOUSE_COUNT) && ((a + 1U) == b));
    return (left || right);
}

static std::string nationality_to_string(Index nat)
{
    switch (nat) {
        case ENGLISHMAN: {
            return std::string("Englishman");
        }
        case SPANIARD: {
            return std::string("Spaniard");
        }
        case UKRAINIAN: {
            return std::string("Ukrainian");
        }
        case NORWEGIAN: {
            return std::string("Norwegian");
        }
        case JAPANESE: {
            return std::string("Japanese");
        }
        default: {
            return std::string();
        }
    }
}
}  // namespace

Solution solve()
{
    const std::array<Index, HOUSE_COUNT> base = {0U, 1U, 2U, 3U, 4U};

    std::array<Index, HOUSE_COUNT> colors = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        const Index green_idx = find_index(colors, GREEN);
        const Index ivory_idx = find_index(colors, IVORY);
        if (!(green_idx == (ivory_idx + 1U))) {
            continue;
        }

        // Prepare nationalities permutations
        std::array<Index, HOUSE_COUNT> nations = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (!(nations[0U] == NORWEGIAN)) {
                continue;
            }

            // 2. The Englishman lives in the red house.
            const Index english_idx = find_index(nations, ENGLISHMAN);
            if (!(colors[english_idx] == RED)) {
                continue;
            }

            // 15. The Norwegian lives next to the blue house.
            const Index norwegian_idx = find_index(nations, NORWEGIAN);
            const bool nor_next_to_blue =
                (((norwegian_idx > 0U) && (colors[norwegian_idx - 1U] == BLUE)) ||
                 (((norwegian_idx + 1U) < HOUSE_COUNT) && (colors[norwegian_idx + 1U] == BLUE)));
            if (!nor_next_to_blue) {
                continue;
            }

            // Prepare drinks permutations
            std::array<Index, HOUSE_COUNT> drinks = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (!(drinks[2U] == MILK)) {
                    continue;
                }

                // 4. The person in the green house drinks coffee.
                if (!(drinks[green_idx] == COFFEE)) {
                    continue;
                }

                // 5. The Ukrainian drinks tea.
                const Index ukrainian_idx = find_index(nations, UKRAINIAN);
                if (!(drinks[ukrainian_idx] == TEA)) {
                    continue;
                }

                // Prepare pets permutations
                std::array<Index, HOUSE_COUNT> pets = base;
                do {
                    // 3. The Spaniard owns the dog.
                    const Index spaniard_idx = find_index(nations, SPANIARD);
                    if (!(pets[spaniard_idx] == DOG)) {
                        continue;
                    }

                    // Prepare hobbies permutations
                    std::array<Index, HOUSE_COUNT> hobbies = base;
                    do {
                        // 7. The snail owner likes to go dancing.
                        const Index snails_idx = find_index(pets, SNAILS);
                        if (!(hobbies[snails_idx] == DANCING)) {
                            continue;
                        }

                        // 8. The person in the yellow house is a painter.
                        const Index yellow_idx = find_index(colors, YELLOW);
                        if (!(hobbies[yellow_idx] == PAINTING)) {
                            continue;
                        }

                        // 13. The person who plays football drinks orange juice.
                        const Index orange_juice_idx = find_index(drinks, ORANGE_JUICE);
                        if (!(hobbies[orange_juice_idx] == FOOTBALL)) {
                            continue;
                        }

                        // 14. The Japanese person plays chess.
                        const Index japanese_idx = find_index(nations, JAPANESE);
                        if (!(hobbies[japanese_idx] == CHESS)) {
                            continue;
                        }

                        // 11. The person who enjoys reading lives next to the person with the fox.
                        const Index reader_idx = find_index(hobbies, READING);
                        const Index fox_idx = find_index(pets, FOX);
                        if (!is_next_to(reader_idx, fox_idx)) {
                            continue;
                        }

                        // 12. The painter's house is next to the house with the horse.
                        const Index painter_idx = find_index(hobbies, PAINTING);
                        const Index horse_idx = find_index(pets, HORSE);
                        if (!is_next_to(painter_idx, horse_idx)) {
                            continue;
                        }

                        // All constraints satisfied; construct solution.
                        const Index water_idx = find_index(drinks, WATER);
                        const Index zebra_idx = find_index(pets, ZEBRA);

                        Solution sol{};
                        sol.drinksWater = nationality_to_string(nations[water_idx]);
                        sol.ownsZebra = nationality_to_string(nations[zebra_idx]);
                        return sol;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Fallback (should not happen for a well-posed puzzle)
    Solution none{};
    none.drinksWater = std::string();
    none.ownsZebra = std::string();
    return none;
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

// Problem size
static constexpr std::size_t N = 5U;

// Indices for categories
// Colors
static constexpr std::uint32_t RED = 0U;
static constexpr std::uint32_t GREEN = 1U;
static constexpr std::uint32_t IVORY = 2U;
static constexpr std::uint32_t YELLOW = 3U;
static constexpr std::uint32_t BLUE = 4U;

// Nationalities
static constexpr std::uint32_t ENGLISHMAN = 0U;
static constexpr std::uint32_t SPANIARD = 1U;
static constexpr std::uint32_t UKRAINIAN = 2U;
static constexpr std::uint32_t NORWEGIAN = 3U;
static constexpr std::uint32_t JAPANESE = 4U;

// Pets
static constexpr std::uint32_t DOG = 0U;
static constexpr std::uint32_t SNAILS = 1U;
static constexpr std::uint32_t FOX = 2U;
static constexpr std::uint32_t HORSE = 3U;
static constexpr std::uint32_t ZEBRA = 4U;

// Drinks
static constexpr std::uint32_t COFFEE = 0U;
static constexpr std::uint32_t TEA = 1U;
static constexpr std::uint32_t MILK = 2U;
static constexpr std::uint32_t ORANGE_JUICE = 3U;
static constexpr std::uint32_t WATER = 4U;

// Hobbies
static constexpr std::uint32_t DANCING = 0U;
static constexpr std::uint32_t PAINTING = 1U;
static constexpr std::uint32_t READING = 2U;
static constexpr std::uint32_t FOOTBALL = 3U;
static constexpr std::uint32_t CHESS = 4U;

using Perm = std::array<std::uint32_t, N>;

static bool is_immediately_right(std::uint32_t right_pos, std::uint32_t left_pos)
{
    return (right_pos == (left_pos + 1U));
}

static bool is_next_to(std::uint32_t a_pos, std::uint32_t b_pos)
{
    const std::uint32_t diff = (a_pos > b_pos) ? (a_pos - b_pos) : (b_pos - a_pos);
    return (diff == 1U);
}

}  // namespace

Solution solve()
{
    const std::array<std::string, N> nationality_names = {
        std::string("Englishman"),
        std::string("Spaniard"),
        std::string("Ukrainian"),
        std::string("Norwegian"),
        std::string("Japanese")
    };

    const Perm base = { { 0U, 1U, 2U, 3U, 4U } };

    Perm color = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!(is_immediately_right(color[GREEN], color[IVORY]))) {
            continue;
        }

        Perm nationality = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (!(nationality[NORWEGIAN] == 0U)) {
                continue;
            }

            // 2. The Englishman lives in the red house.
            if (!(nationality[ENGLISHMAN] == color[RED])) {
                continue;
            }

            // 15. The Norwegian lives next to the blue house.
            if (!(is_next_to(nationality[NORWEGIAN], color[BLUE]))) {
                continue;
            }

            Perm drink = base;
            do {
                // 4. The person in the green house drinks coffee.
                if (!(drink[COFFEE] == color[GREEN])) {
                    continue;
                }

                // 5. The Ukrainian drinks tea.
                if (!(drink[TEA] == nationality[UKRAINIAN])) {
                    continue;
                }

                // 9. The person in the middle house drinks milk.
                if (!(drink[MILK] == 2U)) {
                    continue;
                }

                Perm pet = base;
                do {
                    // 3. The Spaniard owns the dog.
                    if (!(pet[DOG] == nationality[SPANIARD])) {
                        continue;
                    }

                    Perm hobby = base;
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (!(hobby[DANCING] == pet[SNAILS])) {
                            continue;
                        }

                        // 8. The person in the yellow house is a painter.
                        if (!(hobby[PAINTING] == color[YELLOW])) {
                            continue;
                        }

                        // 13. The person who plays football drinks orange juice.
                        if (!(hobby[FOOTBALL] == drink[ORANGE_JUICE])) {
                            continue;
                        }

                        // 14. The Japanese person plays chess.
                        if (!(hobby[CHESS] == nationality[JAPANESE])) {
                            continue;
                        }

                        // 11. Reading lives next to the fox.
                        if (!(is_next_to(hobby[READING], pet[FOX]))) {
                            continue;
                        }

                        // 12. The painter's house is next to the house with the horse.
                        if (!(is_next_to(hobby[PAINTING], pet[HORSE]))) {
                            continue;
                        }

                        // Found a valid solution
                        const std::uint32_t water_pos = drink[WATER];
                        const std::uint32_t zebra_pos = pet[ZEBRA];

                        std::uint32_t water_nat_idx = 0U;
                        std::uint32_t zebra_nat_idx = 0U;

                        for (std::size_t k = 0U; k < N; ++k) {
                            if (nationality[k] == water_pos) {
                                water_nat_idx = static_cast<std::uint32_t>(k);
                            }
                            if (nationality[k] == zebra_pos) {
                                zebra_nat_idx = static_cast<std::uint32_t>(k);
                            }
                        }

                        Solution s{};
                        s.drinksWater = nationality_names[static_cast<std::size_t>(water_nat_idx)];
                        s.ownsZebra = nationality_names[static_cast<std::size_t>(zebra_nat_idx)];
                        return s;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nationality.begin(), nationality.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Fallback (should not happen for a well-posed puzzle)
    Solution s{};
    s.drinksWater = std::string{};
    s.ownsZebra = std::string{};
    return s;
}

}  // namespace zebra_puzzle

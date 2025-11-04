#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {
using Index = std::uint32_t;
constexpr Index N = 5U;

enum class Color : std::uint32_t { Red = 0U, Green = 1U, Ivory = 2U, Yellow = 3U, Blue = 4U };
enum class Nationality : std::uint32_t { Englishman = 0U, Spaniard = 1U, Ukrainian = 2U, Norwegian = 3U, Japanese = 4U };
enum class Pet : std::uint32_t { Dog = 0U, Fox = 1U, Horse = 2U, Snails = 3U, Zebra = 4U };
enum class Drink : std::uint32_t { Coffee = 0U, Tea = 1U, Milk = 2U, OrangeJuice = 3U, Water = 4U };
enum class Hobby : std::uint32_t { Reading = 0U, Painting = 1U, Dancing = 2U, Football = 3U, Chess = 4U };

constexpr Index idx(Color c) noexcept { return static_cast<Index>(c); }
constexpr Index idx(Nationality n) noexcept { return static_cast<Index>(n); }
constexpr Index idx(Pet p) noexcept { return static_cast<Index>(p); }
constexpr Index idx(Drink d) noexcept { return static_cast<Index>(d); }
constexpr Index idx(Hobby h) noexcept { return static_cast<Index>(h); }

inline bool is_adjacent(Index a, Index b) noexcept
{
    return ((((a > b) ? (a - b) : (b - a)) == 1U));
}

const std::array<std::string, N> kNationalityNames = {
    "Englishman",
    "Spaniard",
    "Ukrainian",
    "Norwegian",
    "Japanese"
};

}  // namespace

Solution solve()
{
    // Each array maps attribute -> house index [0..4].
    std::array<Index, N> base = {0U, 1U, 2U, 3U, 4U};

    std::array<Index, N> colorPos{};
    std::array<Index, N> natPos{};
    std::array<Index, N> drinkPos{};
    std::array<Index, N> petPos{};
    std::array<Index, N> hobbyPos{};

    colorPos = base;
    do {
        // (6) The green house is immediately to the right of the ivory house.
        if ((colorPos[idx(Color::Green)] != (colorPos[idx(Color::Ivory)] + 1U))) {
            continue;
        }

        natPos = base;
        do {
            // (10) The Norwegian lives in the first house.
            if ((natPos[idx(Nationality::Norwegian)] != 0U)) {
                continue;
            }

            // (2) The Englishman lives in the red house.
            if ((natPos[idx(Nationality::Englishman)] != colorPos[idx(Color::Red)])) {
                continue;
            }

            // (15) The Norwegian lives next to the blue house.
            if (!is_adjacent(natPos[idx(Nationality::Norwegian)], colorPos[idx(Color::Blue)])) {
                continue;
            }

            drinkPos = base;
            do {
                // (9) The person in the middle house drinks milk.
                if ((drinkPos[idx(Drink::Milk)] != 2U)) {
                    continue;
                }

                // (4) The person in the green house drinks coffee.
                if ((colorPos[idx(Color::Green)] != drinkPos[idx(Drink::Coffee)])) {
                    continue;
                }

                // (5) The Ukrainian drinks tea.
                if ((natPos[idx(Nationality::Ukrainian)] != drinkPos[idx(Drink::Tea)])) {
                    continue;
                }

                petPos = base;
                do {
                    // (3) The Spaniard owns the dog.
                    if ((natPos[idx(Nationality::Spaniard)] != petPos[idx(Pet::Dog)])) {
                        continue;
                    }

                    hobbyPos = base;
                    do {
                        // (8) The person in the yellow house is a painter.
                        if ((colorPos[idx(Color::Yellow)] != hobbyPos[idx(Hobby::Painting)])) {
                            continue;
                        }

                        // (13) The person who plays football drinks orange juice.
                        if ((hobbyPos[idx(Hobby::Football)] != drinkPos[idx(Drink::OrangeJuice)])) {
                            continue;
                        }

                        // (14) The Japanese person plays chess.
                        if ((natPos[idx(Nationality::Japanese)] != hobbyPos[idx(Hobby::Chess)])) {
                            continue;
                        }

                        // (7) The snail owner likes to go dancing.
                        if ((petPos[idx(Pet::Snails)] != hobbyPos[idx(Hobby::Dancing)])) {
                            continue;
                        }

                        // (11) The person who enjoys reading lives next to the person with the fox.
                        if (!is_adjacent(hobbyPos[idx(Hobby::Reading)], petPos[idx(Pet::Fox)])) {
                            continue;
                        }

                        // (12) The painter's house is next to the house with the horse.
                        if (!is_adjacent(hobbyPos[idx(Hobby::Painting)], petPos[idx(Pet::Horse)])) {
                            continue;
                        }

                        // All constraints satisfied: derive solution.
                        const Index waterHouse = drinkPos[idx(Drink::Water)];
                        const Index zebraHouse = petPos[idx(Pet::Zebra)];

                        Index waterNat = 0U;
                        Index zebraNat = 0U;

                        for (Index i = 0U; (i < N); ++i) {
                            if ((natPos[i] == waterHouse)) {
                                waterNat = i;
                            }
                            if ((natPos[i] == zebraHouse)) {
                                zebraNat = i;
                            }
                        }

                        Solution s{ kNationalityNames[waterNat], kNationalityNames[zebraNat] };
                        return s;

                    } while (std::next_permutation(hobbyPos.begin(), hobbyPos.end()));
                } while (std::next_permutation(petPos.begin(), petPos.end()));
            } while (std::next_permutation(drinkPos.begin(), drinkPos.end()));
        } while (std::next_permutation(natPos.begin(), natPos.end()));
    } while (std::next_permutation(colorPos.begin(), colorPos.end()));

    // Fallback (should not be reached for a well-posed puzzle).
    Solution s{ std::string{}, std::string{} };
    return s;
}

}  // namespace zebra_puzzle

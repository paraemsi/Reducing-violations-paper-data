#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>

namespace zebra_puzzle {

namespace {

// Indices for each attribute category.
enum class Color : std::size_t { Red = 0U, Green = 1U, Ivory = 2U, Yellow = 3U, Blue = 4U };
enum class Nationality : std::size_t { Englishman = 0U, Spaniard = 1U, Ukrainian = 2U, Norwegian = 3U, Japanese = 4U };
enum class Pet : std::size_t { Dog = 0U, Snails = 1U, Fox = 2U, Horse = 3U, Zebra = 4U };
enum class Drink : std::size_t { Coffee = 0U, Tea = 1U, Milk = 2U, OrangeJuice = 3U, Water = 4U };
enum class Hobby : std::size_t { Dancing = 0U, Painting = 1U, Reading = 2U, Football = 3U, Chess = 4U };

using Positions = std::array<std::size_t, 5U>;

constexpr std::array<const char*, 5U> NATIONALITY_NAMES = {
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
};

inline bool is_next_to(std::size_t a, std::size_t b) {
    return (((a + 1U) == b) || ((b + 1U) == a));
}

std::size_t nationality_at_house(const Positions& nationPos, std::size_t house) {
    for (std::size_t i = 0U; i < static_cast<std::size_t>(NATIONALITY_NAMES.size()); ++i) {
        if (nationPos[i] == house) {
            return i;
        }
    }
    return static_cast<std::size_t>(NATIONALITY_NAMES.size());
}

}  // namespace

Solution solve() {
    // House indices: 0..4 left to right. 0 is first house, 2 is middle.
    const Positions base = {0U, 1U, 2U, 3U, 4U};

    Positions colorPos = base;
    do {
        // Constraint 6: green immediately right of ivory.
        if ((colorPos[static_cast<std::size_t>(Color::Green)] != (colorPos[static_cast<std::size_t>(Color::Ivory)] + 1U))) {
            continue;
        }

        // From constraints 10 and 15: Norwegian lives in first house (0), next to blue -> blue must be at 1.
        if ((colorPos[static_cast<std::size_t>(Color::Blue)] != 1U)) {
            continue;
        }

        Positions nationPos = base;
        do {
            // Constraint 10: Norwegian lives in the first house.
            if ((nationPos[static_cast<std::size_t>(Nationality::Norwegian)] != 0U)) {
                continue;
            }

            // Constraint 2: Englishman lives in the red house.
            if ((nationPos[static_cast<std::size_t>(Nationality::Englishman)] != colorPos[static_cast<std::size_t>(Color::Red)])) {
                continue;
            }

            // Constraint 15: Norwegian lives next to the blue house.
            if (!is_next_to(nationPos[static_cast<std::size_t>(Nationality::Norwegian)],
                            colorPos[static_cast<std::size_t>(Color::Blue)])) {
                continue;
            }

            Positions drinkPos = base;
            do {
                // Constraint 9: Middle house drinks milk.
                if ((drinkPos[static_cast<std::size_t>(Drink::Milk)] != 2U)) {
                    continue;
                }

                // Constraint 4: Green house drinks coffee.
                if ((colorPos[static_cast<std::size_t>(Color::Green)] != drinkPos[static_cast<std::size_t>(Drink::Coffee)])) {
                    continue;
                }

                // Constraint 5: Ukrainian drinks tea.
                if ((nationPos[static_cast<std::size_t>(Nationality::Ukrainian)] != drinkPos[static_cast<std::size_t>(Drink::Tea)])) {
                    continue;
                }

                Positions hobbyPos = base;
                do {
                    // Constraint 8: Yellow house is a painter.
                    if ((colorPos[static_cast<std::size_t>(Color::Yellow)] != hobbyPos[static_cast<std::size_t>(Hobby::Painting)])) {
                        continue;
                    }

                    // Constraint 13: Football drinks orange juice.
                    if ((hobbyPos[static_cast<std::size_t>(Hobby::Football)] != drinkPos[static_cast<std::size_t>(Drink::OrangeJuice)])) {
                        continue;
                    }

                    // Constraint 14: Japanese plays chess.
                    if ((nationPos[static_cast<std::size_t>(Nationality::Japanese)] != hobbyPos[static_cast<std::size_t>(Hobby::Chess)])) {
                        continue;
                    }

                    Positions petPos = base;
                    do {
                        // Constraint 3: Spaniard owns the dog.
                        if ((nationPos[static_cast<std::size_t>(Nationality::Spaniard)] != petPos[static_cast<std::size_t>(Pet::Dog)])) {
                            continue;
                        }

                        // Constraint 7: Snail owner likes to go dancing.
                        if ((petPos[static_cast<std::size_t>(Pet::Snails)] != hobbyPos[static_cast<std::size_t>(Hobby::Dancing)])) {
                            continue;
                        }

                        // Constraint 12: Painter's house is next to the house with the horse.
                        if (!is_next_to(hobbyPos[static_cast<std::size_t>(Hobby::Painting)],
                                        petPos[static_cast<std::size_t>(Pet::Horse)])) {
                            continue;
                        }

                        // Constraint 11: Reading lives next to the person with the fox.
                        if (!is_next_to(hobbyPos[static_cast<std::size_t>(Hobby::Reading)],
                                        petPos[static_cast<std::size_t>(Pet::Fox)])) {
                            continue;
                        }

                        // All constraints satisfied. Determine answers.
                        const std::size_t waterHouse = drinkPos[static_cast<std::size_t>(Drink::Water)];
                        const std::size_t zebraHouse = petPos[static_cast<std::size_t>(Pet::Zebra)];

                        const std::size_t waterNatIdx = nationality_at_house(nationPos, waterHouse);
                        const std::size_t zebraNatIdx = nationality_at_house(nationPos, zebraHouse);

                        Solution result{};
                        if ((waterNatIdx < NATIONALITY_NAMES.size()) && (zebraNatIdx < NATIONALITY_NAMES.size())) {
                            result.drinksWater = std::string(NATIONALITY_NAMES[waterNatIdx]);
                            result.ownsZebra = std::string(NATIONALITY_NAMES[zebraNatIdx]);
                            return result;
                        }
                    } while (std::next_permutation(petPos.begin(), petPos.end()));
                } while (std::next_permutation(hobbyPos.begin(), hobbyPos.end()));
            } while (std::next_permutation(drinkPos.begin(), drinkPos.end()));
        } while (std::next_permutation(nationPos.begin(), nationPos.end()));
    } while (std::next_permutation(colorPos.begin(), colorPos.end()));

    // Fallback (should not happen for a well-posed puzzle).
    Solution unknown{};
    unknown.drinksWater = std::string("Unknown");
    unknown.ownsZebra = std::string("Unknown");
    return unknown;
}

}  // namespace zebra_puzzle

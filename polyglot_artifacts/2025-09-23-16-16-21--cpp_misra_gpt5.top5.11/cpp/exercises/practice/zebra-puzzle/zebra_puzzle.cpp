#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

auto solve() -> Solution {
    // Value indices:
    // Colors:       0: red, 1: green, 2: ivory, 3: yellow, 4: blue
    // Nationality:  0: Englishman, 1: Spaniard, 2: Ukrainian, 3: Norwegian, 4: Japanese
    // Pets:         0: dog, 1: snails, 2: fox, 3: horse, 4: zebra
    // Drinks:       0: coffee, 1: tea, 2: milk, 3: orange juice, 4: water
    // Hobbies:      0: dancing, 1: painter, 2: reading, 3: football, 4: chess

    std::array<std::uint8_t, 5U> colors = {0U, 1U, 2U, 3U, 4U};
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!((static_cast<std::int32_t>(colors[1U]) == (static_cast<std::int32_t>(colors[2U]) + 1)))) {
            continue;
        }

        std::array<std::uint8_t, 5U> nations = {0U, 1U, 2U, 3U, 4U};
        do {
            // 2. The Englishman lives in the red house.
            if (!(colors[0U] == nations[0U])) {
                continue;
            }
            // 10. The Norwegian lives in the first house (index 0).
            if (!(nations[3U] == static_cast<std::uint8_t>(0U))) {
                continue;
            }
            // 15. The Norwegian lives next to the blue house.
            {
                const std::int32_t diff_nb =
                    static_cast<std::int32_t>(colors[4U]) - static_cast<std::int32_t>(nations[3U]);
                if (!(((diff_nb == 1) || (diff_nb == -1)))) {
                    continue;
                }
            }

            std::array<std::uint8_t, 5U> drinks = {0U, 1U, 2U, 3U, 4U};
            do {
                // 4. The person in the green house drinks coffee.
                if (!(colors[1U] == drinks[0U])) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                if (!(nations[2U] == drinks[1U])) {
                    continue;
                }
                // 9. The person in the middle house drinks milk. (middle is index 2)
                if (!(drinks[2U] == static_cast<std::uint8_t>(2U))) {
                    continue;
                }

                std::array<std::uint8_t, 5U> pets = {0U, 1U, 2U, 3U, 4U};
                do {
                    // 3. The Spaniard owns the dog.
                    if (!(nations[1U] == pets[0U])) {
                        continue;
                    }

                    std::array<std::uint8_t, 5U> hobbies = {0U, 1U, 2U, 3U, 4U};
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (!(pets[1U] == hobbies[0U])) {
                            continue;
                        }
                        // 8. The person in the yellow house is a painter.
                        if (!(colors[3U] == hobbies[1U])) {
                            continue;
                        }
                        // 13. The person who plays football drinks orange juice.
                        if (!(hobbies[3U] == drinks[3U])) {
                            continue;
                        }
                        // 14. The Japanese person plays chess.
                        if (!(nations[4U] == hobbies[4U])) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        {
                            const std::int32_t diff_rf =
                                static_cast<std::int32_t>(hobbies[2U]) - static_cast<std::int32_t>(pets[2U]);
                            if (!(((diff_rf == 1) || (diff_rf == -1)))) {
                                continue;
                            }
                        }
                        // 12. The painter's house is next to the house with the horse.
                        {
                            const std::int32_t diff_ph =
                                static_cast<std::int32_t>(hobbies[1U]) - static_cast<std::int32_t>(pets[3U]);
                            if (!(((diff_ph == 1) || (diff_ph == -1)))) {
                                continue;
                            }
                        }

                        // All constraints satisfied: determine answers.
                        const std::uint8_t posWater = drinks[4U];
                        const std::uint8_t posZebra = pets[4U];

                        std::uint8_t whoDrinksWater = static_cast<std::uint8_t>(0U);
                        std::uint8_t whoOwnsZebra = static_cast<std::uint8_t>(0U);
                        for (std::uint8_t i = static_cast<std::uint8_t>(0U);
                             i != static_cast<std::uint8_t>(5U);
                             i = static_cast<std::uint8_t>(static_cast<std::uint16_t>(i) + static_cast<std::uint16_t>(1U))) {
                            if ((nations[static_cast<std::size_t>(i)] == posWater)) {
                                whoDrinksWater = i;
                            }
                            if ((nations[static_cast<std::size_t>(i)] == posZebra)) {
                                whoOwnsZebra = i;
                            }
                        }

                        static const std::array<const char*, 5U> nationNames = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

                        Solution sol;
                        sol.drinksWater = std::string(nationNames[static_cast<std::size_t>(whoDrinksWater)]);
                        sol.ownsZebra = std::string(nationNames[static_cast<std::size_t>(whoOwnsZebra)]);
                        return sol;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Fallback (should never happen for a well-posed puzzle)
    Solution sol;
    sol.drinksWater = std::string();
    sol.ownsZebra = std::string();
    return sol;
}

}  // namespace zebra_puzzle

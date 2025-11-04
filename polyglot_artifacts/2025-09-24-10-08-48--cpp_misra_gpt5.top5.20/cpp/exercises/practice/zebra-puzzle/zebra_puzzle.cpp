#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <cstdint>

namespace zebra_puzzle {

Solution solve()
{
    using std::uint8_t;
    using std::uint32_t;
    using Arr = std::array<uint8_t, 5U>;

    // Indices for attributes
    constexpr std::size_t RED = 0U;
    constexpr std::size_t GREEN = 1U;
    constexpr std::size_t IVORY = 2U;
    constexpr std::size_t YELLOW = 3U;
    constexpr std::size_t BLUE = 4U;

    constexpr std::size_t ENGLISH = 0U;
    constexpr std::size_t SPANIARD = 1U;
    constexpr std::size_t UKRAINIAN = 2U;
    constexpr std::size_t NORWEGIAN = 3U;
    constexpr std::size_t JAPANESE = 4U;

    constexpr std::size_t DOG = 0U;
    constexpr std::size_t SNAILS = 1U;
    constexpr std::size_t FOX = 2U;
    constexpr std::size_t HORSE = 3U;
    constexpr std::size_t ZEBRA = 4U;

    constexpr std::size_t COFFEE = 0U;
    constexpr std::size_t TEA = 1U;
    constexpr std::size_t MILK = 2U;
    constexpr std::size_t ORANGE = 3U;
    constexpr std::size_t WATER = 4U;

    constexpr std::size_t DANCING = 0U;
    constexpr std::size_t PAINTING = 1U;
    constexpr std::size_t READING = 2U;
    constexpr std::size_t FOOTBALL = 3U;
    constexpr std::size_t CHESS = 4U;

    auto is_right_of = [](uint8_t a, uint8_t b) -> bool {
        const uint32_t au = static_cast<uint32_t>(a);
        const uint32_t bu = static_cast<uint32_t>(b);
        return (au == (bu + 1U));
    };
    auto is_next_to = [](uint8_t a, uint8_t b) -> bool {
        const uint32_t au = static_cast<uint32_t>(a);
        const uint32_t bu = static_cast<uint32_t>(b);
        return ((au + 1U == bu) || (bu + 1U == au));
    };
    auto owner_of_position = [](const Arr& arr, uint8_t pos) -> uint8_t {
        uint8_t i = 0U;
        while (i < 5U) {
            if (arr[static_cast<std::size_t>(i)] == pos) {
                return i;
            } else {
                // continue
            }
            i = static_cast<uint8_t>(static_cast<uint32_t>(i) + 1U);
        }
        return 0U;  // Unreachable in valid solution
    };

    Arr base = {0U, 1U, 2U, 3U, 4U};

    Arr colors = base;
    do {
        // 6. Green is immediately to the right of Ivory.
        if (!is_right_of(colors[GREEN], colors[IVORY])) {
            continue;
        }

        Arr nations = base;
        do {
            // 10. Norwegian lives in the first house.
            if (!(nations[NORWEGIAN] == 0U)) {
                continue;
            }
            // 2. Englishman lives in the red house.
            if (!(nations[ENGLISH] == colors[RED])) {
                continue;
            }
            // 15. Norwegian lives next to the blue house.
            if (!is_next_to(nations[NORWEGIAN], colors[BLUE])) {
                continue;
            }

            Arr drinks = base;
            do {
                // 9. Middle house drinks milk.
                if (!(drinks[MILK] == 2U)) {
                    continue;
                }
                // 4. Green house drinks coffee.
                if (!(colors[GREEN] == drinks[COFFEE])) {
                    continue;
                }
                // 5. Ukrainian drinks tea.
                if (!(nations[UKRAINIAN] == drinks[TEA])) {
                    continue;
                }

                Arr hobbies = base;
                do {
                    // 8. Yellow house is a painter.
                    if (!(colors[YELLOW] == hobbies[PAINTING])) {
                        continue;
                    }
                    // 14. Japanese person plays chess.
                    if (!(nations[JAPANESE] == hobbies[CHESS])) {
                        continue;
                    }
                    // 13. Football player drinks orange juice.
                    if (!(hobbies[FOOTBALL] == drinks[ORANGE])) {
                        continue;
                    }

                    Arr pets = base;
                    do {
                        // 3. Spaniard owns the dog.
                        if (!(nations[SPANIARD] == pets[DOG])) {
                            continue;
                        }
                        // 7. Snail owner likes to go dancing.
                        if (!(pets[SNAILS] == hobbies[DANCING])) {
                            continue;
                        }
                        // 11. Reader lives next to the fox owner.
                        if (!is_next_to(hobbies[READING], pets[FOX])) {
                            continue;
                        }
                        // 12. Painter's house is next to the horse.
                        if (!is_next_to(hobbies[PAINTING], pets[HORSE])) {
                            continue;
                        }

                        // Build and return the solution.
                        const uint8_t waterPos = drinks[WATER];
                        const uint8_t zebraPos = pets[ZEBRA];
                        const uint8_t waterNationIdx = owner_of_position(nations, waterPos);
                        const uint8_t zebraNationIdx = owner_of_position(nations, zebraPos);

                        static const std::array<const char*, 5U> NationNames = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        Solution s{};
                        s.drinksWater = std::string(NationNames[static_cast<std::size_t>(waterNationIdx)]);
                        s.ownsZebra = std::string(NationNames[static_cast<std::size_t>(zebraNationIdx)]);
                        return s;

                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Fallback; should never be reached if constraints are consistent.
    Solution s{};
    s.drinksWater = std::string();
    s.ownsZebra = std::string();
    return s;
}

}  // namespace zebra_puzzle

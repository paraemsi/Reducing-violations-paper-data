#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace {

enum class Color : std::uint8_t { Red = 0U, Green = 1U, Ivory = 2U, Yellow = 3U, Blue = 4U };
enum class Nationality : std::uint8_t { Englishman = 0U, Spaniard = 1U, Ukrainian = 2U, Norwegian = 3U, Japanese = 4U };
enum class Pet : std::uint8_t { Dog = 0U, Fox = 1U, Snails = 2U, Horse = 3U, Zebra = 4U };
enum class Drink : std::uint8_t { Coffee = 0U, Tea = 1U, Milk = 2U, OrangeJuice = 3U, Water = 4U };
enum class Hobby : std::uint8_t { Dancing = 0U, Painting = 1U, Reading = 2U, Football = 3U, Chess = 4U };

static bool right_of(std::uint8_t a, std::uint8_t b) {
    std::int32_t diff = static_cast<std::int32_t>(a) - static_cast<std::int32_t>(b);
    return (diff == static_cast<std::int32_t>(1));
}

static bool adjacent(std::uint8_t a, std::uint8_t b) {
    std::int32_t diff = static_cast<std::int32_t>(a) - static_cast<std::int32_t>(b);
    return ((diff == static_cast<std::int32_t>(1)) || (diff == static_cast<std::int32_t>(-1)));
}

}  // namespace

namespace zebra_puzzle {

Solution solve() {
    // Positions are 0..4 from left to right
    std::array<std::uint8_t, 5U> colors = {0U, 1U, 2U, 3U, 4U};
    std::array<std::uint8_t, 5U> nats = {0U, 1U, 2U, 3U, 4U};
    std::array<std::uint8_t, 5U> pets = {0U, 1U, 2U, 3U, 4U};
    std::array<std::uint8_t, 5U> drinks = {0U, 1U, 2U, 3U, 4U};
    std::array<std::uint8_t, 5U> hobbies = {0U, 1U, 2U, 3U, 4U};

    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!(right_of(colors[static_cast<std::size_t>(Color::Green)], colors[static_cast<std::size_t>(Color::Ivory)]))) {
            continue;
        }

        do {
            // 10. The Norwegian lives in the first house.
            if (!(nats[static_cast<std::size_t>(Nationality::Norwegian)] == static_cast<std::uint8_t>(0U))) {
                continue;
            }

            // 2. The Englishman lives in the red house.
            if (!(nats[static_cast<std::size_t>(Nationality::Englishman)] == colors[static_cast<std::size_t>(Color::Red)])) {
                continue;
            }

            // 15. The Norwegian lives next to the blue house.
            if (!(adjacent(nats[static_cast<std::size_t>(Nationality::Norwegian)], colors[static_cast<std::size_t>(Color::Blue)]))) {
                continue;
            }

            do {
                // 9. The person in the middle house drinks milk. (0-based index 2)
                if (!(drinks[static_cast<std::size_t>(Drink::Milk)] == static_cast<std::uint8_t>(2U))) {
                    continue;
                }

                // 4. The person in the green house drinks coffee.
                if (!(colors[static_cast<std::size_t>(Color::Green)] == drinks[static_cast<std::size_t>(Drink::Coffee)])) {
                    continue;
                }

                // 5. The Ukrainian drinks tea.
                if (!(nats[static_cast<std::size_t>(Nationality::Ukrainian)] == drinks[static_cast<std::size_t>(Drink::Tea)])) {
                    continue;
                }

                do {
                    // 8. The person in the yellow house is a painter.
                    if (!(colors[static_cast<std::size_t>(Color::Yellow)] == hobbies[static_cast<std::size_t>(Hobby::Painting)])) {
                        continue;
                    }

                    // 14. The Japanese person plays chess.
                    if (!(nats[static_cast<std::size_t>(Nationality::Japanese)] == hobbies[static_cast<std::size_t>(Hobby::Chess)])) {
                        continue;
                    }

                    // 13. The person who plays football drinks orange juice.
                    if (!(hobbies[static_cast<std::size_t>(Hobby::Football)] == drinks[static_cast<std::size_t>(Drink::OrangeJuice)])) {
                        continue;
                    }

                    do {
                        // 3. The Spaniard owns the dog.
                        if (!(nats[static_cast<std::size_t>(Nationality::Spaniard)] == pets[static_cast<std::size_t>(Pet::Dog)])) {
                            continue;
                        }

                        // 7. The snail owner likes to go dancing.
                        if (!(pets[static_cast<std::size_t>(Pet::Snails)] == hobbies[static_cast<std::size_t>(Hobby::Dancing)])) {
                            continue;
                        }

                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!(adjacent(hobbies[static_cast<std::size_t>(Hobby::Reading)], pets[static_cast<std::size_t>(Pet::Fox)]))) {
                            continue;
                        }

                        // 12. The painter's house is next to the house with the horse.
                        if (!(adjacent(hobbies[static_cast<std::size_t>(Hobby::Painting)], pets[static_cast<std::size_t>(Pet::Horse)]))) {
                            continue;
                        }

                        // All constraints satisfied; construct solution
                        std::array<std::uint8_t, 5U> nat_at_pos = {0U, 0U, 0U, 0U, 0U};
                        for (std::size_t ni = 0U; (ni < static_cast<std::size_t>(5U)); ni++) {
                            std::uint8_t pos_of_nat = nats[ni];
                            nat_at_pos[static_cast<std::size_t>(pos_of_nat)] = static_cast<std::uint8_t>(ni);
                        }

                        const std::array<std::string, 5U> nat_names = {
                            std::string("Englishman"),
                            std::string("Spaniard"),
                            std::string("Ukrainian"),
                            std::string("Norwegian"),
                            std::string("Japanese")
                        };

                        std::uint8_t water_pos = drinks[static_cast<std::size_t>(Drink::Water)];
                        std::uint8_t zebra_pos = pets[static_cast<std::size_t>(Pet::Zebra)];

                        std::uint8_t water_nat_idx = nat_at_pos[static_cast<std::size_t>(water_pos)];
                        std::uint8_t zebra_nat_idx = nat_at_pos[static_cast<std::size_t>(zebra_pos)];

                        Solution s;
                        s.drinksWater = nat_names[static_cast<std::size_t>(water_nat_idx)];
                        s.ownsZebra = nat_names[static_cast<std::size_t>(zebra_nat_idx)];
                        return s;
                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nats.begin(), nats.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Fallback (should not be reached for the canonical puzzle)
    Solution none;
    none.drinksWater = std::string();
    none.ownsZebra = std::string();
    return none;
}

}  // namespace zebra_puzzle

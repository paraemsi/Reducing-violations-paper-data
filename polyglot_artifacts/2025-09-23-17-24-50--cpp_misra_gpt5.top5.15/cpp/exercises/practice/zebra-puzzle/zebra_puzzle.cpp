#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

enum class Color : std::uint8_t { Red = 0U, Green = 1U, Ivory = 2U, Yellow = 3U, Blue = 4U };
enum class Nat : std::uint8_t { Englishman = 0U, Spaniard = 1U, Ukrainian = 2U, Japanese = 3U, Norwegian = 4U };
enum class Pet : std::uint8_t { Dog = 0U, Snails = 1U, Fox = 2U, Horse = 3U, Zebra = 4U };
enum class Drink : std::uint8_t { Coffee = 0U, Tea = 1U, Milk = 2U, OrangeJuice = 3U, Water = 4U };
enum class Hobby : std::uint8_t { Dancing = 0U, Painting = 1U, Reading = 2U, Football = 3U, Chess = 4U };

constexpr std::size_t idx(Color c) noexcept { return static_cast<std::size_t>(c); }
constexpr std::size_t idx(Nat n) noexcept { return static_cast<std::size_t>(n); }
constexpr std::size_t idx(Pet p) noexcept { return static_cast<std::size_t>(p); }
constexpr std::size_t idx(Drink d) noexcept { return static_cast<std::size_t>(d); }
constexpr std::size_t idx(Hobby h) noexcept { return static_cast<std::size_t>(h); }

using Perm = std::array<std::uint8_t, 5U>;

inline bool is_adjacent(std::uint8_t a, std::uint8_t b) noexcept {
    return (((static_cast<std::uint8_t>(a + 1U)) == b) || ((static_cast<std::uint8_t>(b + 1U)) == a));
}

std::string nat_name(Nat n) {
    switch (n) {
        case Nat::Englishman: { return std::string("Englishman"); }
        case Nat::Spaniard: { return std::string("Spaniard"); }
        case Nat::Ukrainian: { return std::string("Ukrainian"); }
        case Nat::Japanese: { return std::string("Japanese"); }
        case Nat::Norwegian: { return std::string("Norwegian"); }
        default: { return std::string(""); }
    }
}

}  // namespace

Solution solve() {
    Perm colors = { 0U, 1U, 2U, 3U, 4U };
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (!((colors[idx(Color::Green)] == static_cast<std::uint8_t>(colors[idx(Color::Ivory)] + 1U)))) {
            continue;
        }

        Perm nats = { 0U, 1U, 2U, 3U, 4U };
        do {
            // 10. The Norwegian lives in the first house.
            if (!((nats[idx(Nat::Norwegian)] == 0U))) {
                continue;
            }
            // 15. The Norwegian lives next to the blue house.
            if (!(is_adjacent(nats[idx(Nat::Norwegian)], colors[idx(Color::Blue)]))) {
                continue;
            }
            // 2. The Englishman lives in the red house.
            if (!((nats[idx(Nat::Englishman)] == colors[idx(Color::Red)]))) {
                continue;
            }

            Perm drinks = { 0U, 1U, 2U, 3U, 4U };
            do {
                // 9. The person in the middle house drinks milk.
                if (!((drinks[idx(Drink::Milk)] == 2U))) {
                    continue;
                }
                // 4. The person in the green house drinks coffee.
                if (!((colors[idx(Color::Green)] == drinks[idx(Drink::Coffee)]))) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                if (!((nats[idx(Nat::Ukrainian)] == drinks[idx(Drink::Tea)]))) {
                    continue;
                }

                Perm pets = { 0U, 1U, 2U, 3U, 4U };
                do {
                    // 3. The Spaniard owns the dog.
                    if (!((nats[idx(Nat::Spaniard)] == pets[idx(Pet::Dog)]))) {
                        continue;
                    }

                    Perm hobbies = { 0U, 1U, 2U, 3U, 4U };
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (!((pets[idx(Pet::Snails)] == hobbies[idx(Hobby::Dancing)]))) {
                            continue;
                        }
                        // 8. The person in the yellow house is a painter.
                        if (!((colors[idx(Color::Yellow)] == hobbies[idx(Hobby::Painting)]))) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!(is_adjacent(hobbies[idx(Hobby::Reading)], pets[idx(Pet::Fox)]))) {
                            continue;
                        }
                        // 12. The painter's house is next to the house with the horse.
                        if (!(is_adjacent(hobbies[idx(Hobby::Painting)], pets[idx(Pet::Horse)]))) {
                            continue;
                        }
                        // 13. The person who plays football drinks orange juice.
                        if (!((hobbies[idx(Hobby::Football)] == drinks[idx(Drink::OrangeJuice)]))) {
                            continue;
                        }
                        // 14. The Japanese person plays chess.
                        if (!((nats[idx(Nat::Japanese)] == hobbies[idx(Hobby::Chess)]))) {
                            continue;
                        }

                        // Identify nationalities for water drinker and zebra owner
                        const std::uint8_t water_house = drinks[idx(Drink::Water)];
                        const std::uint8_t zebra_house = pets[idx(Pet::Zebra)];

                        Nat water_nat = Nat::Englishman;
                        Nat zebra_nat = Nat::Englishman;

                        if ((nats[idx(Nat::Englishman)] == water_house)) {
                            water_nat = Nat::Englishman;
                        } else if ((nats[idx(Nat::Spaniard)] == water_house)) {
                            water_nat = Nat::Spaniard;
                        } else if ((nats[idx(Nat::Ukrainian)] == water_house)) {
                            water_nat = Nat::Ukrainian;
                        } else if ((nats[idx(Nat::Japanese)] == water_house)) {
                            water_nat = Nat::Japanese;
                        } else if ((nats[idx(Nat::Norwegian)] == water_house)) {
                            water_nat = Nat::Norwegian;
                        } else {
                            continue;
                        }

                        if ((nats[idx(Nat::Englishman)] == zebra_house)) {
                            zebra_nat = Nat::Englishman;
                        } else if ((nats[idx(Nat::Spaniard)] == zebra_house)) {
                            zebra_nat = Nat::Spaniard;
                        } else if ((nats[idx(Nat::Ukrainian)] == zebra_house)) {
                            zebra_nat = Nat::Ukrainian;
                        } else if ((nats[idx(Nat::Japanese)] == zebra_house)) {
                            zebra_nat = Nat::Japanese;
                        } else if ((nats[idx(Nat::Norwegian)] == zebra_house)) {
                            zebra_nat = Nat::Norwegian;
                        } else {
                            continue;
                        }

                        Solution s;
                        s.drinksWater = nat_name(water_nat);
                        s.ownsZebra = nat_name(zebra_nat);
                        return s;
                    } while ((std::next_permutation(hobbies.begin(), hobbies.end())));
                } while ((std::next_permutation(pets.begin(), pets.end())));
            } while ((std::next_permutation(drinks.begin(), drinks.end())));
        } while ((std::next_permutation(nats.begin(), nats.end())));
    } while ((std::next_permutation(colors.begin(), colors.end())));

    // No solution found (should not happen)
    Solution s;
    s.drinksWater = std::string();
    s.ownsZebra = std::string();
    return s;
}

}  // namespace zebra_puzzle

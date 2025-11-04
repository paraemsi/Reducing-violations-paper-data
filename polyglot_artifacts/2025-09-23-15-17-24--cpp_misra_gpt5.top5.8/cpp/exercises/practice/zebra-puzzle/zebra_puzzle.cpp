#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

// Constants for counts
static constexpr std::uint8_t HOUSE_COUNT = 5U;

// Attribute identifiers (0..4)
static constexpr std::uint8_t COLOR_RED    = 0U;
static constexpr std::uint8_t COLOR_GREEN  = 1U;
static constexpr std::uint8_t COLOR_IVORY  = 2U;
static constexpr std::uint8_t COLOR_YELLOW = 3U;
static constexpr std::uint8_t COLOR_BLUE   = 4U;

static constexpr std::uint8_t NAT_ENGLISHMAN = 0U;
static constexpr std::uint8_t NAT_SPANIARD   = 1U;
static constexpr std::uint8_t NAT_UKRAINIAN  = 2U;
static constexpr std::uint8_t NAT_NORWEGIAN  = 3U;
static constexpr std::uint8_t NAT_JAPANESE   = 4U;

static constexpr std::uint8_t PET_DOG    = 0U;
static constexpr std::uint8_t PET_SNAILS = 1U;
static constexpr std::uint8_t PET_FOX    = 2U;
static constexpr std::uint8_t PET_HORSE  = 3U;
static constexpr std::uint8_t PET_ZEBRA  = 4U;

static constexpr std::uint8_t DRINK_COFFEE       = 0U;
static constexpr std::uint8_t DRINK_TEA          = 1U;
static constexpr std::uint8_t DRINK_MILK         = 2U;
static constexpr std::uint8_t DRINK_ORANGE_JUICE = 3U;
static constexpr std::uint8_t DRINK_WATER        = 4U;

static constexpr std::uint8_t HOBBY_PAINTING = 0U;
static constexpr std::uint8_t HOBBY_DANCING  = 1U;
static constexpr std::uint8_t HOBBY_READING  = 2U;
static constexpr std::uint8_t HOBBY_FOOTBALL = 3U;
static constexpr std::uint8_t HOBBY_CHESS    = 4U;

static constexpr std::array<std::uint8_t, HOUSE_COUNT> identity() noexcept {
    return std::array<std::uint8_t, HOUSE_COUNT>{0U, 1U, 2U, 3U, 4U};
}

static std::uint8_t find_index(const std::array<std::uint8_t, HOUSE_COUNT>& arr, std::uint8_t value) noexcept {
    for (std::uint8_t i = 0U; i < HOUSE_COUNT; ++i) {
        if (arr[static_cast<std::size_t>(i)] == value) {
            return i;
        }
    }
    // Should never happen for valid permutations
    return HOUSE_COUNT;
}

static bool is_next_to(std::uint8_t a, std::uint8_t b) noexcept {
    return ((a + 1U) == b) || ((b + 1U) == a);
}

static std::string nat_to_string(std::uint8_t nat) {
    switch (nat) {
        case NAT_ENGLISHMAN: {
            return std::string("Englishman");
        }
        case NAT_SPANIARD: {
            return std::string("Spaniard");
        }
        case NAT_UKRAINIAN: {
            return std::string("Ukrainian");
        }
        case NAT_NORWEGIAN: {
            return std::string("Norwegian");
        }
        case NAT_JAPANESE: {
            return std::string("Japanese");
        }
        default: {
            return std::string();
        }
    }
}

}  // namespace


Solution solve() {
    // Permute colors first with strong constraints to prune early
    std::array<std::uint8_t, HOUSE_COUNT> colors = identity();
    do {
        // Constraint 6: Green house immediately to the right of ivory house
        const std::uint8_t posGreen = find_index(colors, COLOR_GREEN);
        const std::uint8_t posIvory = find_index(colors, COLOR_IVORY);
        if (!(posGreen == (posIvory + 1U))) {
            continue;
        }

        // Constraint 15 + 10 (Norwegian in first house neighbors blue house)
        const std::uint8_t posBlue = find_index(colors, COLOR_BLUE);
        if (!is_next_to(posBlue, 0U)) {
            continue;
        }

        // Now permute nationalities with early checks
        std::array<std::uint8_t, HOUSE_COUNT> nat = identity();
        do {
            // Constraint 10: Norwegian in first house
            if (!(nat[0U] == NAT_NORWEGIAN)) {
                continue;
            }

            // Constraint 2: Englishman lives in the red house
            const std::uint8_t posEnglish = find_index(nat, NAT_ENGLISHMAN);
            if (!(colors[static_cast<std::size_t>(posEnglish)] == COLOR_RED)) {
                continue;
            }

            // We will need some positions later
            const std::uint8_t posSpaniard  = find_index(nat, NAT_SPANIARD);
            const std::uint8_t posJapanese  = find_index(nat, NAT_JAPANESE);
            const std::uint8_t posUkrainian = find_index(nat, NAT_UKRAINIAN);

            // Constraint 15 again (already pruned by colors), keep for clarity:
            if (!is_next_to(posBlue, 0U)) {
                continue;
            }

            // Pets
            std::array<std::uint8_t, HOUSE_COUNT> pets = identity();
            do {
                // Constraint 3: Spaniard owns the dog
                if (!(pets[static_cast<std::size_t>(posSpaniard)] == PET_DOG)) {
                    continue;
                }

                // Drinks
                std::array<std::uint8_t, HOUSE_COUNT> drinks = identity();
                do {
                    // Constraint 9: Middle house drinks milk
                    if (!(drinks[2U] == DRINK_MILK)) {
                        continue;
                    }

                    // Constraint 5: Ukrainian drinks tea
                    if (!(drinks[static_cast<std::size_t>(posUkrainian)] == DRINK_TEA)) {
                        continue;
                    }

                    // Constraint 4: Green house drinks coffee
                    if (!(drinks[static_cast<std::size_t>(posGreen)] == DRINK_COFFEE)) {
                        continue;
                    }

                    // Hobbies
                    std::array<std::uint8_t, HOUSE_COUNT> hobbies = identity();
                    do {
                        // Constraint 8: Yellow house painter
                        const std::uint8_t posYellow = find_index(colors, COLOR_YELLOW);
                        if (!(hobbies[static_cast<std::size_t>(posYellow)] == HOBBY_PAINTING)) {
                            continue;
                        }

                        // Constraint 7: Snail owner likes dancing
                        const std::uint8_t posSnails = find_index(pets, PET_SNAILS);
                        if (!(hobbies[static_cast<std::size_t>(posSnails)] == HOBBY_DANCING)) {
                            continue;
                        }

                        // Constraint 14: Japanese plays chess
                        if (!(hobbies[static_cast<std::size_t>(posJapanese)] == HOBBY_CHESS)) {
                            continue;
                        }

                        // Constraint 13: Football drinks orange juice
                        const std::uint8_t posFootball = find_index(hobbies, HOBBY_FOOTBALL);
                        if (!(drinks[static_cast<std::size_t>(posFootball)] == DRINK_ORANGE_JUICE)) {
                            continue;
                        }

                        // Constraint 11: Reading next to fox
                        const std::uint8_t posReading = find_index(hobbies, HOBBY_READING);
                        const std::uint8_t posFox     = find_index(pets, PET_FOX);
                        if (!is_next_to(posReading, posFox)) {
                            continue;
                        }

                        // Constraint 12: Painter's house next to horse
                        const std::uint8_t posPainter = find_index(hobbies, HOBBY_PAINTING);
                        const std::uint8_t posHorse   = find_index(pets, PET_HORSE);
                        if (!is_next_to(posPainter, posHorse)) {
                            continue;
                        }

                        // All constraints satisfied; build the solution
                        const std::uint8_t posWater = find_index(drinks, DRINK_WATER);
                        const std::uint8_t posZebra = find_index(pets, PET_ZEBRA);

                        Solution s{};
                        s.drinksWater = nat_to_string(nat[static_cast<std::size_t>(posWater)]);
                        s.ownsZebra = nat_to_string(nat[static_cast<std::size_t>(posZebra)]);
                        return s;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(drinks.begin(), drinks.end()));
            } while (std::next_permutation(pets.begin(), pets.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Should never reach here for a well-posed puzzle
    return Solution{};
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

// Fixed-width integer constants for clarity/compliance
constexpr std::int32_t N{5};
constexpr std::int32_t ZERO{0};
constexpr std::int32_t ONE{1};
constexpr std::int32_t TWO{2};

// Indices for each attribute domain
// Colors
constexpr std::int32_t RED{0};
constexpr std::int32_t GREEN{1};
constexpr std::int32_t IVORY{2};
constexpr std::int32_t YELLOW{3};
constexpr std::int32_t BLUE{4};

// Nationalities
constexpr std::int32_t ENGLISH{0};
constexpr std::int32_t SPANIARD{1};
constexpr std::int32_t UKRAINIAN{2};
constexpr std::int32_t NORWEGIAN{3};
constexpr std::int32_t JAPANESE{4};

// Pets
constexpr std::int32_t DOG{0};
constexpr std::int32_t FOX{1};
constexpr std::int32_t HORSE{2};
constexpr std::int32_t SNAILS{3};
constexpr std::int32_t ZEBRA{4};

// Drinks
constexpr std::int32_t COFFEE{0};
constexpr std::int32_t TEA{1};
constexpr std::int32_t MILK{2};
constexpr std::int32_t ORANGE_JUICE{3};
constexpr std::int32_t WATER{4};

// Hobbies
constexpr std::int32_t DANCING{0};
constexpr std::int32_t PAINTING{1};
constexpr std::int32_t READING{2};
constexpr std::int32_t FOOTBALL{3};
constexpr std::int32_t CHESS{4};

inline bool is_neighbor(const std::int32_t a, const std::int32_t b) noexcept
{
    return ((a == (b + ONE)) || (b == (a + ONE)));
}

}  // namespace

Solution solve()
{
    // Positions arrays map attribute ID -> house index (0..4, left to right)
    const std::array<std::int32_t, N> base{{ZERO, ONE, TWO, static_cast<std::int32_t>(3), static_cast<std::int32_t>(4)}};

    // Name mapping for nationalities
    const std::array<std::string, N> nationality_names{
        {std::string("Englishman"), std::string("Spaniard"), std::string("Ukrainian"), std::string("Norwegian"), std::string("Japanese")}
    };

    std::array<std::int32_t, N> color_pos = base;
    do {
        // Constraint 6: Green is immediately to the right of Ivory
        if ((color_pos[GREEN] != (color_pos[IVORY] + ONE))) {
            continue;
        }
        // Constraints 10 and 15 imply Blue must be in house 1 (second house)
        if ((color_pos[BLUE] != ONE)) {
            continue;
        }

        std::array<std::int32_t, N> nat_pos = base;
        do {
            // Constraint 10: Norwegian lives in the first house (index 0)
            if ((nat_pos[NORWEGIAN] != ZERO)) {
                continue;
            }
            // Constraint 2: Englishman lives in the red house
            if ((nat_pos[ENGLISH] != color_pos[RED])) {
                continue;
            }
            // Constraint 15: Norwegian lives next to the blue house
            if (!is_neighbor(nat_pos[NORWEGIAN], color_pos[BLUE])) {
                continue;
            }

            std::array<std::int32_t, N> drink_pos = base;
            do {
                // Constraint 9: Middle house (index 2) drinks milk
                if ((drink_pos[MILK] != TWO)) {
                    continue;
                }
                // Constraint 4: Green house drinks coffee
                if ((drink_pos[COFFEE] != color_pos[GREEN])) {
                    continue;
                }
                // Constraint 5: Ukrainian drinks tea
                if ((drink_pos[TEA] != nat_pos[UKRAINIAN])) {
                    continue;
                }

                std::array<std::int32_t, N> hobby_pos = base;
                do {
                    // Constraint 8: Yellow house is a painter
                    if ((hobby_pos[PAINTING] != color_pos[YELLOW])) {
                        continue;
                    }
                    // Constraint 13: Plays football drinks orange juice
                    if ((hobby_pos[FOOTBALL] != drink_pos[ORANGE_JUICE])) {
                        continue;
                    }
                    // Constraint 14: Japanese person plays chess
                    if ((hobby_pos[CHESS] != nat_pos[JAPANESE])) {
                        continue;
                    }

                    std::array<std::int32_t, N> pet_pos = base;
                    do {
                        // Constraint 3: Spaniard owns the dog
                        if ((pet_pos[DOG] != nat_pos[SPANIARD])) {
                            continue;
                        }
                        // Constraint 7: Snail owner likes to go dancing
                        if ((pet_pos[SNAILS] != hobby_pos[DANCING])) {
                            continue;
                        }
                        // Constraint 11: Reading lives next to the fox
                        if (!is_neighbor(hobby_pos[READING], pet_pos[FOX])) {
                            continue;
                        }
                        // Constraint 12: Painter's house is next to the horse
                        if (!is_neighbor(hobby_pos[PAINTING], pet_pos[HORSE])) {
                            continue;
                        }

                        // All constraints satisfied; derive answers
                        const std::int32_t water_house = drink_pos[WATER];
                        const std::int32_t zebra_house = pet_pos[ZEBRA];

                        Solution sol{};
                        sol.drinksWater = nationality_names[static_cast<std::size_t>([&]() {
                            // Find which nationality lives at water_house
                            for (std::int32_t i = ZERO; i < N; i = static_cast<std::int32_t>(i + ONE)) {
                                if ((nat_pos[static_cast<std::size_t>(i)] == water_house)) {
                                    return i;
                                }
                            }
                            return ZERO;  // Unreachable in valid solution
                        }())];

                        sol.ownsZebra = nationality_names[static_cast<std::size_t>([&]() {
                            // Find which nationality lives at zebra_house
                            for (std::int32_t i = ZERO; i < N; i = static_cast<std::int32_t>(i + ONE)) {
                                if ((nat_pos[static_cast<std::size_t>(i)] == zebra_house)) {
                                    return i;
                                }
                            }
                            return ZERO;  // Unreachable in valid solution
                        }())];

                        return sol;

                    } while (std::next_permutation(pet_pos.begin(), pet_pos.end()));
                } while (std::next_permutation(hobby_pos.begin(), hobby_pos.end()));
            } while (std::next_permutation(drink_pos.begin(), drink_pos.end()));
        } while (std::next_permutation(nat_pos.begin(), nat_pos.end()));
    } while (std::next_permutation(color_pos.begin(), color_pos.end()));

    // Fallback (should not happen for a well-posed puzzle)
    Solution fallback{};
    fallback.drinksWater = std::string();
    fallback.ownsZebra = std::string();
    return fallback;
}

}  // namespace zebra_puzzle

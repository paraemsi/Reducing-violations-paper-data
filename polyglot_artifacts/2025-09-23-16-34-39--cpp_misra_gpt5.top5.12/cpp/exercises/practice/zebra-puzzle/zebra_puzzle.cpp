#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

namespace zebra_puzzle {

namespace {

// Fixed-size counts
constexpr std::size_t HOUSES{5U};

// Categories encoded as fixed-width integers (indices 0..4)
constexpr std::uint8_t NAT_ENGLISH{0U};
constexpr std::uint8_t NAT_SPANIARD{1U};
constexpr std::uint8_t NAT_UKRAINIAN{2U};
constexpr std::uint8_t NAT_NORWEGIAN{3U};
constexpr std::uint8_t NAT_JAPANESE{4U};

constexpr std::uint8_t COL_RED{0U};
constexpr std::uint8_t COL_GREEN{1U};
constexpr std::uint8_t COL_IVORY{2U};
constexpr std::uint8_t COL_YELLOW{3U};
constexpr std::uint8_t COL_BLUE{4U};

constexpr std::uint8_t PET_DOG{0U};
constexpr std::uint8_t PET_SNAILS{1U};
constexpr std::uint8_t PET_FOX{2U};
constexpr std::uint8_t PET_HORSE{3U};
constexpr std::uint8_t PET_ZEBRA{4U};

constexpr std::uint8_t DRINK_COFFEE{0U};
constexpr std::uint8_t DRINK_TEA{1U};
constexpr std::uint8_t DRINK_MILK{2U};
constexpr std::uint8_t DRINK_ORANGE_JUICE{3U};
constexpr std::uint8_t DRINK_WATER{4U};

constexpr std::uint8_t HOBBY_DANCING{0U};
constexpr std::uint8_t HOBBY_PAINTING{1U};
constexpr std::uint8_t HOBBY_READING{2U};
constexpr std::uint8_t HOBBY_FOOTBALL{3U};
constexpr std::uint8_t HOBBY_CHESS{4U};

constexpr std::uint8_t UNASSIGNED{static_cast<std::uint8_t>(255U)};

inline auto is_neighbor(std::size_t a, std::size_t b) -> bool {
    if (a > 0U) {
        if (((a - 1U) == b)) {
            return true;
        }
    }
    if ((a + 1U) < HOUSES) {
        if (((a + 1U) == b)) {
            return true;
        }
    }
    return false;
}

inline auto index_of(const std::array<std::uint8_t, HOUSES>& arr, std::uint8_t value) -> std::size_t {
    for (std::size_t i{0U}; i < HOUSES; ++i) {
        if ((arr[i] == value)) {
            return i;
        }
    }
    return HOUSES;  // Not found (should not happen in valid states)
}

inline auto nat_to_string(std::uint8_t nat) -> std::string {
    switch (nat) {
        case NAT_ENGLISH: {
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
            return std::string("Unknown");
        }
    }
}

}  // namespace

auto solve() -> Solution {
    // Prepare base sequences to permute
    std::array<std::uint8_t, HOUSES> nat{{NAT_ENGLISH, NAT_SPANIARD, NAT_UKRAINIAN, NAT_NORWEGIAN, NAT_JAPANESE}};
    std::array<std::uint8_t, HOUSES> pets_base{{PET_DOG, PET_SNAILS, PET_FOX, PET_HORSE, PET_ZEBRA}};

    // Iterate all nationality permutations with Norwegian fixed in the first house (index 0)
    std::sort(nat.begin(), nat.end());
    do {
        if ((nat[0U] != NAT_NORWEGIAN)) {
            continue;
        }

        // Enumerate color arrangements satisfying:
        // - The green house is immediately to the right of the ivory house.
        // - The Englishman lives in the red house.
        // - The Norwegian lives next to the blue house (with Norwegian at house 0, blue must be at house 1).
        for (std::size_t ivory_pos{0U}; ivory_pos < (HOUSES - 1U); ++ivory_pos) {
            std::array<std::uint8_t, HOUSES> color;
            for (std::size_t i{0U}; i < HOUSES; ++i) {
                color[i] = UNASSIGNED;
            }
            color[ivory_pos] = COL_IVORY;
            color[ivory_pos + 1U] = COL_GREEN;

            // Remaining colors to place into remaining slots
            std::array<std::uint8_t, 3U> remaining_colors{{COL_RED, COL_YELLOW, COL_BLUE}};
            std::array<std::size_t, 3U> free_slots{};
            {
                std::size_t k{0U};
                for (std::size_t i{0U}; i < HOUSES; ++i) {
                    if ((color[i] == UNASSIGNED)) {
                        free_slots[k] = i;
                        k = k + 1U;
                    }
                }
            }

            std::sort(remaining_colors.begin(), remaining_colors.end());
            do {
                // Place remaining colors
                for (std::size_t j{0U}; j < remaining_colors.size(); ++j) {
                    color[free_slots[j]] = remaining_colors[j];
                }

                // Check "Englishman lives in the red house"
                std::size_t red_pos{index_of(color, COL_RED)};
                if (!(nat[red_pos] == NAT_ENGLISH)) {
                    continue;
                }

                // Check "Norwegian lives next to the blue house"
                std::size_t blue_pos{index_of(color, COL_BLUE)};
                if (!(is_neighbor(0U, blue_pos))) {
                    continue;
                }

                // Drinks: set known constraints
                std::array<std::uint8_t, HOUSES> drink;
                for (std::size_t i{0U}; i < HOUSES; ++i) {
                    drink[i] = UNASSIGNED;
                }
                // The person in the green house drinks coffee.
                std::size_t green_pos{index_of(color, COL_GREEN)};
                drink[green_pos] = DRINK_COFFEE;
                // The person in the middle house drinks milk. (middle is index 2)
                drink[2U] = DRINK_MILK;
                // The Ukrainian drinks tea.
                std::size_t ukr_pos{index_of(nat, NAT_UKRAINIAN)};
                drink[ukr_pos] = DRINK_TEA;

                // Determine remaining two drink positions and assign Water/Orange Juice in both orders
                std::array<std::size_t, 2U> drink_free_slots{};
                {
                    std::size_t k{0U};
                    for (std::size_t i{0U}; i < HOUSES; ++i) {
                        if ((drink[i] == UNASSIGNED)) {
                            drink_free_slots[k] = i;
                            k = k + 1U;
                        }
                    }
                    if (!(drink_free_slots[1U] < HOUSES)) {
                        // Should not happen; continue defensively
                        continue;
                    }
                }

                // Try two assignments for remaining drinks
                for (std::uint8_t variant{0U}; variant < static_cast<std::uint8_t>(2U); ++variant) {
                    std::array<std::uint8_t, HOUSES> drink_try{drink};
                    if ((variant == 0U)) {
                        drink_try[drink_free_slots[0U]] = DRINK_ORANGE_JUICE;
                        drink_try[drink_free_slots[1U]] = DRINK_WATER;
                    } else {
                        drink_try[drink_free_slots[0U]] = DRINK_WATER;
                        drink_try[drink_free_slots[1U]] = DRINK_ORANGE_JUICE;
                    }

                    // Pets permutations with constraints:
                    // - The Spaniard owns the dog.
                    // - The painter's house is next to the house with the horse. (painter = yellow house)
                    std::array<std::uint8_t, HOUSES> pets{pets_base};
                    std::sort(pets.begin(), pets.end());
                    do {
                        // Spaniard owns dog
                        std::size_t sp_pos{index_of(nat, NAT_SPANIARD)};
                        if (!(pets[sp_pos] == PET_DOG)) {
                            continue;
                        }

                        // Painter's house is next to the house with the horse (painter is the yellow house)
                        std::size_t yellow_pos{index_of(color, COL_YELLOW)};
                        std::size_t horse_pos{index_of(pets, PET_HORSE)};
                        if (!(is_neighbor(yellow_pos, horse_pos))) {
                            continue;
                        }

                        // Now assign hobbies with constraints:
                        // - The snail owner likes to go dancing.
                        // - The person in the yellow house is a painter.
                        // - The person who plays football drinks orange juice.
                        // - The Japanese person plays chess.
                        // - The person who enjoys reading lives in the house next to the person with the fox.
                        std::array<std::uint8_t, HOUSES> hobby;
                        for (std::size_t i{0U}; i < HOUSES; ++i) {
                            hobby[i] = UNASSIGNED;
                        }

                        // Fixed hobby placements
                        std::size_t snails_pos{index_of(pets, PET_SNAILS)};
                        hobby[snails_pos] = HOBBY_DANCING;

                        hobby[yellow_pos] = HOBBY_PAINTING;

                        std::size_t oj_pos{index_of(drink_try, DRINK_ORANGE_JUICE)};
                        hobby[oj_pos] = HOBBY_FOOTBALL;

                        std::size_t jap_pos{index_of(nat, NAT_JAPANESE)};
                        hobby[jap_pos] = HOBBY_CHESS;

                        // Place READING next to FOX
                        std::size_t fox_pos{index_of(pets, PET_FOX)};
                        bool placed_reading{false};
                        // Try left neighbor
                        if ((fox_pos > 0U)) {
                            std::size_t left{fox_pos - 1U};
                            if ((hobby[left] == UNASSIGNED)) {
                                hobby[left] = HOBBY_READING;
                                placed_reading = true;
                            }
                        }
                        // If left not placed, try right neighbor
                        if (!placed_reading) {
                            if (((fox_pos + 1U) < HOUSES)) {
                                std::size_t right{fox_pos + 1U};
                                if ((hobby[right] == UNASSIGNED)) {
                                    hobby[right] = HOBBY_READING;
                                    placed_reading = true;
                                }
                            }
                        }

                        if (!placed_reading) {
                            // Could not place reading satisfying adjacency and uniqueness
                            continue;
                        }

                        // Validate that all hobbies are assigned uniquely
                        bool all_assigned{true};
                        for (std::size_t i{0U}; i < HOUSES; ++i) {
                            if ((hobby[i] == UNASSIGNED)) {
                                all_assigned = false;
                            }
                        }
                        if (!all_assigned) {
                            continue;
                        }

                        // All constraints satisfied; extract answers
                        std::size_t water_pos{index_of(drink_try, DRINK_WATER)};
                        std::size_t zebra_pos{index_of(pets, PET_ZEBRA)};

                        Solution sol{};
                        sol.drinksWater = nat_to_string(nat[water_pos]);
                        sol.ownsZebra = nat_to_string(nat[zebra_pos]);
                        return sol;

                    } while (std::next_permutation(pets.begin(), pets.end()));
                }

            } while (std::next_permutation(remaining_colors.begin(), remaining_colors.end()));
        }

    } while (std::next_permutation(nat.begin(), nat.end()));

    // Fallback (should not happen for a valid puzzle)
    Solution sol{};
    sol.drinksWater = std::string("Unknown");
    sol.ownsZebra = std::string("Unknown");
    return sol;
}

}  // namespace zebra_puzzle

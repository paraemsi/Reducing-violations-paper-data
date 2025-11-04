#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

using std::string;
using std::array;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using house_t = std::uint8_t;
using attr_t = std::uint8_t;

constexpr index_t NUM_HOUSES = 5U;
constexpr index_t NUM_ATTRS = 5U;

// Attribute indices
enum Color : attr_t { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality : attr_t { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet : attr_t { DOG, SNAILS, FOX, HORSE, ZEBRA };
enum Drink : attr_t { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby : attr_t { DANCING, PAINTING, READING, FOOTBALL, CHESS };

// Names for output
constexpr array<const char*, NUM_ATTRS> color_names = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<const char*, NUM_ATTRS> nationality_names = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<const char*, NUM_ATTRS> pet_names = { "dog", "snails", "fox", "horse", "zebra" };
constexpr array<const char*, NUM_ATTRS> drink_names = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<const char*, NUM_ATTRS> hobby_names = { "dancing", "painting", "reading", "football", "chess" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a > b) ? ((a - b) == 1U) : ((b - a) == 1U);
}

Solution solve()
{
    // All permutations of 5 elements
    array<attr_t, NUM_ATTRS> base = { 0U, 1U, 2U, 3U, 4U };

    array<attr_t, NUM_HOUSES> color;
    array<attr_t, NUM_HOUSES> nationality;
    array<attr_t, NUM_HOUSES> pet;
    array<attr_t, NUM_HOUSES> drink;
    array<attr_t, NUM_HOUSES> hobby;

    // Try all possible assignments for each attribute
    // To reduce search space, apply constraints as early as possible

    // 10. The Norwegian lives in the first house.
    // 9. The person in the middle house drinks milk.
    // 15. The Norwegian lives next to the blue house.
    // 6. The green house is immediately to the right of the ivory house.

    // Fix Norwegian at house 0, milk at house 2
    array<attr_t, NUM_ATTRS> nat_perm = base;
    do {
        if (nat_perm[0U] != NORWEGIAN) {
            continue;
        }
        nationality = nat_perm;

        array<attr_t, NUM_ATTRS> col_perm = base;
        do {
            // 6. The green house is immediately to the right of the ivory house.
            index_t ivory = 0U, green = 0U;
            for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                if (col_perm[i] == IVORY) {
                    ivory = i;
                }
                if (col_perm[i] == GREEN) {
                    green = i;
                }
            }
            if ((green != (ivory + 1U))) {
                continue;
            }
            // 15. The Norwegian lives next to the blue house.
            index_t norw = 0U, blue = 0U;
            for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                if (nationality[i] == NORWEGIAN) {
                    norw = i;
                }
                if (col_perm[i] == BLUE) {
                    blue = i;
                }
            }
            if (!is_neighbor(norw, blue)) {
                continue;
            }
            color = col_perm;

            array<attr_t, NUM_ATTRS> dri_perm = base;
            do {
                // 9. The person in the middle house drinks milk.
                if (dri_perm[2U] != MILK) {
                    continue;
                }
                // 4. The person in the green house drinks coffee.
                index_t green_idx = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (color[i] == GREEN) {
                        green_idx = i;
                        break;
                    }
                }
                if (dri_perm[green_idx] != COFFEE) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                index_t ukr_idx = 0U;
                for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if (nationality[i] == UKRAINIAN) {
                        ukr_idx = i;
                        break;
                    }
                }
                if (dri_perm[ukr_idx] != TEA) {
                    continue;
                }
                drink = dri_perm;

                array<attr_t, NUM_ATTRS> hob_perm = base;
                do {
                    // 8. The person in the yellow house is a painter.
                    index_t yellow_idx = 0U;
                    for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if (color[i] == YELLOW) {
                            yellow_idx = i;
                            break;
                        }
                    }
                    if (hob_perm[yellow_idx] != PAINTING) {
                        continue;
                    }
                    // 13. The person who plays football drinks orange juice.
                    index_t oj_idx = 0U;
                    for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if (drink[i] == ORANGE_JUICE) {
                            oj_idx = i;
                            break;
                        }
                    }
                    if (hob_perm[oj_idx] != FOOTBALL) {
                        continue;
                    }
                    // 14. The Japanese person plays chess.
                    index_t jap_idx = 0U;
                    for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if (nationality[i] == JAPANESE) {
                            jap_idx = i;
                            break;
                        }
                    }
                    if (hob_perm[jap_idx] != CHESS) {
                        continue;
                    }
                    hobby = hob_perm;

                    array<attr_t, NUM_ATTRS> pet_perm = base;
                    do {
                        // 3. The Spaniard owns the dog.
                        index_t spa_idx = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (nationality[i] == SPANIARD) {
                                spa_idx = i;
                                break;
                            }
                        }
                        if (pet_perm[spa_idx] != DOG) {
                            continue;
                        }
                        // 7. The snail owner likes to go dancing.
                        index_t snails_idx = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (pet_perm[i] == SNAILS) {
                                snails_idx = i;
                                break;
                            }
                        }
                        if (hobby[snails_idx] != DANCING) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        index_t fox_idx = 0U, reading_idx = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (pet_perm[i] == FOX) {
                                fox_idx = i;
                            }
                            if (hobby[i] == READING) {
                                reading_idx = i;
                            }
                        }
                        if (!is_neighbor(fox_idx, reading_idx)) {
                            continue;
                        }
                        // 12. The painter's house is next to the house with the horse.
                        index_t horse_idx = 0U, painting_idx = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (pet_perm[i] == HORSE) {
                                horse_idx = i;
                            }
                            if (hobby[i] == PAINTING) {
                                painting_idx = i;
                            }
                        }
                        if (!is_neighbor(horse_idx, painting_idx)) {
                            continue;
                        }
                        pet = pet_perm;

                        // 2. The Englishman lives in the red house.
                        index_t eng_idx = 0U, red_idx = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (nationality[i] == ENGLISHMAN) {
                                eng_idx = i;
                            }
                            if (color[i] == RED) {
                                red_idx = i;
                            }
                        }
                        if (eng_idx != red_idx) {
                            continue;
                        }

                        // All constraints satisfied, find water drinker and zebra owner
                        index_t water_idx = 0U, zebra_idx = 0U;
                        for (index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if (drink[i] == WATER) {
                                water_idx = i;
                            }
                            if (pet[i] == ZEBRA) {
                                zebra_idx = i;
                            }
                        }
                        Solution sol;
                        sol.drinksWater = nationality_names[nationality[water_idx]];
                        sol.ownsZebra = nationality_names[nationality[zebra_idx]];
                        return sol;
                    } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));
                } while (std::next_permutation(hob_perm.begin(), hob_perm.end()));
            } while (std::next_permutation(dri_perm.begin(), dri_perm.end()));
        } while (std::next_permutation(col_perm.begin(), col_perm.end()));
    } while (std::next_permutation(nat_perm.begin(), nat_perm.end()));

    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>

namespace zebra_puzzle {

// Fixed-width type alias for house index
using house_index_t = std::uint8_t;

// All possible values for each attribute
static const std::array<std::string, 5U> colors = { "red", "green", "ivory", "yellow", "blue" };
static const std::array<std::string, 5U> nationalities = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
static const std::array<std::string, 5U> pets = { "dog", "snails", "fox", "horse", "zebra" };
static const std::array<std::string, 5U> drinks = { "coffee", "tea", "milk", "orange juice", "water" };
static const std::array<std::string, 5U> hobbies = { "dancing", "painter", "reading", "football", "chess" };

// Helper function to check if two houses are neighbors
static bool is_neighbor(house_index_t a, house_index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

Solution solve()
{
    // All permutations of 5 elements
    std::array<house_index_t, 5U> idx = { 0U, 1U, 2U, 3U, 4U };

    // We'll permute each attribute and check constraints
    // (removed unused variables to fix -Wunused-variable)

    // For performance, fix some attributes based on clues:
    // 9. The person in the middle house drinks milk.
    // 10. The Norwegian lives in the first house.
    // So, drink[2] == milk, nationality[0] == Norwegian

    // Find the index of "milk" and "Norwegian"
    house_index_t milk_idx = 0U;
    house_index_t norwegian_idx = 0U;
    for (house_index_t i = 0U; i < 5U; ++i) {
        if (drinks[i] == "milk") {
            milk_idx = i;
        }
        if (nationalities[i] == "Norwegian") {
            norwegian_idx = i;
        }
    }

    // Generate all permutations for color
    std::array<house_index_t, 5U> color_perm = idx;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        house_index_t green = 0U, ivory = 0U;
        for (house_index_t i = 0U; i < 5U; ++i) {
            if (colors[color_perm[i]] == "green") {
                green = i;
            }
            if (colors[color_perm[i]] == "ivory") {
                ivory = i;
            }
        }
        if (green != (ivory + 1U)) {
            continue;
        }

        // 15. The Norwegian lives next to the blue house.
        house_index_t blue = 0U;
        for (house_index_t i = 0U; i < 5U; ++i) {
            if (colors[color_perm[i]] == "blue") {
                blue = i;
            }
        }

        // Generate all permutations for nationality
        std::array<house_index_t, 5U> nat_perm = idx;
        do {
            if (nat_perm[0] != norwegian_idx) {
                continue;
            }
            // 2. The Englishman lives in the red house.
            house_index_t englishman = 0U, red = 0U;
            for (house_index_t i = 0U; i < 5U; ++i) {
                if (nationalities[nat_perm[i]] == "Englishman") {
                    englishman = i;
                }
                if (colors[color_perm[i]] == "red") {
                    red = i;
                }
            }
            if (englishman != red) {
                continue;
            }
            // 15. Norwegian lives next to blue house
            if (!is_neighbor(0U, blue)) {
                continue;
            }

            // Generate all permutations for drink
            std::array<house_index_t, 5U> drink_perm = idx;
            do {
                if (drink_perm[2] != milk_idx) {
                    continue;
                }
                // 4. The person in the green house drinks coffee.
                house_index_t green_house = 0U, coffee = 0U;
                for (house_index_t i = 0U; i < 5U; ++i) {
                    if (colors[color_perm[i]] == "green") {
                        green_house = i;
                    }
                    if (drinks[drink_perm[i]] == "coffee") {
                        coffee = i;
                    }
                }
                if (green_house != coffee) {
                    continue;
                }
                // 5. The Ukrainian drinks tea.
                house_index_t ukrainian = 0U, tea = 0U;
                for (house_index_t i = 0U; i < 5U; ++i) {
                    if (nationalities[nat_perm[i]] == "Ukrainian") {
                        ukrainian = i;
                    }
                    if (drinks[drink_perm[i]] == "tea") {
                        tea = i;
                    }
                }
                if (ukrainian != tea) {
                    continue;
                }
                // 13. The person who plays football drinks orange juice.
                // We'll check this after hobby is set.

                // Generate all permutations for pet
                std::array<house_index_t, 5U> pet_perm = idx;
                do {
                    // 3. The Spaniard owns the dog.
                    house_index_t spaniard = 0U, dog = 0U;
                    for (house_index_t i = 0U; i < 5U; ++i) {
                        if (nationalities[nat_perm[i]] == "Spaniard") {
                            spaniard = i;
                        }
                        if (pets[pet_perm[i]] == "dog") {
                            dog = i;
                        }
                    }
                    if (spaniard != dog) {
                        continue;
                    }
                    // 11. The person who enjoys reading lives in the house next to the person with the fox.
                    // 12. The painter's house is next to the house with the horse.
                    // We'll check these after hobby is set.

                    // Generate all permutations for hobby
                    std::array<house_index_t, 5U> hobby_perm = idx;
                    do {
                        // 8. The person in the yellow house is a painter.
                        house_index_t yellow = 0U, painter = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (colors[color_perm[i]] == "yellow") {
                                yellow = i;
                            }
                            if (hobbies[hobby_perm[i]] == "painter") {
                                painter = i;
                            }
                        }
                        if (yellow != painter) {
                            continue;
                        }
                        // 7. The snail owner likes to go dancing.
                        house_index_t snails = 0U, dancing = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (pets[pet_perm[i]] == "snails") {
                                snails = i;
                            }
                            if (hobbies[hobby_perm[i]] == "dancing") {
                                dancing = i;
                            }
                        }
                        if (snails != dancing) {
                            continue;
                        }
                        // 14. The Japanese person plays chess.
                        house_index_t japanese = 0U, chess = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (nationalities[nat_perm[i]] == "Japanese") {
                                japanese = i;
                            }
                            if (hobbies[hobby_perm[i]] == "chess") {
                                chess = i;
                            }
                        }
                        if (japanese != chess) {
                            continue;
                        }
                        // 13. The person who plays football drinks orange juice.
                        house_index_t football = 0U, orange_juice = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (hobbies[hobby_perm[i]] == "football") {
                                football = i;
                            }
                            if (drinks[drink_perm[i]] == "orange juice") {
                                orange_juice = i;
                            }
                        }
                        if (football != orange_juice) {
                            continue;
                        }
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        house_index_t reading = 0U, fox = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (hobbies[hobby_perm[i]] == "reading") {
                                reading = i;
                            }
                            if (pets[pet_perm[i]] == "fox") {
                                fox = i;
                            }
                        }
                        if (!is_neighbor(reading, fox)) {
                            continue;
                        }
                        // 12. The painter's house is next to the house with the horse.
                        house_index_t horse = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (pets[pet_perm[i]] == "horse") {
                                horse = i;
                            }
                        }
                        if (!is_neighbor(painter, horse)) {
                            continue;
                        }

                        // All constraints satisfied, build solution
                        house_index_t water_house = 0U, zebra_house = 0U;
                        for (house_index_t i = 0U; i < 5U; ++i) {
                            if (drinks[drink_perm[i]] == "water") {
                                water_house = i;
                            }
                            if (pets[pet_perm[i]] == "zebra") {
                                zebra_house = i;
                            }
                        }
                        Solution sol;
                        sol.drinksWater = nationalities[nat_perm[water_house]];
                        sol.ownsZebra = nationalities[nat_perm[zebra_house]];
                        return sol;
                    } while (std::next_permutation(hobby_perm.begin(), hobby_perm.end()));
                } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));
            } while (std::next_permutation(drink_perm.begin(), drink_perm.end()));
        } while (std::next_permutation(nat_perm.begin(), nat_perm.end()));
    } while (std::next_permutation(color_perm.begin(), color_perm.end()));

    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

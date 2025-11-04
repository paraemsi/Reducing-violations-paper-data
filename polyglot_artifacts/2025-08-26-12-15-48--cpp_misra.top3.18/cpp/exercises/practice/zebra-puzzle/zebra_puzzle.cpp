#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>

namespace zebra_puzzle {

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using HouseArray = std::array<index_t, 5U>;

// All possible values for each attribute
static const std::array<std::string, 5U> COLORS = { "red", "green", "ivory", "yellow", "blue" };
static const std::array<std::string, 5U> NATIONALITIES = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
static const std::array<std::string, 5U> PETS = { "dog", "snails", "fox", "horse", "zebra" };
static const std::array<std::string, 5U> DRINKS = { "coffee", "tea", "milk", "orange juice", "water" };
static const std::array<std::string, 5U> HOBBIES = { "dancing", "reading", "painting", "football", "chess" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a > b) ? ((a - b) == static_cast<index_t>(1)) : ((b - a) == static_cast<index_t>(1));
}

Solution solve()
{
    // All permutations of 0..4 for each attribute
    std::array<index_t, 5U> base = { 0U, 1U, 2U, 3U, 4U };

    // Generate all color permutations with green right of ivory
    std::vector<HouseArray> color_perms;
    std::array<index_t, 5U> color = base;
    do {
        index_t ivory = 0U, green = 0U, blue = 0U;
        for(index_t i = 0U; i < 5U; ++i) {
            if(color[i] == 2U) { ivory = i; }
            if(color[i] == 1U) { green = i; }
            if(color[i] == 4U) { blue = i; }
        }
        if((green == (ivory + 1U))) {
            color_perms.push_back(color);
        }
    } while(std::next_permutation(color.begin(), color.end()));

    // Generate all nationality permutations with Norwegian in first house
    std::vector<HouseArray> nat_perms;
    std::array<index_t, 5U> nationality = base;
    do {
        if(nationality[0U] == 3U) {
            nat_perms.push_back(nationality);
        }
    } while(std::next_permutation(nationality.begin(), nationality.end()));

    // Generate all drink permutations with milk in the middle house
    std::vector<HouseArray> drink_perms;
    std::array<index_t, 5U> drink = base;
    do {
        if(drink[2U] == 2U) {
            drink_perms.push_back(drink);
        }
    } while(std::next_permutation(drink.begin(), drink.end()));

    // Generate all permutations for pet and hobby
    std::vector<HouseArray> pet_perms;
    std::array<index_t, 5U> pet = base;
    do {
        pet_perms.push_back(pet);
    } while(std::next_permutation(pet.begin(), pet.end()));

    std::vector<HouseArray> hobby_perms;
    std::array<index_t, 5U> hobby = base;
    do {
        hobby_perms.push_back(hobby);
    } while(std::next_permutation(hobby.begin(), hobby.end()));

    // Try all combinations
    for(const auto& color : color_perms) {
        for(const auto& nationality : nat_perms) {
            // 2. Englishman lives in red house
            index_t englishman = 0U;
            for(index_t i = 0U; i < 5U; ++i) {
                if(nationality[i] == 0U) { englishman = i; }
            }
            if(color[englishman] != 0U) { continue; }

            // 15. Norwegian lives next to blue house
            index_t norwegian = 0U;
            for(index_t i = 0U; i < 5U; ++i) {
                if(nationality[i] == 3U) { norwegian = i; }
            }
            index_t blue = 0U;
            for(index_t i = 0U; i < 5U; ++i) {
                if(color[i] == 4U) { blue = i; }
            }
            if(!is_neighbor(norwegian, blue)) { continue; }

            for(const auto& drink : drink_perms) {
                // 4. Green house drinks coffee
                index_t green = 0U;
                for(index_t i = 0U; i < 5U; ++i) {
                    if(color[i] == 1U) { green = i; }
                }
                if(drink[green] != 0U) { continue; }

                // 5. Ukrainian drinks tea
                index_t ukrainian = 0U;
                for(index_t i = 0U; i < 5U; ++i) {
                    if(nationality[i] == 2U) { ukrainian = i; }
                }
                if(drink[ukrainian] != 1U) { continue; }

                for(const auto& pet : pet_perms) {
                    // 3. Spaniard owns the dog
                    index_t spaniard = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(nationality[i] == 1U) { spaniard = i; }
                    }
                    if(pet[spaniard] != 0U) { continue; }

                    for(const auto& hobby : hobby_perms) {
                        // 7. Snail owner likes dancing
                        index_t snail = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(pet[i] == 1U) { snail = i; }
                        }
                        if(hobby[snail] != 0U) { continue; }

                        // 8. Yellow house is painter
                        index_t yellow = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(color[i] == 3U) { yellow = i; }
                        }
                        if(hobby[yellow] != 2U) { continue; }

                        // 9. Middle house drinks milk (already enforced)

                        // 11. Reader lives next to fox owner
                        index_t fox = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(pet[i] == 2U) { fox = i; }
                        }
                        index_t reader = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(hobby[i] == 1U) { reader = i; }
                        }
                        if(!is_neighbor(reader, fox)) { continue; }

                        // 12. Painter's house is next to horse
                        index_t painter = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(hobby[i] == 2U) { painter = i; }
                        }
                        index_t horse = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(pet[i] == 3U) { horse = i; }
                        }
                        if(!is_neighbor(painter, horse)) { continue; }

                        // 13. Football player drinks orange juice
                        index_t football = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(hobby[i] == 3U) { football = i; }
                        }
                        if(drink[football] != 3U) { continue; }

                        // 14. Japanese plays chess
                        index_t japanese = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(nationality[i] == 4U) { japanese = i; }
                        }
                        if(hobby[japanese] != 4U) { continue; }

                        // All constraints satisfied, find water drinker and zebra owner
                        index_t water = 0U, zebra = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(drink[i] == 4U) { water = i; }
                            if(pet[i] == 4U) { zebra = i; }
                        }
                        Solution sol;
                        sol.drinksWater = NATIONALITIES[static_cast<std::size_t>(nationality[water])];
                        sol.ownsZebra = NATIONALITIES[static_cast<std::size_t>(nationality[zebra])];
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found, return empty
    Solution sol;
    return sol;
}

}  // namespace zebra_puzzle

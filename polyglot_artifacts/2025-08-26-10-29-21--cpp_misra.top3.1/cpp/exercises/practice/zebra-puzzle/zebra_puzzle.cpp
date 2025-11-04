#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <vector>
#include <algorithm>

namespace zebra_puzzle {

namespace {

using std::array;
using std::string;
using std::vector;

// Aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using perm_t = array<index_t, 5U>;


// Helper to check if two houses are neighbors
bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

} // namespace

Solution solve()
{
    // All possible values for each attribute
    const array<string, 5U> colors = { "red", "green", "ivory", "yellow", "blue" };
    const array<string, 5U> nationalities = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
    const array<string, 5U> pets = { "dog", "snails", "fox", "horse", "zebra" };
    const array<string, 5U> drinks = { "coffee", "tea", "milk", "orange juice", "water" };
    const array<string, 5U> hobbies = { "dancing", "painter", "reading", "football", "chess" };

    // Initial permutation: 0,1,2,3,4
    perm_t color, nat, pet, drink, hobby;
    for(index_t i = 0U; i < 5U; ++i) {
        color[i] = i;
        nat[i] = i;
        pet[i] = i;
        drink[i] = i;
        hobby[i] = i;
    }

    // Generate all permutations for each attribute, but use constraints to prune search
    // The order of the houses is 0..4 (left to right)
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if((color[1U] != 1U) && (color[2U] != 1U) && (color[3U] != 1U) && (color[4U] != 1U)) {
            continue;
        }
        index_t green = 0U, ivory = 0U;
        for(index_t i = 0U; i < 5U; ++i) {
            if(color[i] == 1U) { green = i; }
            if(color[i] == 2U) { ivory = i; }
        }
        if((green != (ivory + 1U))) {
            continue;
        }

        do {
            // 2. The Englishman lives in the red house.
            index_t englishman = 0U, red = 0U;
            for(index_t i = 0U; i < 5U; ++i) {
                if(nat[i] == 0U) { englishman = i; }
                if(color[i] == 0U) { red = i; }
            }
            if(englishman != red) { continue; }

            // 10. The Norwegian lives in the first house.
            bool skip_nat = false;
            for(index_t i = 0U; i < 5U; ++i) {
                if((nat[i] == 3U) && (i != 0U)) { skip_nat = true; break; }
            }
            if(skip_nat) { continue; }

            // 15. The Norwegian lives next to the blue house.
            index_t norwegian = 0U, blue = 0U;
            for(index_t i = 0U; i < 5U; ++i) {
                if(nat[i] == 3U) { norwegian = i; }
                if(color[i] == 4U) { blue = i; }
            }
            if(!is_neighbor(norwegian, blue)) { continue; }

            do {
                // 3. The Spaniard owns the dog.
                index_t spaniard = 0U, dog = 0U;
                for(index_t i = 0U; i < 5U; ++i) {
                    if(nat[i] == 1U) { spaniard = i; }
                    if(pet[i] == 0U) { dog = i; }
                }
                if(spaniard != dog) { continue; }

                // 11. The person who enjoys reading lives in the house next to the person with the fox.
                index_t reading = 0U, fox = 0U;
                for(index_t i = 0U; i < 5U; ++i) {
                    if(hobby[i] == 2U) { reading = i; }
                    if(pet[i] == 2U) { fox = i; }
                }
                if(!is_neighbor(reading, fox)) { continue; }

                // 12. The painter's house is next to the house with the horse.
                index_t painter = 0U, horse = 0U;
                for(index_t i = 0U; i < 5U; ++i) {
                    if(hobby[i] == 1U) { painter = i; }
                    if(pet[i] == 3U) { horse = i; }
                }
                if(!is_neighbor(painter, horse)) { continue; }

                do {
                    // 4. The person in the green house drinks coffee.
                    index_t green = 0U, coffee = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(color[i] == 1U) { green = i; }
                        if(drink[i] == 0U) { coffee = i; }
                    }
                    if(green != coffee) { continue; }

                    // 5. The Ukrainian drinks tea.
                    index_t ukrainian = 0U, tea = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(nat[i] == 2U) { ukrainian = i; }
                        if(drink[i] == 1U) { tea = i; }
                    }
                    if(ukrainian != tea) { continue; }

                    // 9. The person in the middle house drinks milk.
                    if(drink[2U] != 2U) { continue; }

                    // 13. The person who plays football drinks orange juice.
                    index_t football = 0U, orange_juice = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(hobby[i] == 3U) { football = i; }
                        if(drink[i] == 3U) { orange_juice = i; }
                    }
                    if(football != orange_juice) { continue; }

                    // 8. The person in the yellow house is a painter.
                    index_t yellow = 0U, painter = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(color[i] == 3U) { yellow = i; }
                        if(hobby[i] == 1U) { painter = i; }
                    }
                    if(yellow != painter) { continue; }

                    // 7. The snail owner likes to go dancing.
                    index_t snails = 0U, dancing = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(pet[i] == 1U) { snails = i; }
                        if(hobby[i] == 0U) { dancing = i; }
                    }
                    if(snails != dancing) { continue; }

                    // 14. The Japanese person plays chess.
                    index_t japanese = 0U, chess = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(nat[i] == 4U) { japanese = i; }
                        if(hobby[i] == 4U) { chess = i; }
                    }
                    if(japanese != chess) { continue; }

                    // 1. There are five houses. (implicit)
                    // 6. The green house is immediately to the right of the ivory house. (already checked)
                    // 15. The Norwegian lives next to the blue house. (already checked)

                    // 11. The person who enjoys reading lives in the house next to the person with the fox. (already checked)
                    // 12. The painter's house is next to the house with the horse. (already checked)

                    // All constraints satisfied, extract solution
                    index_t water_drinker = 0U, zebra_owner = 0U;
                    for(index_t i = 0U; i < 5U; ++i) {
                        if(drink[i] == 4U) { water_drinker = i; }
                        if(pet[i] == 4U) { zebra_owner = i; }
                    }
                    Solution sol;
                    sol.drinksWater = nationalities[static_cast<std::size_t>(nat[water_drinker])];
                    sol.ownsZebra = nationalities[static_cast<std::size_t>(nat[zebra_owner])];
                    return sol;

                } while(std::next_permutation(drink.begin(), drink.end()));
            } while(std::next_permutation(pet.begin(), pet.end()));
        next_nat: ;
        } while(std::next_permutation(nat.begin(), nat.end()));
    } while(std::next_permutation(color.begin(), color.end()));

    // If no solution found (should not happen)
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

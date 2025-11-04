#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

namespace {

using std::string;
using std::array;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using house_t = std::uint8_t;
constexpr index_t N = 5U;

// All possible values for each attribute
constexpr array<const char*, N> colors = { "red", "green", "ivory", "yellow", "blue" };
constexpr array<const char*, N> nationalities = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
constexpr array<const char*, N> pets = { "dog", "snails", "fox", "horse", "zebra" };
constexpr array<const char*, N> drinks = { "coffee", "tea", "milk", "orange juice", "water" };
constexpr array<const char*, N> hobbies = { "dancing", "painter", "reading", "football", "chess" };

// Helper to check if two houses are neighbors
inline bool is_neighbor(index_t a, index_t b)
{
    return (a > b) ? ((a - b) == 1U) : ((b - a) == 1U);
}

} // anonymous namespace

Solution solve()
{
    // All permutations of 0..4 for each attribute
    array<index_t, N> color, nationality, pet, drink, hobby;

    // For performance, fix some attributes by clues:
    // 9. The person in the middle house drinks milk. (house 2)
    // 10. The Norwegian lives in the first house. (house 0)
    // 15. The Norwegian lives next to the blue house.

    // Try all permutations for color
    do {
        // 6. The green house is immediately to the right of the ivory house.
        index_t green = 0U, ivory = 0U;
        for(index_t i = 0U; i < N; ++i) {
            if(color[i] == 1U) { green = i; } // green
            if(color[i] == 2U) { ivory = i; } // ivory
        }
        if((green != (ivory + 1U))) { continue; }

        // 15. The Norwegian lives next to the blue house.
        index_t blue = 0U;
        for(index_t i = 0U; i < N; ++i) {
            if(color[i] == 4U) { blue = i; } // blue
        }

        // Try all permutations for nationality
        do {
            // 10. The Norwegian lives in the first house.
            index_t norwegian = 0U;
            for(index_t i = 0U; i < N; ++i) {
                if(nationality[i] == 3U) { norwegian = i; } // Norwegian
            }
            if(norwegian != 0U) { continue; }
            if(!is_neighbor(norwegian, blue)) { continue; }

            // 2. The Englishman lives in the red house.
            index_t englishman = 0U, red = 0U;
            for(index_t i = 0U; i < N; ++i) {
                if(nationality[i] == 0U) { englishman = i; }
                if(color[i] == 0U) { red = i; }
            }
            if(englishman != red) { continue; }

            // Try all permutations for pet
            do {
                // 3. The Spaniard owns the dog.
                index_t spaniard = 0U, dog = 0U;
                for(index_t i = 0U; i < N; ++i) {
                    if(nationality[i] == 1U) { spaniard = i; }
                    if(pet[i] == 0U) { dog = i; }
                }
                if(spaniard != dog) { continue; }

                // Try all permutations for drink
                do {
                    // 4. The person in the green house drinks coffee.
                    index_t coffee = 0U;
                    for(index_t i = 0U; i < N; ++i) {
                        if(drink[i] == 0U) { coffee = i; }
                    }
                    if(color[coffee] != 1U) { continue; }

                    // 5. The Ukrainian drinks tea.
                    index_t ukrainian = 0U, tea = 0U;
                    for(index_t i = 0U; i < N; ++i) {
                        if(nationality[i] == 2U) { ukrainian = i; }
                        if(drink[i] == 1U) { tea = i; }
                    }
                    if(ukrainian != tea) { continue; }

                    // 9. The person in the middle house drinks milk.
                    if(drink[2U] != 2U) { continue; }

                    // 13. The person who plays football drinks orange juice.
                    index_t football = 0U, orange_juice = 0U;
                    for(index_t i = 0U; i < N; ++i) {
                        if(hobby[i] == 3U) { football = i; }
                        if(drink[i] == 3U) { orange_juice = i; }
                    }
                    if(football != orange_juice) { continue; }

                    // Try all permutations for hobby
                    do {
                        // 7. The snail owner likes to go dancing.
                        index_t snails = 0U, dancing = 0U;
                        for(index_t i = 0U; i < N; ++i) {
                            if(pet[i] == 1U) { snails = i; }
                            if(hobby[i] == 0U) { dancing = i; }
                        }
                        if(snails != dancing) { continue; }

                        // 8. The person in the yellow house is a painter.
                        index_t yellow = 0U, painter = 0U;
                        for(index_t i = 0U; i < N; ++i) {
                            if(color[i] == 3U) { yellow = i; }
                            if(hobby[i] == 1U) { painter = i; }
                        }
                        if(yellow != painter) { continue; }

                        // 12. The painter's house is next to the house with the horse.
                        index_t horse = 0U;
                        for(index_t i = 0U; i < N; ++i) {
                            if(pet[i] == 3U) { horse = i; }
                        }
                        if(!is_neighbor(painter, horse)) { continue; }

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        index_t reading = 0U, fox = 0U;
                        for(index_t i = 0U; i < N; ++i) {
                            if(hobby[i] == 2U) { reading = i; }
                            if(pet[i] == 2U) { fox = i; }
                        }
                        if(!is_neighbor(reading, fox)) { continue; }

                        // 14. The Japanese person plays chess.
                        index_t japanese = 0U, chess = 0U;
                        for(index_t i = 0U; i < N; ++i) {
                            if(nationality[i] == 4U) { japanese = i; }
                            if(hobby[i] == 4U) { chess = i; }
                        }
                        if(japanese != chess) { continue; }

                        // All constraints satisfied, find water drinker and zebra owner
                        index_t water = 0U, zebra = 0U;
                        for(index_t i = 0U; i < N; ++i) {
                            if(drink[i] == 4U) { water = i; }
                            if(pet[i] == 4U) { zebra = i; }
                        }
                        Solution sol;
                        sol.drinksWater = nationalities[static_cast<std::size_t>(nationality[water])];
                        sol.ownsZebra = nationalities[static_cast<std::size_t>(nationality[zebra])];
                        return sol;
                    } while(std::next_permutation(hobby.begin(), hobby.end()));
                } while(std::next_permutation(drink.begin(), drink.end()));
            } while(std::next_permutation(pet.begin(), pet.end()));
        } while(std::next_permutation(nationality.begin(), nationality.end()));
    } while(std::next_permutation(color.begin(), color.end()));

    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdint>

namespace zebra_puzzle {

namespace {

using std::string;
using std::array;
using std::vector;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using house_t = std::uint8_t;
constexpr index_t NUM_HOUSES = static_cast<index_t>(5U);

enum class Color : index_t { Red, Green, Ivory, Yellow, Blue, Count };
enum class Nationality : index_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese, Count };
enum class Pet : index_t { Dog, Snails, Fox, Horse, Zebra, Count };
enum class Drink : index_t { Coffee, Tea, Milk, OrangeJuice, Water, Count };
enum class Hobby : index_t { Reading, Dancing, Painting, Football, Chess, Count };

const array<string, static_cast<index_t>(Color::Count)> color_names = {
    "red", "green", "ivory", "yellow", "blue"
};
const array<string, static_cast<index_t>(Nationality::Count)> nationality_names = {
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
};
const array<string, static_cast<index_t>(Pet::Count)> pet_names = {
    "dog", "snails", "fox", "horse", "zebra"
};
const array<string, static_cast<index_t>(Drink::Count)> drink_names = {
    "coffee", "tea", "milk", "orange juice", "water"
};
const array<string, static_cast<index_t>(Hobby::Count)> hobby_names = {
    "reading", "dancing", "painting", "football", "chess"
};

// Helper to check if two houses are neighbors
inline bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

} // namespace

Solution solve()
{
    // All possible permutations for each attribute
    array<index_t, NUM_HOUSES> idx = {0U, 1U, 2U, 3U, 4U};

    // 1. There are five houses. (already modeled)

    // Try all permutations for each attribute, but apply constraints as early as possible.
    // We start with colors and nationalities, as many clues relate to them.

    // For performance, we use std::next_permutation and prune impossible cases early.
    // The order of loops is chosen to maximize early pruning.

    // colors: 0=Red, 1=Green, 2=Ivory, 3=Yellow, 4=Blue
    array<index_t, NUM_HOUSES> color_perm = idx;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        index_t green = 0U, ivory = 0U;
        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
            if(color_perm[i] == static_cast<index_t>(Color::Green)) { green = i; }
            if(color_perm[i] == static_cast<index_t>(Color::Ivory)) { ivory = i; }
        }
        if(green != (ivory + 1U)) { continue; }

        // 15. The Norwegian lives next to the blue house.
        index_t blue = 0U;
        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
            if(color_perm[i] == static_cast<index_t>(Color::Blue)) { blue = i; }
        }

        // nationalities: 0=Englishman, 1=Spaniard, 2=Ukrainian, 3=Norwegian, 4=Japanese
        array<index_t, NUM_HOUSES> nat_perm = idx;
        do {
            // 10. The Norwegian lives in the first house.
            if(nat_perm[0] != static_cast<index_t>(Nationality::Norwegian)) { continue; }
            // 2. The Englishman lives in the red house.
            index_t englishman = 0U;
            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                if(nat_perm[i] == static_cast<index_t>(Nationality::Englishman)) { englishman = i; }
            }
            if(color_perm[englishman] != static_cast<index_t>(Color::Red)) { continue; }
            // 15. The Norwegian lives next to the blue house.
            index_t norwegian = 0U;
            for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                if(nat_perm[i] == static_cast<index_t>(Nationality::Norwegian)) { norwegian = i; }
            }
            if(!is_neighbor(norwegian, blue)) { continue; }

            // drinks: 0=Coffee, 1=Tea, 2=Milk, 3=OrangeJuice, 4=Water
            array<index_t, NUM_HOUSES> drink_perm = idx;
            do {
                // 9. The person in the middle house drinks milk.
                if(drink_perm[2] != static_cast<index_t>(Drink::Milk)) { continue; }
                // 4. The person in the green house drinks coffee.
                if(drink_perm[green] != static_cast<index_t>(Drink::Coffee)) { continue; }
                // 5. The Ukrainian drinks tea.
                index_t ukrainian = 0U;
                for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                    if(nat_perm[i] == static_cast<index_t>(Nationality::Ukrainian)) { ukrainian = i; }
                }
                if(drink_perm[ukrainian] != static_cast<index_t>(Drink::Tea)) { continue; }

                // pets: 0=Dog, 1=Snails, 2=Fox, 3=Horse, 4=Zebra
                array<index_t, NUM_HOUSES> pet_perm = idx;
                do {
                    // 3. The Spaniard owns the dog.
                    index_t spaniard = 0U;
                    for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                        if(nat_perm[i] == static_cast<index_t>(Nationality::Spaniard)) { spaniard = i; }
                    }
                    if(pet_perm[spaniard] != static_cast<index_t>(Pet::Dog)) { continue; }

                    // hobbies: 0=Reading, 1=Dancing, 2=Painting, 3=Football, 4=Chess
                    array<index_t, NUM_HOUSES> hobby_perm = idx;
                    do {
                        // 7. The snail owner likes to go dancing.
                        index_t snail_owner = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(pet_perm[i] == static_cast<index_t>(Pet::Snails)) { snail_owner = i; }
                        }
                        if(hobby_perm[snail_owner] != static_cast<index_t>(Hobby::Dancing)) { continue; }
                        // 8. The person in the yellow house is a painter.
                        index_t yellow = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(color_perm[i] == static_cast<index_t>(Color::Yellow)) { yellow = i; }
                        }
                        if(hobby_perm[yellow] != static_cast<index_t>(Hobby::Painting)) { continue; }
                        // 12. The painter's house is next to the house with the horse.
                        index_t painter = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(hobby_perm[i] == static_cast<index_t>(Hobby::Painting)) { painter = i; }
                        }
                        index_t horse = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(pet_perm[i] == static_cast<index_t>(Pet::Horse)) { horse = i; }
                        }
                        if(!is_neighbor(painter, horse)) { continue; }
                        // 13. The person who plays football drinks orange juice.
                        index_t football = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(hobby_perm[i] == static_cast<index_t>(Hobby::Football)) { football = i; }
                        }
                        if(drink_perm[football] != static_cast<index_t>(Drink::OrangeJuice)) { continue; }
                        // 14. The Japanese person plays chess.
                        index_t japanese = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(nat_perm[i] == static_cast<index_t>(Nationality::Japanese)) { japanese = i; }
                        }
                        if(hobby_perm[japanese] != static_cast<index_t>(Hobby::Chess)) { continue; }
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        index_t reading = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(hobby_perm[i] == static_cast<index_t>(Hobby::Reading)) { reading = i; }
                        }
                        index_t fox = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(pet_perm[i] == static_cast<index_t>(Pet::Fox)) { fox = i; }
                        }
                        if(!is_neighbor(reading, fox)) { continue; }

                        // All constraints satisfied, extract solution
                        index_t water_drinker = 0U;
                        index_t zebra_owner = 0U;
                        for(index_t i = 0U; i < NUM_HOUSES; ++i) {
                            if(drink_perm[i] == static_cast<index_t>(Drink::Water)) { water_drinker = i; }
                            if(pet_perm[i] == static_cast<index_t>(Pet::Zebra)) { zebra_owner = i; }
                        }
                        Solution sol;
                        sol.drinksWater = nationality_names[nat_perm[water_drinker]];
                        sol.ownsZebra = nationality_names[nat_perm[zebra_owner]];
                        return sol;
                    } while(std::next_permutation(hobby_perm.begin(), hobby_perm.end()));
                } while(std::next_permutation(pet_perm.begin(), pet_perm.end()));
            } while(std::next_permutation(drink_perm.begin(), drink_perm.end()));
        } while(std::next_permutation(nat_perm.begin(), nat_perm.end()));
    } while(std::next_permutation(color_perm.begin(), color_perm.end()));

    // If no solution found (should not happen)
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

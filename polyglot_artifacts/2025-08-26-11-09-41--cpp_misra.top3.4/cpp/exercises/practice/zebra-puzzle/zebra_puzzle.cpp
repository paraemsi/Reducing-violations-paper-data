#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <cstdint>

namespace zebra_puzzle {

namespace {

using std::array;
using std::string;

// House attributes
constexpr std::size_t house_count = 5U;

constexpr array<const char*, house_count> colors = {"red", "green", "ivory", "yellow", "blue"};
constexpr array<const char*, house_count> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
constexpr array<const char*, house_count> pets = {"dog", "snails", "fox", "horse", "zebra"};
constexpr array<const char*, house_count> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
constexpr array<const char*, house_count> hobbies = {"dancing", "reading", "painting", "chess", "football"};

// For MISRA: use fixed-width types
using index_t = std::uint8_t;

// Helper to generate all permutations of 0..N-1
template <std::size_t N>
class Permutator {
public:
    Permutator() : first(true) {
        for(index_t i = 0U; i < static_cast<index_t>(N); ++i) {
            perm[i] = i;
        }
    }
    bool next() {
        if(first) {
            first = false;
            return true;
        }
        return std::next_permutation(perm.begin(), perm.end());
    }
    array<index_t, N> perm{};
private:
    bool first;
};

} // anonymous namespace

Solution solve() {
    // Each attribute is an array of indices, where index is the house position (0..4)
    // The value at each index is the attribute's value (e.g. color[0] = 2 means house 0 is color #2)
    // We'll permute each attribute and check constraints

    // For performance, permute colors first, then nationalities, then pets, then drinks, then hobbies

    Permutator<house_count> color_perm;
    do {
        const array<index_t, house_count>& color = color_perm.perm;

        // Constraint 6: green is immediately right of ivory
        index_t green = 0U, ivory = 0U;
        for(index_t i = 0U; i < house_count; ++i) {
            if(color[i] == 1U) { green = i; } // green
            if(color[i] == 2U) { ivory = i; } // ivory
        }
        if((green != (ivory + 1U))) { continue; }

        Permutator<house_count> nat_perm;
        do {
            const array<index_t, house_count>& nat = nat_perm.perm;

            // Constraint 2: Englishman lives in red house
            index_t englishman = 0U, red = 0U;
            for(index_t i = 0U; i < house_count; ++i) {
                if(nat[i] == 0U) { englishman = i; } // Englishman
                if(color[i] == 0U) { red = i; } // red
            }
            if(englishman != red) { continue; }

            // Constraint 10: Norwegian lives in first house
            index_t norwegian = 0U;
            for(index_t i = 0U; i < house_count; ++i) {
                if(nat[i] == 3U) { norwegian = i; }
            }
            if(norwegian != 0U) { continue; }

            // Constraint 15: Norwegian lives next to blue house
            index_t blue = 0U;
            for(index_t i = 0U; i < house_count; ++i) {
                if(color[i] == 4U) { blue = i; }
            }
            if(((norwegian + 1U) != blue) && (norwegian != (blue + 1U))) { continue; }

            Permutator<house_count> pet_perm;
            do {
                const array<index_t, house_count>& pet = pet_perm.perm;

                // Constraint 3: Spaniard owns the dog
                index_t spaniard = 0U, dog = 0U;
                for(index_t i = 0U; i < house_count; ++i) {
                    if(nat[i] == 1U) { spaniard = i; }
                    if(pet[i] == 0U) { dog = i; }
                }
                if(spaniard != dog) { continue; }

                Permutator<house_count> drink_perm;
                do {
                    const array<index_t, house_count>& drink = drink_perm.perm;

                    // Constraint 4: green house drinks coffee
                    index_t green_house = 0U, coffee = 0U;
                    for(index_t i = 0U; i < house_count; ++i) {
                        if(color[i] == 1U) { green_house = i; }
                        if(drink[i] == 0U) { coffee = i; }
                    }
                    if(green_house != coffee) { continue; }

                    // Constraint 5: Ukrainian drinks tea
                    index_t ukrainian = 0U, tea = 0U;
                    for(index_t i = 0U; i < house_count; ++i) {
                        if(nat[i] == 2U) { ukrainian = i; }
                        if(drink[i] == 1U) { tea = i; }
                    }
                    if(ukrainian != tea) { continue; }

                    // Constraint 9: Middle house drinks milk
                    if(drink[2U] != 2U) { continue; }

                    Permutator<house_count> hobby_perm;
                    do {
                        const array<index_t, house_count>& hobby = hobby_perm.perm;

                        // Constraint 7: Snail owner likes dancing
                        index_t snails = 0U, dancing = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(pet[i] == 1U) { snails = i; }
                            if(hobby[i] == 0U) { dancing = i; }
                        }
                        if(snails != dancing) { continue; }

                        // Constraint 8: Yellow house is painter
                        index_t yellow = 0U, painting = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(color[i] == 3U) { yellow = i; }
                            if(hobby[i] == 2U) { painting = i; }
                        }
                        if(yellow != painting) { continue; }

                        // Constraint 12: Painter's house is next to house with horse
                        index_t horse = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(pet[i] == 3U) { horse = i; }
                        }
                        if(((painting + 1U) != horse) && (painting != (horse + 1U))) { continue; }

                        // Constraint 11: Reader lives next to fox owner
                        index_t reading = 0U, fox = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(hobby[i] == 1U) { reading = i; }
                            if(pet[i] == 2U) { fox = i; }
                        }
                        if(((reading + 1U) != fox) && (reading != (fox + 1U))) { continue; }

                        // Constraint 13: Football player drinks orange juice
                        index_t football = 0U, orange_juice = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(hobby[i] == 4U) { football = i; }
                            if(drink[i] == 3U) { orange_juice = i; }
                        }
                        if(football != orange_juice) { continue; }

                        // Constraint 14: Japanese plays chess
                        index_t japanese = 0U, chess = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(nat[i] == 4U) { japanese = i; }
                            if(hobby[i] == 3U) { chess = i; }
                        }
                        if(japanese != chess) { continue; }

                        // All constraints satisfied, find water drinker and zebra owner
                        index_t water = 0U, zebra = 0U;
                        for(index_t i = 0U; i < house_count; ++i) {
                            if(drink[i] == 4U) { water = i; }
                            if(pet[i] == 4U) { zebra = i; }
                        }
                        Solution sol;
                        sol.drinksWater = nationalities[nat[water]];
                        sol.ownsZebra = nationalities[nat[zebra]];
                        return sol;
                    } while(hobby_perm.next());
                } while(drink_perm.next());
            } while(pet_perm.next());
        } while(nat_perm.next());
    } while(color_perm.next());

    // If no solution found
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle

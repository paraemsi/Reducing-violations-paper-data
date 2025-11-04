#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <vector>
#include <string>

namespace zebra_puzzle {

using std::array;
using std::string;
using std::vector;

// All possible values for each attribute
constexpr array<const char*, 5> COLORS = {"red", "green", "ivory", "yellow", "blue"};
constexpr array<const char*, 5> NATIONALITIES = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
constexpr array<const char*, 5> PETS = {"dog", "snails", "fox", "horse", "zebra"};
constexpr array<const char*, 5> DRINKS = {"coffee", "tea", "milk", "orange juice", "water"};
constexpr array<const char*, 5> HOBBIES = {"dancing", "reading", "painter", "football", "chess"};

// Helper function to get the index of a value in an array
template <size_t N>
int index_of(const array<const char*, N>& arr, const string& value) {
    for (size_t i = 0; i < N; ++i) {
        if (arr[i] == value)
            return static_cast<int>(i);
    }
    return -1;
}

Solution solve() {
    // Each house is an index 0..4
    // We'll try all permutations for each attribute, and check constraints

    array<int, 5> color, nationality, pet, drink, hobby;

    // To speed up, fix some clues:
    // - Norwegian lives in first house (nationality[0] == Norwegian)
    // - Milk is drunk in the middle house (drink[2] == milk)
    // - Green is immediately right of ivory (color[green] == color[ivory]+1)
    // - Norwegian lives next to blue (abs(color[blue] - nationality[Norwegian]) == 1)
    // We'll permute in an order that allows us to prune early.

    do { // color
        // Green is immediately right of ivory
        int green = index_of(COLORS, "green");
        int ivory = index_of(COLORS, "ivory");
        if (std::find(color.begin(), color.end(), green) == color.end() ||
            std::find(color.begin(), color.end(), ivory) == color.end())
            continue;
        int green_pos = std::find(color.begin(), color.end(), green) - color.begin();
        int ivory_pos = std::find(color.begin(), color.end(), ivory) - color.begin();
        if (green_pos != ivory_pos + 1) continue;

        do { // nationality
            // Norwegian in first house
            int norwegian = index_of(NATIONALITIES, "Norwegian");
            if (nationality[0] != norwegian) continue;

            // Englishman lives in red house
            int englishman = index_of(NATIONALITIES, "Englishman");
            int red = index_of(COLORS, "red");
            int englishman_pos = std::find(nationality.begin(), nationality.end(), englishman) - nationality.begin();
            int red_pos = std::find(color.begin(), color.end(), red) - color.begin();
            if (englishman_pos != red_pos) continue;

            // Norwegian lives next to blue house
            int blue = index_of(COLORS, "blue");
            int blue_pos = std::find(color.begin(), color.end(), blue) - color.begin();
            if (std::abs(blue_pos - 0) != 1) continue;

            do { // pet
                // Spaniard owns the dog
                int spaniard = index_of(NATIONALITIES, "Spaniard");
                int dog = index_of(PETS, "dog");
                int spaniard_pos = std::find(nationality.begin(), nationality.end(), spaniard) - nationality.begin();
                int dog_pos = std::find(pet.begin(), pet.end(), dog) - pet.begin();
                if (spaniard_pos != dog_pos) continue;

                do { // drink
                    // Coffee in green house
                    int coffee = index_of(DRINKS, "coffee");
                    int green = index_of(COLORS, "green");
                    int coffee_pos = std::find(drink.begin(), drink.end(), coffee) - drink.begin();
                    int green_pos = std::find(color.begin(), color.end(), green) - color.begin();
                    if (coffee_pos != green_pos) continue;

                    // Ukrainian drinks tea
                    int ukrainian = index_of(NATIONALITIES, "Ukrainian");
                    int tea = index_of(DRINKS, "tea");
                    int ukrainian_pos = std::find(nationality.begin(), nationality.end(), ukrainian) - nationality.begin();
                    int tea_pos = std::find(drink.begin(), drink.end(), tea) - drink.begin();
                    if (ukrainian_pos != tea_pos) continue;

                    // Milk in middle house
                    int milk = index_of(DRINKS, "milk");
                    if (drink[2] != milk) continue;

                    do { // hobby
                        // Dancing: snails
                        int dancing = index_of(HOBBIES, "dancing");
                        int snails = index_of(PETS, "snails");
                        int dancing_pos = std::find(hobby.begin(), hobby.end(), dancing) - hobby.begin();
                        int snails_pos = std::find(pet.begin(), pet.end(), snails) - pet.begin();
                        if (dancing_pos != snails_pos) continue;

                        // Yellow: painter
                        int yellow = index_of(COLORS, "yellow");
                        int painter = index_of(HOBBIES, "painter");
                        int yellow_pos = std::find(color.begin(), color.end(), yellow) - color.begin();
                        int painter_pos = std::find(hobby.begin(), hobby.end(), painter) - hobby.begin();
                        if (yellow_pos != painter_pos) continue;

                        // Football: orange juice
                        int football = index_of(HOBBIES, "football");
                        int oj = index_of(DRINKS, "orange juice");
                        int football_pos = std::find(hobby.begin(), hobby.end(), football) - hobby.begin();
                        int oj_pos = std::find(drink.begin(), drink.end(), oj) - drink.begin();
                        if (football_pos != oj_pos) continue;

                        // Japanese: chess
                        int japanese = index_of(NATIONALITIES, "Japanese");
                        int chess = index_of(HOBBIES, "chess");
                        int japanese_pos = std::find(nationality.begin(), nationality.end(), japanese) - nationality.begin();
                        int chess_pos = std::find(hobby.begin(), hobby.end(), chess) - hobby.begin();
                        if (japanese_pos != chess_pos) continue;

                        // Reading lives next to fox
                        int reading = index_of(HOBBIES, "reading");
                        int fox = index_of(PETS, "fox");
                        int reading_pos = std::find(hobby.begin(), hobby.end(), reading) - hobby.begin();
                        int fox_pos = std::find(pet.begin(), pet.end(), fox) - pet.begin();
                        if (std::abs(reading_pos - fox_pos) != 1) continue;

                        // Painter's house next to horse
                        int horse = index_of(PETS, "horse");
                        if (std::abs(painter_pos - (std::find(pet.begin(), pet.end(), horse) - pet.begin())) != 1) continue;

                        // All constraints satisfied, now find water drinker and zebra owner
                        int water = index_of(DRINKS, "water");
                        int zebra = index_of(PETS, "zebra");
                        int water_pos = std::find(drink.begin(), drink.end(), water) - drink.begin();
                        int zebra_pos = std::find(pet.begin(), pet.end(), zebra) - pet.begin();

                        Solution sol;
                        sol.drinksWater = NATIONALITIES[nationality[water_pos]];
                        sol.ownsZebra = NATIONALITIES[nationality[zebra_pos]];
                        return sol;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(drink.begin(), drink.end()));
            } while (std::next_permutation(pet.begin(), pet.end()));
        } while (std::next_permutation(nationality.begin(), nationality.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // If no solution found
    return Solution{};
}

}  // namespace zebra_puzzle

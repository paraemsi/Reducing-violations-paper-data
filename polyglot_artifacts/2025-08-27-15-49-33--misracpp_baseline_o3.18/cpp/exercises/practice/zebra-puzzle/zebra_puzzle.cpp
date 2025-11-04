#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>  // std::abs overload for integral types
#include <cmath>    // std::abs overloads for floating and integral types
#include <string>

namespace zebra_puzzle {

namespace {

// Number of houses in the puzzle
constexpr int HOUSES = 5;

// Enumerations for each attribute
enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

// Helper: find the index of value in the given container
template <typename Arr>
int pos(const Arr &a, int value) {
    return static_cast<int>(std::find(a.begin(), a.end(), value) - a.begin());
}

// Map enums to human-readable strings for the result
const std::array<std::string, HOUSES> nationality_name{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

}  // namespace

Solution solve() {
    std::array<int, HOUSES> colors{RED, GREEN, IVORY, YELLOW, BLUE};
    std::array<int, HOUSES> nationalities{ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE};
    std::array<int, HOUSES> drinks{COFFEE, TEA, MILK, ORANGE_JUICE, WATER};
    std::array<int, HOUSES> pets{DOG, SNAIL, FOX, HORSE, ZEBRA};
    std::array<int, HOUSES> hobbies{DANCING, PAINTER, READING, FOOTBALL, CHESS};

    // Enumerate all possibilities with incremental pruning
    do {
        // 6.  Green is immediately right of Ivory
        if (pos(colors, GREEN) != pos(colors, IVORY) + 1) continue;

        do {
            // 2.  Englishman in red
            if (pos(nationalities, ENGLISHMAN) != pos(colors, RED)) continue;
            // 10. Norwegian in first house (index 0)
            if (pos(nationalities, NORWEGIAN) != 0) continue;
            // 15. Norwegian next to blue
            if (std::abs(pos(nationalities, NORWEGIAN) - pos(colors, BLUE)) != 1) continue;

            do {
                // 4.  Green drinks coffee
                if (pos(drinks, COFFEE) != pos(colors, GREEN)) continue;
                // 5.  Ukrainian drinks tea
                if (pos(drinks, TEA) != pos(nationalities, UKRAINIAN)) continue;
                // 9.  Middle house (index 2) drinks milk
                if (drinks[2] != MILK) continue;

                do {
                    // 3.  Spaniard owns dog
                    if (pos(pets, DOG) != pos(nationalities, SPANIARD)) continue;

                    do {
                        // 7.  Snail owner likes dancing
                        if (pos(pets, SNAIL) != pos(hobbies, DANCING)) continue;
                        // 8.  Yellow house painter
                        if (pos(colors, YELLOW) != pos(hobbies, PAINTER)) continue;
                        // 11. Reading next to fox
                        if (std::abs(pos(hobbies, READING) - pos(pets, FOX)) != 1) continue;
                        // 12. Painter next to horse
                        if (std::abs(pos(hobbies, PAINTER) - pos(pets, HORSE)) != 1) continue;
                        // 13. Football drinks orange juice
                        if (pos(hobbies, FOOTBALL) != pos(drinks, ORANGE_JUICE)) continue;
                        // 14. Japanese plays chess
                        if (pos(nationalities, JAPANESE) != pos(hobbies, CHESS)) continue;

                        // All constraints satisfied – build the solution
                        Solution sol;
                        sol.drinksWater = nationality_name[nationalities[pos(drinks, WATER)]];
                        sol.ownsZebra   = nationality_name[nationalities[pos(pets, ZEBRA)]];
                        return sol;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));

                } while (std::next_permutation(pets.begin(), pets.end()));

            } while (std::next_permutation(drinks.begin(), drinks.end()));

        } while (std::next_permutation(nationalities.begin(), nationalities.end()));

    } while (std::next_permutation(colors.begin(), colors.end()));

    // Should never reach here; puzzle guarantees a unique solution
    return {};
}

}  // namespace zebra_puzzle

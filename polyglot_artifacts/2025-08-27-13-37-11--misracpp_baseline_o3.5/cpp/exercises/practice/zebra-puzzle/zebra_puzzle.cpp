#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>

namespace zebra_puzzle {

namespace {

// Enumerations for each attribute set
enum Color  { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nation { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet    { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Drink  { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby  { READING, DANCING, PAINTING, FOOTBALL, CHESS };

// Helper for converting enumeration values to nationality strings
constexpr std::array<const char*, 5> NATION_NAMES{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
};

// Find the index of a value inside an std::array
template <typename T, std::size_t N>
std::size_t find_pos(const std::array<T, N>& arr, T value) {
    return static_cast<std::size_t>(
        std::distance(arr.begin(), std::find(arr.begin(), arr.end(), value)));
}

}  // namespace

Solution solve() {
    // Initial ordered arrays (required for std::next_permutation)
    std::array<int, 5> nation{ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE};
    std::array<int, 5> color{RED, GREEN, IVORY, YELLOW, BLUE};
    std::array<int, 5> drink{COFFEE, TEA, MILK, ORANGE_JUICE, WATER};
    std::array<int, 5> pet{DOG, SNAIL, FOX, HORSE, ZEBRA};
    std::array<int, 5> hobby{READING, DANCING, PAINTING, FOOTBALL, CHESS};

    //  Iterate through all feasible permutations while pruning aggressively
    std::sort(nation.begin(), nation.end());
    do {
        if (nation[0] != NORWEGIAN) continue;  // 10. Norwegian lives in the first house

        std::sort(color.begin(), color.end());
        do {
            // 2. The Englishman lives in the red house.
            if (color[find_pos(nation, ENGLISHMAN)] != RED) continue;
            // 15. The Norwegian lives next to the blue house.
            if (std::abs(static_cast<int>(find_pos(color, BLUE)) - 0) != 1) continue;
            // 6. The green house is immediately to the right of the ivory house.
            if (find_pos(color, GREEN) != find_pos(color, IVORY) + 1) continue;

            std::sort(drink.begin(), drink.end());
            do {
                // 9. The person in the middle house drinks milk.
                if (drink[2] != MILK) continue;
                // 4. Person in green house drinks coffee.
                if (drink[find_pos(color, GREEN)] != COFFEE) continue;
                // 5. The Ukrainian drinks tea.
                if (drink[find_pos(nation, UKRAINIAN)] != TEA) continue;

                std::sort(pet.begin(), pet.end());
                do {
                    // 3. The Spaniard owns the dog.
                    if (pet[find_pos(nation, SPANIARD)] != DOG) continue;

                    std::sort(hobby.begin(), hobby.end());
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (hobby[find_pos(pet, SNAIL)] != DANCING) continue;
                        // 8. The person in the yellow house is a painter.
                        if (color[find_pos(hobby, PAINTING)] != YELLOW) continue;
                        // 11. Reader next to fox owner.
                        if (std::abs(static_cast<int>(find_pos(hobby, READING)) -
                                      static_cast<int>(find_pos(pet, FOX))) != 1)
                            continue;
                        // 12. Painter's house next to horse.
                        if (std::abs(static_cast<int>(find_pos(hobby, PAINTING)) -
                                      static_cast<int>(find_pos(pet, HORSE))) != 1)
                            continue;
                        // 13. Football player drinks orange juice.
                        if (hobby[find_pos(drink, ORANGE_JUICE)] != FOOTBALL) continue;
                        // 14. The Japanese person plays chess.
                        if (hobby[find_pos(nation, JAPANESE)] != CHESS) continue;

                        // All constraints satisfied – construct the solution
                        Solution sol;
                        sol.drinksWater =
                            NATION_NAMES[nation[find_pos(drink, WATER)]];
                        sol.ownsZebra =
                            NATION_NAMES[nation[find_pos(pet, ZEBRA)]];
                        return sol;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(color.begin(), color.end()));
    } while (std::next_permutation(nation.begin(), nation.end()));

    // Should never be reached – puzzle has a unique solution
    return {};
}

}  // namespace zebra_puzzle

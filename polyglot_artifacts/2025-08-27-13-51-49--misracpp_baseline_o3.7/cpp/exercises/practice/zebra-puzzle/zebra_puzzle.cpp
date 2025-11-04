#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>
#include <utility>

namespace zebra_puzzle {

// Enumerations for every attribute
enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

template <typename T, std::size_t N>
inline std::size_t index_of(const std::array<T, N> &arr, T value) {
    return static_cast<std::size_t>(std::distance(arr.begin(),
                                                  std::find(arr.begin(), arr.end(), value)));
}

Solution solve() {
    // House indices are 0 .. 4 (left-to-right)
    std::array<int, 5> colors{RED, GREEN, IVORY, YELLOW, BLUE};
    do {
        // 6. Green is immediately to the right of ivory.
        if (index_of(colors, GREEN) != index_of(colors, IVORY) + 1) continue;

        std::array<int, 5> nationalities{ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE};
        do {
            // 2. Englishman lives in the red house.
            if (index_of(nationalities, ENGLISHMAN) != index_of(colors, RED)) continue;
            // 10. Norwegian lives in the first house (index 0).
            if (index_of(nationalities, NORWEGIAN) != 0) continue;
            // 15. Norwegian lives next to the blue house.
            if (std::abs(static_cast<int>(index_of(nationalities, NORWEGIAN)) -
                         static_cast<int>(index_of(colors, BLUE))) != 1)
                continue;

            std::array<int, 5> drinks{COFFEE, TEA, MILK, ORANGE_JUICE, WATER};
            do {
                // 4. Green house drinks coffee.
                if (index_of(colors, GREEN) != index_of(drinks, COFFEE)) continue;
                // 5. Ukrainian drinks tea.
                if (index_of(nationalities, UKRAINIAN) != index_of(drinks, TEA)) continue;
                // 9. Middle house drinks milk.
                if (index_of(drinks, MILK) != 2) continue;

                std::array<int, 5> pets{DOG, SNAIL, FOX, HORSE, ZEBRA};
                do {
                    // 3. Spaniard owns the dog.
                    if (index_of(nationalities, SPANIARD) != index_of(pets, DOG)) continue;

                    std::array<int, 5> hobbies{DANCING, PAINTER, READING, FOOTBALL, CHESS};
                    do {
                        // 7. Snail owner likes to go dancing.
                        if (index_of(pets, SNAIL) != index_of(hobbies, DANCING)) continue;
                        // 8. Yellow house is a painter.
                        if (index_of(colors, YELLOW) != index_of(hobbies, PAINTER)) continue;
                        // 11. Reader lives next to fox.
                        if (std::abs(static_cast<int>(index_of(hobbies, READING)) -
                                     static_cast<int>(index_of(pets, FOX))) != 1)
                            continue;
                        // 12. Painter's house is next to the house with the horse.
                        if (std::abs(static_cast<int>(index_of(hobbies, PAINTER)) -
                                     static_cast<int>(index_of(pets, HORSE))) != 1)
                            continue;
                        // 13. Football player drinks orange juice.
                        if (index_of(hobbies, FOOTBALL) != index_of(drinks, ORANGE_JUICE)) continue;
                        // 14. Japanese person plays chess.
                        if (index_of(nationalities, JAPANESE) != index_of(hobbies, CHESS)) continue;

                        // All constraints satisfied – build the answer.
                        const std::array<std::string, 5> nat_names{
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

                        Solution sol;
                        sol.drinksWater = nat_names[nationalities[index_of(drinks, WATER)]];
                        sol.ownsZebra   = nat_names[nationalities[index_of(pets, ZEBRA)]];
                        return sol;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // If no solution found (should not happen)
    return {"", ""};
}

}  // namespace zebra_puzzle

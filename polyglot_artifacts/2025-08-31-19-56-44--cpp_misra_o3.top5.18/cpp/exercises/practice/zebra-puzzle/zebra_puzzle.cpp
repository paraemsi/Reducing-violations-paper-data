#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

// Fixed-width alias to comply with MISRA “no plain int” rule.
using index_t = std::uint8_t;

// Enumeration for every attribute value.
enum class Color : index_t { BLUE = 0U, GREEN, IVORY, RED, YELLOW };
enum class Nationality : index_t { ENGLISH = 0U, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum class Pet : index_t { DOG = 0U, SNAILS, FOX, HORSE, ZEBRA };
enum class Drink : index_t { COFFEE = 0U, TEA, MILK, ORANGE_JUICE, WATER };
enum class Hobby : index_t { READING = 0U, PAINTING, DANCING, FOOTBALL, CHESS };

// Name tables to convert enumeration to std::string.
static const std::array<std::string, 5U> NATIONALITY_NAMES{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

// Helper – return the house index holding the given value.
template <typename T>
static index_t find_index(const std::array<T, 5U>& attr, T value)
{
    for (index_t i = 0U; i < static_cast<index_t>(attr.size()); ++i) {
        if (attr[static_cast<std::size_t>(i)] == value) {
            return i;
        }
    }
    // Should never happen in valid permutations.
    return 5U;
}

// Helper – check whether two houses are adjacent.
static bool is_neighbor(index_t h1, index_t h2)
{
    const std::int32_t diff = std::abs(
        static_cast<std::int32_t>(h1) - static_cast<std::int32_t>(h2));
    return diff == 1;
}

Solution solve()
{
    // Base permutation [0,1,2,3,4]
    const std::array<index_t, 5U> base{{0U, 1U, 2U, 3U, 4U}};

    std::array<Color, 5U>      colors{};
    std::array<Nationality, 5U> nations{};
    std::array<Pet, 5U>        pets{};
    std::array<Drink, 5U>      drinks{};
    std::array<Hobby, 5U>      hobbies{};

    // Enumerate color permutations first – apply colour-specific constraints.
    std::array<index_t, 5U> perm = base;
    do {
        for (index_t h = 0U; h < 5U; ++h) {
            colors[static_cast<std::size_t>(h)] =
                static_cast<Color>(perm[static_cast<std::size_t>(h)]);
        }

        const index_t house_green = find_index(colors, Color::GREEN);
        const index_t house_ivory = find_index(colors, Color::IVORY);
        if (house_green != static_cast<index_t>(house_ivory + 1U)) {
            continue; // Constraint 6
        }

        // Nationalities.
        perm = base;
        do {
            for (index_t h = 0U; h < 5U; ++h) {
                nations[static_cast<std::size_t>(h)] =
                    static_cast<Nationality>(perm[static_cast<std::size_t>(h)]);
            }

            // Constraint 10: Norwegian in first house.
            if (nations[0U] != Nationality::NORWEGIAN) {
                continue;
            }

            // Constraint 2: Englishman lives in the red house.
            if (colors[static_cast<std::size_t>(
                    find_index(nations, Nationality::ENGLISH))] != Color::RED) {
                continue;
            }

            // Constraint 15: Norwegian lives next to the blue house.
            if (!is_neighbor(find_index(nations, Nationality::NORWEGIAN),
                             find_index(colors, Color::BLUE))) {
                continue;
            }

            // Drinks.
            perm = base;
            do {
                for (index_t h = 0U; h < 5U; ++h) {
                    drinks[static_cast<std::size_t>(h)] =
                        static_cast<Drink>(perm[static_cast<std::size_t>(h)]);
                }

                // Constraint 4: Green house drinks coffee.
                if (drinks[house_green] != Drink::COFFEE) {
                    continue;
                }

                // Constraint 5: Ukrainian drinks tea.
                if (drinks[static_cast<std::size_t>(
                        find_index(nations, Nationality::UKRAINIAN))] != Drink::TEA) {
                    continue;
                }

                // Constraint 9: Middle house drinks milk.
                if (drinks[2U] != Drink::MILK) {
                    continue;
                }

                // Hobbies.
                perm = base;
                do {
                    for (index_t h = 0U; h < 5U; ++h) {
                        hobbies[static_cast<std::size_t>(h)] =
                            static_cast<Hobby>(perm[static_cast<std::size_t>(h)]);
                    }

                    // Constraint 8: Yellow house painter.
                    if (hobbies[static_cast<std::size_t>(
                            find_index(colors, Color::YELLOW))] != Hobby::PAINTING) {
                        continue;
                    }

                    // Constraint 13: Football drinks orange juice.
                    if (drinks[static_cast<std::size_t>(
                            find_index(hobbies, Hobby::FOOTBALL))] != Drink::ORANGE_JUICE) {
                        continue;
                    }

                    // Constraint 14: Japanese plays chess.
                    if (hobbies[static_cast<std::size_t>(
                            find_index(nations, Nationality::JAPANESE))] != Hobby::CHESS) {
                        continue;
                    }

                    // Pets.
                    perm = base;
                    do {
                        for (index_t h = 0U; h < 5U; ++h) {
                            pets[static_cast<std::size_t>(h)] =
                                static_cast<Pet>(perm[static_cast<std::size_t>(h)]);
                        }

                        // Constraint 3: Spaniard owns the dog.
                        if (pets[static_cast<std::size_t>(
                                find_index(nations, Nationality::SPANIARD))] != Pet::DOG) {
                            continue;
                        }

                        // Constraint 7: Snail owner dances.
                        if (hobbies[static_cast<std::size_t>(
                                find_index(pets, Pet::SNAILS))] != Hobby::DANCING) {
                            continue;
                        }

                        // Constraint 11: Reader lives next to fox owner.
                        if (!is_neighbor(find_index(hobbies, Hobby::READING),
                                         find_index(pets, Pet::FOX))) {
                            continue;
                        }

                        // Constraint 12: Painter next to horse.
                        if (!is_neighbor(find_index(hobbies, Hobby::PAINTING),
                                         find_index(pets, Pet::HORSE))) {
                            continue;
                        }

                        // All constraints satisfied – formulate answer.
                        const Nationality water_drinker =
                            nations[static_cast<std::size_t>(
                                find_index(drinks, Drink::WATER))];
                        const Nationality zebra_owner =
                            nations[static_cast<std::size_t>(
                                find_index(pets, Pet::ZEBRA))];

                        Solution sol{};
                        sol.drinksWater = NATIONALITY_NAMES
                            [static_cast<std::size_t>(water_drinker)];
                        sol.ownsZebra = NATIONALITY_NAMES
                            [static_cast<std::size_t>(zebra_owner)];
                        return sol;

                    } while (std::next_permutation(perm.begin(), perm.end()));
                } while (std::next_permutation(perm.begin(), perm.end()));
            } while (std::next_permutation(perm.begin(), perm.end()));
        } while (std::next_permutation(perm.begin(), perm.end()));
    } while (std::next_permutation(perm.begin(), perm.end()));

    // Should never fall through.
    return Solution{};
}

} // namespace zebra_puzzle

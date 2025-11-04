#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

/*  Enumerations for the five distinct values of every attribute.
 *  Their exact numerical values are irrelevant – they only need to be unique
 *  and in the range 0-4 so that they can be held in an std::int32_t and used
 *  as indices.
 */
enum class Color : std::int32_t { blue, green, ivory, red, yellow };
enum class Nationality : std::int32_t { englishman, spaniard, ukrainian, norwegian, japanese };
enum class Pet : std::int32_t { dog, fox, horse, snail, zebra };
enum class Drink : std::int32_t { coffee, tea, milk, orange_juice, water };
enum class Hobby : std::int32_t { chess, football, painting, reading, dancing };

/*  Convenience aliases that satisfy the “no built-in integral type names”
 *  requirement while still letting us write short, readable code.
 */
using Permutation = std::array<std::int32_t, 5>;

template <typename T>
[[nodiscard]] std::int32_t index_of(const Permutation& houses, T value)
{
    for (std::int32_t idx {0}; idx < 5; ++idx) {
        if (houses[static_cast<std::size_t>(idx)] == static_cast<std::int32_t>(value)) {
            return idx;
        }
    }
    return -1; /* unreachable – permutations always contain every value */
}

} // namespace

Solution solve()
{
    /*  Start with the identity permutation {0,1,2,3,4}.  We will generate every
     *  permutation with std::next_permutation, but we nest the permutations so
     *  that constraints can be applied as early as possible, dramatically
     *  reducing the search space.
     */
    Permutation colors   {0, 1, 2, 3, 4};
    Permutation nations  {0, 1, 2, 3, 4};
    Permutation pets     {0, 1, 2, 3, 4};
    Permutation drinks   {0, 1, 2, 3, 4};
    Permutation hobbies  {0, 1, 2, 3, 4};

    do { /* colors */
        const std::int32_t green_idx  {index_of(colors, Color::green)};
        const std::int32_t ivory_idx  {index_of(colors, Color::ivory)};

        if (green_idx != (ivory_idx + 1)) {
            continue; /* Constraint 6: green immediately right of ivory. */
        }

        const std::int32_t red_idx    {index_of(colors, Color::red)};
        const std::int32_t blue_idx   {index_of(colors, Color::blue)};
        const std::int32_t yellow_idx {index_of(colors, Color::yellow)};

        do { /* nationalities */
            const std::int32_t english_idx  {index_of(nations, Nationality::englishman)};
            if (english_idx != red_idx) {
                continue; /* Constraint 2 */
            }

            const std::int32_t norwegian_idx {index_of(nations, Nationality::norwegian)};
            if (norwegian_idx != 0) {
                continue; /* Constraint 10: first house (index 0). */
            }

            if ((norwegian_idx != (blue_idx - 1)) && (norwegian_idx != (blue_idx + 1))) {
                continue; /* Constraint 15: Norwegian next to blue. */
            }

            do { /* drinks */
                const std::int32_t coffee_idx {index_of(drinks, Drink::coffee)};
                if (coffee_idx != green_idx) {
                    continue; /* Constraint 4 */
                }

                const std::int32_t tea_idx {index_of(drinks, Drink::tea)};
                const std::int32_t ukrainian_idx {index_of(nations, Nationality::ukrainian)};
                if (tea_idx != ukrainian_idx) {
                    continue; /* Constraint 5 */
                }

                if (drinks[2] != static_cast<std::int32_t>(Drink::milk)) {
                    continue; /* Constraint 9: middle house (index 2). */
                }

                do { /* hobbies */
                    const std::int32_t painter_idx {index_of(hobbies, Hobby::painting)};
                    if (painter_idx != yellow_idx) {
                        continue; /* Constraint 8 */
                    }

                    const std::int32_t chess_idx {index_of(hobbies, Hobby::chess)};
                    const std::int32_t japanese_idx {index_of(nations, Nationality::japanese)};
                    if (chess_idx != japanese_idx) {
                        continue; /* Constraint 14 */
                    }

                    const std::int32_t football_idx {index_of(hobbies, Hobby::football)};
                    const std::int32_t orange_idx {index_of(drinks, Drink::orange_juice)};
                    if (football_idx != orange_idx) {
                        continue; /* Constraint 13 */
                    }

                    do { /* pets */
                        const std::int32_t dog_idx {index_of(pets, Pet::dog)};
                        const std::int32_t spaniard_idx {index_of(nations, Nationality::spaniard)};
                        if (dog_idx != spaniard_idx) {
                            continue; /* Constraint 3 */
                        }

                        const std::int32_t snail_idx {index_of(pets, Pet::snail)};
                        const std::int32_t dancing_idx {index_of(hobbies, Hobby::dancing)};
                        if (snail_idx != dancing_idx) {
                            continue; /* Constraint 7 */
                        }

                        /* Constraint 11: reading next to fox */
                        const std::int32_t reading_idx {index_of(hobbies, Hobby::reading)};
                        const std::int32_t fox_idx {index_of(pets, Pet::fox)};
                        if ((reading_idx != (fox_idx - 1)) && (reading_idx != (fox_idx + 1))) {
                            continue;
                        }

                        /* Constraint 12: painter next to horse */
                        const std::int32_t horse_idx {index_of(pets, Pet::horse)};
                        if ((painter_idx != (horse_idx - 1)) && (painter_idx != (horse_idx + 1))) {
                            continue;
                        }

                        /* All constraints satisfied – we have a solution. */
                        const std::int32_t water_idx {index_of(drinks, Drink::water)};
                        const std::int32_t zebra_idx {index_of(pets,   Pet::zebra)};

                        static constexpr std::array<const char*, 5> nation_names {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };

                        Solution sol;
                        sol.drinksWater = nation_names[static_cast<std::size_t>(nations[static_cast<std::size_t>(water_idx)])];
                        sol.ownsZebra   = nation_names[static_cast<std::size_t>(nations[static_cast<std::size_t>(zebra_idx)])];
                        return sol;
                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    /* The puzzle is guaranteed to have exactly one solution, so we should
     * never reach this point.  Still, return a default-constructed object to
     * satisfy the compiler.
     */
    return Solution{};
}

} // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <cmath>

namespace zebra_puzzle {

namespace {

/* Enumerations give readable indices into the permutation arrays.
 * The integral values are required for array indexing, therefore the
 * underlying type is explicitly fixed-width (std::int32_t).            */
enum class Nationality : std::int32_t {
    Englishman,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};

enum class Colour : std::int32_t {
    Red,
    Green,
    Ivory,
    Yellow,
    Blue
};

enum class Pet : std::int32_t {
    Dog,
    Snails,
    Fox,
    Horse,
    Zebra
};

enum class Drink : std::int32_t {
    Coffee,
    Tea,
    Milk,
    OrangeJuice,
    Water
};

enum class Hobby : std::int32_t {
    Dancing,
    Painting,
    Reading,
    Football,
    Chess
};

/* Helper to convert enum value to its positional index                */
template <typename EnumT>
constexpr auto toIndex(EnumT e) noexcept -> std::int32_t
{
    return static_cast<std::int32_t>(e);
}

}  // namespace

auto solve() -> Solution
{
    /* House indices: 0 == first (left-most), 4 == last (right-most)    */
    constexpr std::int32_t houseCount {5};

    std::array<std::string, houseCount> nationalityStr {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    /* Base permutation {0,1,2,3,4}; will be permuted in place.        */
    std::array<std::int32_t, houseCount> perm {{0, 1, 2, 3, 4}};

    /* Nationalities                                                   */
    std::array<std::int32_t, houseCount> nat = perm;

    do {
        /* 10. The Norwegian lives in the first house.                 */
        if (nat[toIndex(Nationality::Norwegian)] != 0) {
            continue;
        }

        /* Colours                                                     */
        std::array<std::int32_t, houseCount> col = perm;
        do {
            /* 6. Green immediately right of ivory.                    */
            if (col[toIndex(Colour::Green)] !=
                (col[toIndex(Colour::Ivory)] + 1)) {
                continue;
            }

            /* 2. Englishman in red house.                             */
            if (nat[toIndex(Nationality::Englishman)] !=
                col[toIndex(Colour::Red)]) {
                continue;
            }

            /* 15. Norwegian next to blue house.                       */
            if (std::abs(nat[toIndex(Nationality::Norwegian)] -
                          col[toIndex(Colour::Blue)]) != 1) {
                continue;
            }

            /* Drinks                                                  */
            std::array<std::int32_t, houseCount> dri = perm;
            do {
                /* 4. Green house drinks coffee.                       */
                if (dri[toIndex(Drink::Coffee)] !=
                    col[toIndex(Colour::Green)]) {
                    continue;
                }

                /* 5. Ukrainian drinks tea.                            */
                if (dri[toIndex(Drink::Tea)] !=
                    nat[toIndex(Nationality::Ukrainian)]) {
                    continue;
                }

                /* 9. Middle house drinks milk.                        */
                if (dri[toIndex(Drink::Milk)] != 2) {
                    continue;
                }

                /* 13. Football drinks orange juice.                   */
                /* We'll check this once hobbies are assigned.         */

                /* Pets                                                */
                std::array<std::int32_t, houseCount> pet = perm;
                do {
                    /* 3. Spaniard owns the dog.                       */
                    if (pet[toIndex(Pet::Dog)] !=
                        nat[toIndex(Nationality::Spaniard)]) {
                        continue;
                    }

                    /* 11. Reading next to fox (to be checked later).  */
                    /* 12. Painter next to horse (to be checked later).*/

                    /* Hobbies                                         */
                    std::array<std::int32_t, houseCount> hob = perm;
                    do {
                        /* 7. Snail owner likes dancing.               */
                        if (hob[toIndex(Hobby::Dancing)] !=
                            pet[toIndex(Pet::Snails)]) {
                            continue;
                        }

                        /* 8. Yellow house resident is a painter.      */
                        if (hob[toIndex(Hobby::Painting)] !=
                            col[toIndex(Colour::Yellow)]) {
                            continue;
                        }

                        /* 13. Football drinks orange juice.           */
                        if (dri[toIndex(Drink::OrangeJuice)] !=
                            hob[toIndex(Hobby::Football)]) {
                            continue;
                        }

                        /* 14. Japanese plays chess.                   */
                        if (hob[toIndex(Hobby::Chess)] !=
                            nat[toIndex(Nationality::Japanese)]) {
                            continue;
                        }

                        /* 11. Reading next to fox.                    */
                        if (std::abs(hob[toIndex(Hobby::Reading)] -
                                     pet[toIndex(Pet::Fox)]) != 1) {
                            continue;
                        }

                        /* 12. Painter next to horse.                  */
                        if (std::abs(hob[toIndex(Hobby::Painting)] -
                                     pet[toIndex(Pet::Horse)]) != 1) {
                            continue;
                        }

                        /* All constraints satisfied – determine result*/
                        Solution sol {};
                        sol.drinksWater =
                            nationalityStr[ static_cast<std::size_t>(
                                nat[toIndex(Nationality::Englishman)] /*dummy*/ ) ];
                        /* Actually we need nationality who drinks water */
                        for (std::int32_t n {0}; n < houseCount; ++n) {
                            if (dri[toIndex(Drink::Water)] ==
                                nat[n]) {
                                sol.drinksWater = nationalityStr[ static_cast<std::size_t>(n) ];
                            }
                            if (pet[toIndex(Pet::Zebra)] ==
                                nat[n]) {
                                sol.ownsZebra = nationalityStr[ static_cast<std::size_t>(n) ];
                            }
                        }
                        return sol;
                    } while (std::next_permutation(hob.begin(), hob.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(dri.begin(), dri.end()));
        } while (std::next_permutation(col.begin(), col.end()));
    } while (std::next_permutation(nat.begin(), nat.end()));

    /* No solution – should never happen with a correct puzzle.        */
    return Solution{};
}

}  // namespace zebra_puzzle

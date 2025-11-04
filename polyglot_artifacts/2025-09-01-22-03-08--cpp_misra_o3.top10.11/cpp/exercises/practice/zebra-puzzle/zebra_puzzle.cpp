#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

/*  Enumerations for the categorical attributes.
 *  The numeric values are used only as array indices – no
 *  arithmetic is performed on them, hence they comply with
 *  the MISRA “numeric assignment” rules.
 */
enum class Nat : std::int8_t {
    Englishman = 0,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};

enum class Color : std::int8_t {
    Red = 0,
    Green,
    Ivory,
    Yellow,
    Blue
};

enum class Pet : std::int8_t {
    Dog = 0,
    Snail,
    Fox,
    Horse,
    Zebra
};

enum class Drink : std::int8_t {
    Coffee = 0,
    Tea,
    Milk,
    OrangeJuice,
    Water
};

enum class Hobby : std::int8_t {
    Dancing = 0,
    Painting,
    Reading,
    Football,
    Chess
};

using Perm = std::array<std::int8_t, 5>;

template <typename Predicate>
auto first_valid_permutation(Predicate pred) -> Perm
{
    Perm p {{0, 1, 2, 3, 4}};
    /*  std::next_permutation returns false when the input is the last
     *  permutation; we therefore evaluate the predicate on the first
     *  permutation before the loop begins.
     */
    do {
        if (pred(p)) {
            return p;
        }
    } while (std::next_permutation(p.begin(), p.end()));

    /*  The puzzle has a unique solution, therefore this point is
     *  unreachable.  Still, we return a zero-initialised permutation
     *  to satisfy every return-path requirement.
     */
    return Perm {{0, 0, 0, 0, 0}};
}

} // unnamed namespace

auto solve() -> Solution
{
    /*  Prepare string lookup tables for the final answer. */
    static const std::array<std::string, 5> natStr {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };
    [[maybe_unused]] static const std::array<std::string, 5> petStr {
        "dog", "snail", "fox", "horse", "zebra"
    };
    [[maybe_unused]] static const std::array<std::string, 5> drinkStr {
        "coffee", "tea", "milk", "orange juice", "water"
    };

    /*  Generate every permutation of the five colours subject to the
     *  constraint that the green house is immediately to the right of
     *  the ivory house (statement 6).
     */
    const Perm colourPerm = first_valid_permutation([](const Perm& colour) noexcept -> bool {
        /*  Locate the ivory and green houses. */
        std::int8_t ivoryPos { -1 };
        std::int8_t greenPos { -1 };
        for (std::int8_t i { 0 }; i < static_cast<std::int8_t>(colour.size()); ++i) {
            if (colour[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Color::Ivory)) {
                ivoryPos = i;
            } else if (colour[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Color::Green)) {
                greenPos = i;
            }
        }

        /*  Green must be exactly to the right of ivory. */
        return (greenPos == (ivoryPos + 1));
    });

    /*  Fix the colour permutation found; it reduces the remaining search
     *  space by almost a factor of 5.
     */
    const auto& colour = colourPerm;

    /*  Permute nationalities with all applicable constraints. */
    const Perm natPerm = first_valid_permutation([&colour](const Perm& nat) noexcept -> bool {
        /*  Statement 2 – Englishman in red house. */
        std::int8_t redHouse {-1};
        std::int8_t engHouse {-1};
        for (std::int8_t i {0}; i < 5; ++i) {
            if (colour[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Color::Red)) {
                redHouse = i;
            }
            if (nat[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Nat::Englishman)) {
                engHouse = i;
            }
        }
        if (engHouse != redHouse) {
            return false;
        }

        /*  Statement 10 – Norwegian in the first house (index 0). */
        if (nat[0] != static_cast<std::int8_t>(Nat::Norwegian)) {
            return false;
        }

        /*  Statement 15 – Norwegian lives next to the blue house. */
        std::int8_t blueHouse { -1 };
        for (std::int8_t i {0}; i < 5; ++i) {
            if (colour[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Color::Blue)) {
                blueHouse = i;
            }
        }
        /*  Blue must be the house immediately to the right of the
         *  Norwegian’s first house, i.e. index 1.
         */
        if (blueHouse != static_cast<std::int8_t>(1)) {
            return false;
        }

        return true;
    });

    const auto& nat = natPerm;

    /*  Permute drinks with all constraints. */
    const Perm drinkPerm = first_valid_permutation([&colour, &nat](const Perm& drink) noexcept -> bool {
        /*  Statement 4 – green house drinks coffee. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (colour[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Color::Green)) {
                if (drink[static_cast<std::size_t>(i)] != static_cast<std::int8_t>(Drink::Coffee)) {
                    return false;
                }
            }
        }

        /*  Statement 5 – Ukrainian drinks tea. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (nat[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Nat::Ukrainian)) {
                if (drink[static_cast<std::size_t>(i)] != static_cast<std::int8_t>(Drink::Tea)) {
                    return false;
                }
            }
        }

        /*  Statement 9 – middle house (index 2) drinks milk. */
        if (drink[2] != static_cast<std::int8_t>(Drink::Milk)) {
            return false;
        }

        return true;
    });

    const auto& drink = drinkPerm;

    /*  Permute pets subject to constraints. */
    const Perm petPerm = first_valid_permutation([&nat](const Perm& pet) noexcept -> bool {
        /*  Statement 3 – Spaniard owns the dog. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (nat[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Nat::Spaniard)) {
                return (pet[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Pet::Dog));
            }
        }
        return false;
    });

    const auto& pet = petPerm;

    /*  Finally, permute hobbies. */
    const Perm hobbyPerm = first_valid_permutation([&](const Perm& hobby) noexcept -> bool {

        /*  Statement 7 – snail owner likes dancing. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (pet[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Pet::Snail)) {
                if (hobby[static_cast<std::size_t>(i)] != static_cast<std::int8_t>(Hobby::Dancing)) {
                    return false;
                }
            }
        }

        /*  Statement 8 – person in yellow house is a painter. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (colour[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Color::Yellow)) {
                if (hobby[static_cast<std::size_t>(i)] != static_cast<std::int8_t>(Hobby::Painting)) {
                    return false;
                }
            }
        }

        /*  Statement 11 – reader lives next to fox owner. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (hobby[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Hobby::Reading)) {
                const bool left { (i > 0) &&
                                  (pet[static_cast<std::size_t>(i - 1)] == static_cast<std::int8_t>(Pet::Fox)) };
                const bool right { (i < 4) &&
                                   (pet[static_cast<std::size_t>(i + 1)] == static_cast<std::int8_t>(Pet::Fox)) };
                if (!left && !right) {
                    return false;
                }
            }
        }

        /*  Statement 12 – painter next to horse owner. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (hobby[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Hobby::Painting)) {
                const bool left { (i > 0) &&
                                  (pet[static_cast<std::size_t>(i - 1)] == static_cast<std::int8_t>(Pet::Horse)) };
                const bool right { (i < 4) &&
                                   (pet[static_cast<std::size_t>(i + 1)] == static_cast<std::int8_t>(Pet::Horse)) };
                if (!left && !right) {
                    return false;
                }
            }
        }

        /*  Statement 13 – football player drinks orange juice. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (hobby[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Hobby::Football)) {
                if (drink[static_cast<std::size_t>(i)] != static_cast<std::int8_t>(Drink::OrangeJuice)) {
                    return false;
                }
            }
        }

        /*  Statement 14 – Japanese plays chess. */
        for (std::int8_t i {0}; i < 5; ++i) {
            if (nat[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Nat::Japanese)) {
                if (hobby[static_cast<std::size_t>(i)] != static_cast<std::int8_t>(Hobby::Chess)) {
                    return false;
                }
            }
        }

        return true;
    });

    const auto& hobby = hobbyPerm;

    /*  Identify the unique water-drinker and zebra owner. */
    std::string waterDrinker {};
    std::string zebraOwner {};
    for (std::int8_t i {0}; i < 5; ++i) {
        if (drink[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Drink::Water)) {
            waterDrinker = natStr[static_cast<std::size_t>(nat[static_cast<std::size_t>(i)])];
        }
        if (pet[static_cast<std::size_t>(i)] == static_cast<std::int8_t>(Pet::Zebra)) {
            zebraOwner = natStr[static_cast<std::size_t>(nat[static_cast<std::size_t>(i)])];
        }
    }

    return Solution {waterDrinker, zebraOwner};
}

}  // namespace zebra_puzzle

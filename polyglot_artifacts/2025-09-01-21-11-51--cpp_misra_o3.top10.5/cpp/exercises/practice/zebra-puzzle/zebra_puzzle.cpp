#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstddef>

namespace zebra_puzzle {

Solution solve()
{
    using index_t = std::uint8_t;

    /* Enumerations for the five possible values of each category */
    enum class Color : index_t { Red, Green, Ivory, Yellow, Blue };
    enum class Nat   : index_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum class Pet   : index_t { Dog, Snail, Fox, Horse, Zebra };
    enum class Drink : index_t { Coffee, Tea, Milk, OrangeJuice, Water };
    enum class Hobby : index_t { Dancing, Painting, Reading, Football, Chess };

    /* Helper lambda for absolute distance between two house indices */
    auto const distance_one = [](index_t lhs, index_t rhs) noexcept -> bool
    {
        return ((lhs > rhs) ? (lhs - rhs) : (rhs - lhs)) == static_cast<index_t>(1U);
    };

    /* Permutation base */
    constexpr std::array<index_t, 5U> base { 0U, 1U, 2U, 3U, 4U };

    std::array<std::string, 5U> const nat_names {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    /* Enumerate colours first – earliest strong constraint (ivory/green order) */
    std::array<index_t, 5U> colors = base;
    do
    {
        /* 6. Green house is immediately to the right of the ivory house */
        if (colors[static_cast<index_t>(Color::Green)]
            != (colors[static_cast<index_t>(Color::Ivory)]
                + static_cast<index_t>(1U)))
        {
            continue;
        }

        /* Enumerate nationalities */
        std::array<index_t, 5U> nats = base;
        do
        {
            /* 10. Norwegian lives in the first house */
            if (nats[static_cast<index_t>(Nat::Norwegian)] != static_cast<index_t>(0U))
            {
                continue;
            }

            /* 2. Englishman lives in the red house */
            if (nats[static_cast<index_t>(Nat::Englishman)]
                != colors[static_cast<index_t>(Color::Red)])
            {
                continue;
            }

            /* 15. Norwegian lives next to the blue house */
            if (!distance_one(
                    nats[static_cast<index_t>(Nat::Norwegian)],
                    colors[static_cast<index_t>(Color::Blue)]))
            {
                continue;
            }

            /* Enumerate drinks */
            std::array<index_t, 5U> drinks = base;
            do
            {
                /* 9. Middle house drinks milk */
                if (drinks[static_cast<index_t>(Drink::Milk)] != static_cast<index_t>(2U))
                {
                    continue;
                }

                /* 4. Green house drinks coffee */
                if (drinks[static_cast<index_t>(Drink::Coffee)]
                    != colors[static_cast<index_t>(Color::Green)])
                {
                    continue;
                }

                /* 5. Ukrainian drinks tea */
                if (nats[static_cast<index_t>(Nat::Ukrainian)]
                    != drinks[static_cast<index_t>(Drink::Tea)])
                {
                    continue;
                }

                /* Enumerate pets */
                std::array<index_t, 5U> pets = base;
                do
                {
                    /* 3. Spaniard owns the dog */
                    if (nats[static_cast<index_t>(Nat::Spaniard)]
                        != pets[static_cast<index_t>(Pet::Dog)])
                    {
                        continue;
                    }

                    /* Enumerate hobbies */
                    std::array<index_t, 5U> hobbies = base;
                    do
                    {
                        /* 8. Yellow house is a painter */
                        if (hobbies[static_cast<index_t>(Hobby::Painting)]
                            != colors[static_cast<index_t>(Color::Yellow)])
                        {
                            continue;
                        }

                        /* 14. Japanese plays chess */
                        if (hobbies[static_cast<index_t>(Hobby::Chess)]
                            != nats[static_cast<index_t>(Nat::Japanese)])
                        {
                            continue;
                        }

                        /* 7. The snail owner likes to go dancing */
                        if (pets[static_cast<index_t>(Pet::Snail)]
                            != hobbies[static_cast<index_t>(Hobby::Dancing)])
                        {
                            continue;
                        }

                        /* 13. Football player drinks orange juice */
                        if (hobbies[static_cast<index_t>(Hobby::Football)]
                            != drinks[static_cast<index_t>(Drink::OrangeJuice)])
                        {
                            continue;
                        }

                        /* 11. Reader lives next to fox owner */
                        if (!distance_one(
                                hobbies[static_cast<index_t>(Hobby::Reading)],
                                pets[static_cast<index_t>(Pet::Fox)]))
                        {
                            continue;
                        }

                        /* 12. Painter’s house is next to the house with the horse */
                        if (!distance_one(
                                hobbies[static_cast<index_t>(Hobby::Painting)],
                                pets[static_cast<index_t>(Pet::Horse)]))
                        {
                            continue;
                        }

                        /* All constraints satisfied – build solution */
                        Solution sol;

                        /* Who drinks water? */
                        {
                            index_t const water_house =
                                drinks[static_cast<index_t>(Drink::Water)];
                            auto const it =
                                std::find(nats.begin(), nats.end(), water_house);
                            std::size_t const nat_idx =
                                static_cast<std::size_t>(std::distance(nats.begin(), it));
                            sol.drinksWater = nat_names[nat_idx];
                        }

                        /* Who owns the zebra? */
                        {
                            index_t const zebra_house =
                                pets[static_cast<index_t>(Pet::Zebra)];
                            auto const it =
                                std::find(nats.begin(), nats.end(), zebra_house);
                            std::size_t const nat_idx =
                                static_cast<std::size_t>(std::distance(nats.begin(), it));
                            sol.ownsZebra = nat_names[nat_idx];
                        }

                        return sol; /* Unique solution found */
                    }
                    while (std::next_permutation(
                        hobbies.begin(), hobbies.end()));
                }
                while (std::next_permutation(pets.begin(), pets.end()));
            }
            while (std::next_permutation(drinks.begin(), drinks.end()));
        }
        while (std::next_permutation(nats.begin(), nats.end()));
    }
    while (std::next_permutation(colors.begin(), colors.end()));

    /* Fallback (the puzzle is guaranteed to have a solution) */
    return Solution{};
}

} /* namespace zebra_puzzle */

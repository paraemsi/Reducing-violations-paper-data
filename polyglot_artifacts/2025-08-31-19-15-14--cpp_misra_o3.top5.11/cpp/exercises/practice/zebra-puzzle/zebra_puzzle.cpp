#include "zebra_puzzle.h"

#include <array>
#include <algorithm>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

/* Enumerations with fixed-width underlying type to satisfy MISRA rules. */
enum class Colour      : std::uint8_t { red, green, ivory, yellow, blue };
enum class Nation      : std::uint8_t { english, spaniard, ukrainian, norwegian, japanese };
enum class Pet         : std::uint8_t { dog, snails, fox, horse, zebra };
enum class Drink       : std::uint8_t { coffee, tea, milk, orange_juice, water };
enum class Hobby       : std::uint8_t { dancing, painting, reading, football, chess };

template<typename T>
using Line = std::array<T, 5U>;   /* One attribute for each of the five houses. */

constexpr std::uint8_t LEFT  = 0U;
constexpr std::uint8_t MID   = 2U;

/* Helper returning absolute distance of two indexes (small unsigned so safe). */
static auto adj(std::uint8_t a, std::uint8_t b) noexcept -> bool
{
    return (a > b) ? ((a - b) == 1U) : ((b - a) == 1U);
}

} // unnamed namespace


auto solve() -> Solution
{
    Line<std::uint8_t> base{{0U, 1U, 2U, 3U, 4U}};

    Line<Colour>    colours{};
    Line<Nation>    nations{};
    Line<Pet>       pets{};
    Line<Drink>     drinks{};
    Line<Hobby>     hobbies{};

    /* Pre-build name look-up tables for the answer. */
    constexpr const char* nation_names[] = { "Englishman", "Spaniard", "Ukrainian",
                                             "Norwegian", "Japanese" };


    /* Iterate permutations with early pruning ----------------------------- */
    Line<std::uint8_t> p = base;

    /* Colours */
    do {
        colours = { static_cast<Colour>(p[0]), static_cast<Colour>(p[1]),
                    static_cast<Colour>(p[2]), static_cast<Colour>(p[3]),
                    static_cast<Colour>(p[4]) };

        /* 6. green is immediately right of ivory (index +1). */
        std::uint8_t ivory_idx{ 0U };
        std::uint8_t green_idx{ 0U };
        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
            if (colours[i] == Colour::ivory) { ivory_idx = i; }
            if (colours[i] == Colour::green) { green_idx = i; }
        }
        if (green_idx != (ivory_idx + 1U)) { continue; }

        /* 15. Norwegian lives next to blue → save blue index for nation loop. */
        std::uint8_t blue_idx{ 0U };
        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
            if (colours[i] == Colour::blue) { blue_idx = i; }
        }

        /* Nations ---------------------------------------------------------- */
        Line<std::uint8_t> pn = base;
        do {
            nations = { static_cast<Nation>(pn[0]), static_cast<Nation>(pn[1]),
                        static_cast<Nation>(pn[2]), static_cast<Nation>(pn[3]),
                        static_cast<Nation>(pn[4]) };

            /* 10. Norwegian in first house. */
            if (nations[LEFT] != Nation::norwegian) { continue; }
            /* 1. Englishman lives in red. */
            std::uint8_t english_idx{ 0U };
            for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                if (nations[i] == Nation::english) { english_idx = i; }
            }
            if (colours[english_idx] != Colour::red) { continue; }
            /* 15. Norwegian next to blue. */
            if (!adj(LEFT, blue_idx)) { continue; }

            /* Drinks ------------------------------------------------------- */
            Line<std::uint8_t> pd = base;
            do {
                drinks = { static_cast<Drink>(pd[0]), static_cast<Drink>(pd[1]),
                           static_cast<Drink>(pd[2]), static_cast<Drink>(pd[3]),
                           static_cast<Drink>(pd[4]) };

                /* 9. Middle house drinks milk. */
                if (drinks[MID] != Drink::milk) { continue; }
                /* 4. Green -> coffee. */
                if (drinks[green_idx] != Drink::coffee) { continue; }
                /* 5. Ukrainian -> tea. */
                std::uint8_t ukr_idx{ 0U };
                for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                    if (nations[i] == Nation::ukrainian) { ukr_idx = i; }
                }
                if (drinks[ukr_idx] != Drink::tea) { continue; }

                /* Hobbies --------------------------------------------------- */
                Line<std::uint8_t> ph = base;
                do {
                    hobbies = { static_cast<Hobby>(ph[0]), static_cast<Hobby>(ph[1]),
                                static_cast<Hobby>(ph[2]), static_cast<Hobby>(ph[3]),
                                static_cast<Hobby>(ph[4]) };

                    /* 8. Yellow -> painting. */
                    std::uint8_t yellow_idx{ 0U };
                    for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                        if (colours[i] == Colour::yellow) { yellow_idx = i; }
                    }
                    if (hobbies[yellow_idx] != Hobby::painting) { continue; }
                    /* 13. Football -> orange juice. */
                    std::uint8_t football_idx{ 0U };
                    for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                        if (hobbies[i] == Hobby::football) { football_idx = i; }
                    }
                    if (drinks[football_idx] != Drink::orange_juice) { continue; }
                    /* 14. Japanese -> chess. */
                    std::uint8_t jap_idx{ 0U };
                    for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                        if (nations[i] == Nation::japanese) { jap_idx = i; }
                    }
                    if (hobbies[jap_idx] != Hobby::chess) { continue; }

                    /* Pets --------------------------------------------------- */
                    Line<std::uint8_t> pp = base;
                    do {
                        pets = { static_cast<Pet>(pp[0]), static_cast<Pet>(pp[1]),
                                 static_cast<Pet>(pp[2]), static_cast<Pet>(pp[3]),
                                 static_cast<Pet>(pp[4]) };

                        /* 3. Spaniard owns dog. */
                        std::uint8_t sp_idx{ 0U };
                        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                            if (nations[i] == Nation::spaniard) { sp_idx = i; }
                        }
                        if (pets[sp_idx] != Pet::dog) { continue; }
                        /* 7. Snails -> dancing. */
                        std::uint8_t sn_idx{ 0U };
                        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                            if (pets[i] == Pet::snails) { sn_idx = i; }
                        }
                        if (hobbies[sn_idx] != Hobby::dancing) { continue; }
                        /* 11. Reading next to fox. */
                        std::uint8_t fox_idx{ 0U };
                        std::uint8_t read_idx{ 0U };
                        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                            if (pets[i] == Pet::fox)    { fox_idx  = i; }
                            if (hobbies[i] == Hobby::reading) { read_idx = i; }
                        }
                        if (!adj(fox_idx, read_idx)) { continue; }
                        /* 12. Painter next to horse. */
                        std::uint8_t horse_idx{ 0U };
                        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                            if (pets[i] == Pet::horse) { horse_idx = i; }
                        }
                        if (!adj(horse_idx, yellow_idx)) { continue; } /* painter == yellow */

                        /* All constraints satisfied – build answer ----------- */
                        Solution sol{};
                        std::uint8_t water_idx{ 0U };
                        std::uint8_t zebra_idx{ 0U };
                        for (std::uint8_t i{ 0U }; i < 5U; ++i) {
                            if (drinks[i] == Drink::water) { water_idx = i; }
                            if (pets[i]   == Pet::zebra)  { zebra_idx = i; }
                        }
                        sol.drinksWater = nation_names[static_cast<std::uint8_t>(nations[water_idx])];
                        sol.ownsZebra   = nation_names[static_cast<std::uint8_t>(nations[zebra_idx])];
                        return sol;

                    } while (std::next_permutation(pp.begin(), pp.end()));
                } while (std::next_permutation(ph.begin(), ph.end()));
            } while (std::next_permutation(pd.begin(), pd.end()));
        } while (std::next_permutation(pn.begin(), pn.end()));
    } while (std::next_permutation(p.begin(), p.end()));

    /* The puzzle has exactly one solution, so code should never reach here. */
    return Solution{};
}

}  // namespace zebra_puzzle

#include "zebra_puzzle.h"

#include <array>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>   // for std::abs(int)

namespace zebra_puzzle {

// Map index → nationality string (order must match the enumeration below)
static const std::array<std::string, 5> kNationalityNames{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
};

Solution solve() {
    // Enumerations for clarity (values 0-4).
    enum Color       { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Pet         { DOG, SNAIL, FOX, HORSE, ZEBRA };
    enum Drink       { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    enum Hobby       { READING, DANCING, PAINTING, FOOTBALL, CHESS };

    constexpr int kHouses = 5;
    const std::array<int, kHouses> init{0, 1, 2, 3, 4};

    // Colours ----------------------------------------------------------------
    std::array<int, kHouses> colors = init;
    do {
        if (colors[GREEN] != colors[IVORY] + 1) continue;               // (6)

        const int blue_pos   = colors[BLUE];
        const int red_pos    = colors[RED];
        const int yellow_pos = colors[YELLOW];
        const int green_pos  = colors[GREEN];

        // Nationalities ------------------------------------------------------
        std::array<int, kHouses> nations = init;
        do {
            if (nations[NORWEGIAN] != 0) continue;                      // (10)
            if (std::abs(nations[NORWEGIAN] - blue_pos) != 1) continue; // (15)
            if (nations[ENGLISHMAN] != red_pos) continue;               // (2)

            const int ukrainian_pos = nations[UKRAINIAN];
            const int japanese_pos  = nations[JAPANESE];

            // Drinks ---------------------------------------------------------
            std::array<int, kHouses> drinks = init;
            do {
                if (drinks[COFFEE] != green_pos) continue;              // (4)
                if (drinks[TEA] != ukrainian_pos) continue;             // (5)
                if (drinks[MILK] != 2) continue;                        // (9)

                const int oj_pos = drinks[ORANGE_JUICE];

                // Pets -------------------------------------------------------
                std::array<int, kHouses> pets = init;
                do {
                    if (pets[DOG] != nations[SPANIARD]) continue;       // (3)

                    const int fox_pos   = pets[FOX];
                    const int horse_pos = pets[HORSE];
                    const int snail_pos = pets[SNAIL];

                    // Hobbies / Professions ----------------------------------
                    std::array<int, kHouses> hobbies = init;
                    do {
                        if (hobbies[PAINTING] != yellow_pos) continue;          // (8)
                        if (hobbies[DANCING] != snail_pos) continue;            // (7)
                        if (std::abs(hobbies[READING] - fox_pos) != 1) continue;// (11)
                        if (std::abs(hobbies[PAINTING] - horse_pos) != 1) continue;// (12)
                        if (hobbies[FOOTBALL] != oj_pos) continue;              // (13)
                        if (hobbies[CHESS] != japanese_pos) continue;           // (14)

                        // All constraints satisfied – construct solution.
                        const int water_pos = drinks[WATER];
                        const int zebra_pos = pets[ZEBRA];

                        auto nationality_at = [&](int house) -> std::string {
                            for (int n = 0; n < kHouses; ++n)
                                if (nations[n] == house) return kNationalityNames[n];
                            return {};
                        };

                        Solution sol;
                        sol.drinksWater = nationality_at(water_pos);
                        sol.ownsZebra   = nationality_at(zebra_pos);
                        return sol;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nations.begin(), nations.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // The puzzle is guaranteed to have a unique solution; this is fallback.
    return {};
}

}  // namespace zebra_puzzle

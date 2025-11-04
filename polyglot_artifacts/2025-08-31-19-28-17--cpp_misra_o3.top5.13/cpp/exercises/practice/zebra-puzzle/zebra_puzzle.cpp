#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <string>

namespace zebra_puzzle {
using std::int32_t;

namespace {  // unnamed namespace for internal helpers

using HouseIndex = int32_t;

constexpr int32_t housesCount = 5;

/* Enumerations for the various attributes */
enum Color : int32_t { Red, Green, Ivory, Yellow, Blue };
enum Nationality : int32_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum Pet : int32_t { Dog, Snail, Fox, Horse, Zebra };
enum Drink : int32_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum Hobby : int32_t { Dancing, Painting, Reading, Football, Chess };

/* Human-readable names for the nationalities – index matches enum value */
const std::array<std::string, housesCount> nationalityNames = {
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
};

/* Helper that delegates to std::next_permutation for std::array */
template <typename T>
bool nextPermutation(std::array<T, housesCount>& arr) {
    return std::next_permutation(arr.begin(), arr.end());
}

}  // unnamed namespace

Solution solve() {
    /* Each array maps attribute-value → house index */
    std::array<int32_t, housesCount> colors        = {0, 1, 2, 3, 4};
    std::array<int32_t, housesCount> nationalities = {0, 1, 2, 3, 4};
    std::array<int32_t, housesCount> pets          = {0, 1, 2, 3, 4};
    std::array<int32_t, housesCount> drinks        = {0, 1, 2, 3, 4};
    std::array<int32_t, housesCount> hobbies       = {0, 1, 2, 3, 4};

    do {
        /* 6. Green is immediately to the right of Ivory */
        if(colors[Green] != (colors[Ivory] + 1)) {
            continue;
        }

        do {
            /* 10. Norwegian lives in first house */
            if(nationalities[Norwegian] != 0) {
                continue;
            }
            /* 2. Englishman lives in red house */
            if(nationalities[Englishman] != colors[Red]) {
                continue;
            }
            /* 15. Norwegian lives next to blue house */
            if(std::abs(nationalities[Norwegian] - colors[Blue]) != 1) {
                continue;
            }

            do {
                /* 3. Spaniard owns dog */
                if(nationalities[Spaniard] != pets[Dog]) {
                    continue;
                }
                /* 7. Snail owner likes dancing */
                if(pets[Snail] != hobbies[Dancing]) {
                    continue;
                }
                /* 11. Reader lives next to fox owner */
                if(std::abs(hobbies[Reading] - pets[Fox]) != 1) {
                    continue;
                }
                /* 12. Painter next to horse owner */
                if(std::abs(hobbies[Painting] - pets[Horse]) != 1) {
                    continue;
                }

                do {
                    /* 9. Milk in middle house (index 2) */
                    if(drinks[Milk] != 2) {
                        continue;
                    }
                    /* 4. Coffee in green house */
                    if(colors[Green] != drinks[Coffee]) {
                        continue;
                    }
                    /* 5. Ukrainian drinks tea */
                    if(nationalities[Ukrainian] != drinks[Tea]) {
                        continue;
                    }
                    /* 13. Football player drinks orange juice */
                    if(hobbies[Football] != drinks[OrangeJuice]) {
                        continue;
                    }

                    do {
                        /* 8. Yellow house – painter */
                        if(colors[Yellow] != hobbies[Painting]) {
                            continue;
                        }
                        /* 14. Japanese plays chess */
                        if(nationalities[Japanese] != hobbies[Chess]) {
                            continue;
                        }

                        /* All constraints satisfied – construct solution */
                        HouseIndex waterHouse = drinks[Water];
                        HouseIndex zebraHouse = pets[Zebra];

                        std::string waterDrinker{};
                        std::string zebraOwner{};

                        for(int32_t n = 0; n < housesCount; ++n) {
                            if(nationalities[n] == waterHouse) {
                                waterDrinker = nationalityNames[static_cast<std::size_t>(n)];
                            }
                            if(nationalities[n] == zebraHouse) {
                                zebraOwner = nationalityNames[static_cast<std::size_t>(n)];
                            }
                        }

                        Solution sol{};
                        sol.drinksWater = waterDrinker;
                        sol.ownsZebra   = zebraOwner;
                        return sol;

                    } while(nextPermutation(hobbies));

                } while(nextPermutation(drinks));

            } while(nextPermutation(pets));

        } while(nextPermutation(nationalities));

    } while(nextPermutation(colors));

    /* Should never reach here for a valid puzzle definition */
    return Solution{};
}

}  // namespace zebra_puzzle

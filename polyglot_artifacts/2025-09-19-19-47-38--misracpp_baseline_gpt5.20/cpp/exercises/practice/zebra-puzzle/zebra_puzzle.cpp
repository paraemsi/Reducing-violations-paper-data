#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>

namespace zebra_puzzle {

namespace {
using Perm = std::array<int, 5>;

template <typename Container>
Perm invert(const Container& m) {
    Perm inv{};
    for (int i = 0; i < 5; ++i) {
        inv[m[i]] = i;
    }
    return inv;
}

enum Color { Red, Green, Ivory, Yellow, Blue };
enum Nat { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum Pet { Dog, Snails, Fox, Horse, Zebra };
enum Hobby { Dancing, Painter, Reading, Football, Chess };

constexpr std::array<const char*, 5> NatNames = {
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
};

}  // namespace

Solution solve() {
    Perm base = {0, 1, 2, 3, 4};

    // Colors
    Perm colors = base;
    do {
        // 6: The green house is immediately to the right of the ivory house.
        if (colors[Green] != colors[Ivory] + 1) continue;

        // Nationalities
        Perm nats = base;
        do {
            // 10: The Norwegian lives in the first house.
            if (nats[Norwegian] != 0) continue;

            // 2: The Englishman lives in the red house.
            if (nats[Englishman] != colors[Red]) continue;

            // 15: The Norwegian lives next to the blue house.
            if (std::abs(nats[Norwegian] - colors[Blue]) != 1) continue;

            // Drinks
            Perm drinks = base;
            do {
                // 9: The person in the middle house drinks milk.
                if (drinks[Milk] != 2) continue;

                // 4: The person in the green house drinks coffee.
                if (drinks[Coffee] != colors[Green]) continue;

                // 5: The Ukrainian drinks tea.
                if (drinks[Tea] != nats[Ukrainian]) continue;

                // Hobbies
                Perm hobbies = base;
                do {
                    // 8: The person in the yellow house is a painter.
                    if (hobbies[Painter] != colors[Yellow]) continue;

                    // 14: The Japanese person plays chess.
                    if (hobbies[Chess] != nats[Japanese]) continue;

                    // 13: The person who plays football drinks orange juice.
                    if (drinks[OrangeJuice] != hobbies[Football]) continue;

                    // Pets
                    Perm pets = base;
                    do {
                        // 3: The Spaniard owns the dog.
                        if (pets[Dog] != nats[Spaniard]) continue;

                        // 12: The painter's house is next to the house with the horse.
                        if (std::abs(hobbies[Painter] - pets[Horse]) != 1) continue;

                        // 11: The person who enjoys reading lives in the house next to the person with the fox.
                        if (std::abs(hobbies[Reading] - pets[Fox]) != 1) continue;

                        // 7: The snail owner likes to go dancing.
                        if (pets[Snails] != hobbies[Dancing]) continue;

                        // Found a consistent assignment.
                        auto invNat = invert(nats);

                        Solution sol;
                        sol.drinksWater = NatNames[invNat[drinks[Water]]];
                        sol.ownsZebra = NatNames[invNat[pets[Zebra]]];
                        return sol;
                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nats.begin(), nats.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Should never reach here if the puzzle has a unique solution.
    return Solution{};
}

}  // namespace zebra_puzzle

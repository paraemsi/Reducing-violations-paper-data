#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>

namespace zebra_puzzle {

namespace {

// Enumerations for each category
enum Nationality { Englishman = 0, Spaniard, Ukrainian, Norwegian, Japanese, NationalityCount };
enum Color { Red = 0, Green, Ivory, Yellow, Blue, ColorCount };
enum Drink { Coffee = 0, Tea, Milk, OrangeJuice, Water, DrinkCount };
enum Pet { Dog = 0, Snails, Fox, Horse, Zebra, PetCount };
enum Hobby { Dancing = 0, Painting, Reading, Football, Chess, HobbyCount };

// Helper to check adjacency
inline bool adjacent(int a, int b) { return std::abs(a - b) == 1; }

}  // namespace

Solution solve() {
    // We map each value in a category to a position [0..4]:
    // For example, nat_pos[Englishman] == position of the Englishman.
    using Positions = std::array<int, 5>;

    // Names for output
    static const std::array<std::string, NationalityCount> nationalityNames{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    // Base permutation to iterate over
    Positions base{{0, 1, 2, 3, 4}};

    // Nationalities: constrain Norwegian to position 0
    Positions nat_pos = base;
    Solution solution{};

    do {
        if (nat_pos[Norwegian] != 0) continue;

        // Colors: constrain Blue to 1 (Norwegian lives next to Blue and is at 0)
        Positions color_pos = base;
        do {
            if (color_pos[Blue] != 1) continue;
            // Green immediately to the right of Ivory
            if (color_pos[Green] != color_pos[Ivory] + 1) continue;
            // Englishman lives in Red
            if (nat_pos[Englishman] != color_pos[Red]) continue;

            // Drinks: Milk at middle (2), Green -> Coffee, Ukrainian -> Tea
            Positions drink_pos = base;
            do {
                if (drink_pos[Milk] != 2) continue;
                if (drink_pos[Coffee] != color_pos[Green]) continue;
                if (drink_pos[Tea] != nat_pos[Ukrainian]) continue;

                // Pets: Spaniard -> Dog
                Positions pet_pos = base;
                do {
                    if (pet_pos[Dog] != nat_pos[Spaniard]) continue;

                    // Hobbies:
                    Positions hobby_pos = base;
                    do {
                        // Snails owner likes Dancing
                        if (hobby_pos[Dancing] != pet_pos[Snails]) continue;
                        // Yellow house is a Painter
                        if (hobby_pos[Painting] != color_pos[Yellow]) continue;
                        // Japanese plays Chess
                        if (hobby_pos[Chess] != nat_pos[Japanese]) continue;
                        // Football player drinks Orange Juice
                        if (hobby_pos[Football] != drink_pos[OrangeJuice]) continue;
                        // Reader lives next to the Fox
                        if (!adjacent(hobby_pos[Reading], pet_pos[Fox])) continue;
                        // Painter's house is next to the house with the Horse
                        if (!adjacent(hobby_pos[Painting], pet_pos[Horse])) continue;

                        // All constraints satisfied: determine answers
                        int water_pos = drink_pos[Water];
                        int zebra_pos = pet_pos[Zebra];

                        // Find nationalities at those positions
                        int water_nat = -1;
                        int zebra_nat = -1;
                        for (int n = 0; n < NationalityCount; ++n) {
                            if (nat_pos[n] == water_pos) water_nat = n;
                            if (nat_pos[n] == zebra_pos) zebra_nat = n;
                        }

                        if (water_nat != -1 && zebra_nat != -1) {
                            solution.drinksWater = nationalityNames[water_nat];
                            solution.ownsZebra = nationalityNames[zebra_nat];
                            return solution;
                        }

                    } while (std::next_permutation(hobby_pos.begin(), hobby_pos.end()));
                } while (std::next_permutation(pet_pos.begin(), pet_pos.end()));
            } while (std::next_permutation(drink_pos.begin(), drink_pos.end()));
        } while (std::next_permutation(color_pos.begin(), color_pos.end()));
    } while (std::next_permutation(nat_pos.begin(), nat_pos.end()));

    // If somehow not found (should not happen), return empty strings
    return solution;
}

}  // namespace zebra_puzzle

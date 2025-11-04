#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>

namespace zebra_puzzle {

namespace {

constexpr int N = 5;

int index_of(const std::array<int, N>& a, int value) {
    for (int i = 0; i < N; ++i) {
        if (a[i] == value) return i;
    }
    return -1;
}

}  // namespace

Solution solve() {
    // Enumerations mapped to 0..4 for each category
    enum Color { Red, Green, Ivory, Yellow, Blue };
    enum Nation { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Pet { Dog, Fox, Horse, Snails, Zebra };
    enum Hobby { Dancing, Painting, Reading, Football, Chess };

    std::array<int, N> base = {0, 1, 2, 3, 4};

    std::array<int, N> color = base;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        if (index_of(color, Green) != index_of(color, Ivory) + 1) continue;

        std::array<int, N> nation = base;
        do {
            // 10. The Norwegian lives in the first house.
            if (index_of(nation, Norwegian) != 0) continue;

            // 2. The Englishman lives in the red house.
            if (index_of(nation, Englishman) != index_of(color, Red)) continue;

            // 15. The Norwegian lives next to the blue house.
            if (std::abs(index_of(nation, Norwegian) - index_of(color, Blue)) != 1) continue;

            std::array<int, N> drink = base;
            do {
                // 4. The person in the green house drinks coffee.
                if (index_of(color, Green) != index_of(drink, Coffee)) continue;

                // 5. The Ukrainian drinks tea.
                if (index_of(nation, Ukrainian) != index_of(drink, Tea)) continue;

                // 9. The person in the middle house drinks milk.
                if (index_of(drink, Milk) != 2) continue;

                std::array<int, N> pet = base;
                do {
                    // 3. The Spaniard owns the dog.
                    if (index_of(nation, Spaniard) != index_of(pet, Dog)) continue;

                    std::array<int, N> hobby = base;
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (index_of(pet, Snails) != index_of(hobby, Dancing)) continue;

                        // 8. The person in the yellow house is a painter.
                        if (index_of(color, Yellow) != index_of(hobby, Painting)) continue;

                        // 12. The painter's house is next to the house with the horse.
                        if (std::abs(index_of(hobby, Painting) - index_of(pet, Horse)) != 1) continue;

                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (std::abs(index_of(hobby, Reading) - index_of(pet, Fox)) != 1) continue;

                        // 13. The person who plays football drinks orange juice.
                        if (index_of(hobby, Football) != index_of(drink, OrangeJuice)) continue;

                        // 14. The Japanese person plays chess.
                        if (index_of(nation, Japanese) != index_of(hobby, Chess)) continue;

                        // All constraints satisfied. Build the solution.
                        int water_house = index_of(drink, Water);
                        int zebra_house = index_of(pet, Zebra);

                        static const char* nation_names[N] = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

                        Solution sol;
                        sol.drinksWater = nation_names[nation[water_house]];
                        sol.ownsZebra = nation_names[nation[zebra_house]];
                        return sol;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(nation.begin(), nation.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Fallback (should never be reached with valid constraints)
    return {};
}

}  // namespace zebra_puzzle

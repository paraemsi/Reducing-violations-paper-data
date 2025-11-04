#include "zebra_puzzle.h"

#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>

namespace zebra_puzzle {

Solution solve() {
    constexpr int HOUSE_COUNT = 5;

    enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
    constexpr int COLOR_COUNT = 5;
    enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    constexpr int NATIONALITY_COUNT = 5;
    enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
    constexpr int PET_COUNT = 5;
    enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    constexpr int DRINK_COUNT = 5;
    enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS };
    constexpr int HOBBY_COUNT = 5;

    const std::array<std::string, NATIONALITY_COUNT> nationality_names{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    auto adjacent = [](int a, int b) { return std::abs(a - b) == 1; };

    std::array<int, COLOR_COUNT> color_to_house{};
    std::array<int, NATIONALITY_COUNT> nat_to_house{};
    std::array<int, DRINK_COUNT> drink_to_house{};
    std::array<int, PET_COUNT> pet_to_house{};
    std::array<int, HOBBY_COUNT> hobby_to_house{};

    std::array<int, HOUSE_COUNT> colors_perm{};
    std::iota(colors_perm.begin(), colors_perm.end(), 0);

    do { // Colors permutation
        color_to_house = colors_perm;

        // #6: The green house is immediately to the right of the ivory house.
        if (color_to_house[GREEN] != color_to_house[IVORY] + 1)
            continue;

        std::array<int, HOUSE_COUNT> nat_perm{};
        std::iota(nat_perm.begin(), nat_perm.end(), 0);

        do { // Nationalities permutation
            nat_to_house = nat_perm;

            // #10: The Norwegian lives in the first house.
            if (nat_to_house[NORWEGIAN] != 0)
                continue;

            // #2: The Englishman lives in the red house.
            if (nat_to_house[ENGLISHMAN] != color_to_house[RED])
                continue;

            // #15: The Norwegian lives next to the blue house.
            if (!adjacent(nat_to_house[NORWEGIAN], color_to_house[BLUE]))
                continue;

            std::array<int, HOUSE_COUNT> drink_perm{};
            std::iota(drink_perm.begin(), drink_perm.end(), 0);

            do { // Drinks permutation
                drink_to_house = drink_perm;

                // #4: The person in the green house drinks coffee.
                if (drink_to_house[COFFEE] != color_to_house[GREEN])
                    continue;

                // #5: The Ukrainian drinks tea.
                if (drink_to_house[TEA] != nat_to_house[UKRAINIAN])
                    continue;

                // #9: The person in the middle house drinks milk.
                if (drink_to_house[MILK] != 2)
                    continue;

                std::array<int, HOUSE_COUNT> pet_perm{};
                std::iota(pet_perm.begin(), pet_perm.end(), 0);

                do { // Pets permutation
                    pet_to_house = pet_perm;

                    // #3: The Spaniard owns the dog.
                    if (pet_to_house[DOG] != nat_to_house[SPANIARD])
                        continue;

                    std::array<int, HOUSE_COUNT> hobby_perm{};
                    std::iota(hobby_perm.begin(), hobby_perm.end(), 0);

                    do { // Hobbies permutation
                        hobby_to_house = hobby_perm;

                        // #7: The snail owner likes to go dancing.
                        if (hobby_to_house[DANCING] != pet_to_house[SNAIL])
                            continue;

                        // #8: The person in the yellow house is a painter.
                        if (hobby_to_house[PAINTING] != color_to_house[YELLOW])
                            continue;

                        // #12: The painter's house is next to the house with the horse.
                        if (!adjacent(hobby_to_house[PAINTING], pet_to_house[HORSE]))
                            continue;

                        // #11: The person who enjoys reading lives next to the person with the fox.
                        if (!adjacent(hobby_to_house[READING], pet_to_house[FOX]))
                            continue;

                        // #13: The person who plays football drinks orange juice.
                        if (drink_to_house[ORANGE_JUICE] != hobby_to_house[FOOTBALL])
                            continue;

                        // #14: The Japanese person plays chess.
                        if (hobby_to_house[CHESS] != nat_to_house[JAPANESE])
                            continue;

                        // All constraints satisfied.
                        int house_water = drink_to_house[WATER];
                        int house_zebra = pet_to_house[ZEBRA];

                        int water_idx = -1;
                        int zebra_idx = -1;
                        for (int n = 0; n < NATIONALITY_COUNT; ++n) {
                            if (nat_to_house[n] == house_water)
                                water_idx = n;
                            if (nat_to_house[n] == house_zebra)
                                zebra_idx = n;
                        }

                        Solution sol;
                        sol.drinksWater = nationality_names[water_idx];
                        sol.ownsZebra  = nationality_names[zebra_idx];
                        return sol;

                    } while (std::next_permutation(hobby_perm.begin(), hobby_perm.end()));

                } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));

            } while (std::next_permutation(drink_perm.begin(), drink_perm.end()));

        } while (std::next_permutation(nat_perm.begin(), nat_perm.end()));

    } while (std::next_permutation(colors_perm.begin(), colors_perm.end()));

    // Fallback (should never happen)
    return Solution{};
}

}  // namespace zebra_puzzle

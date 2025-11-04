#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <string>

namespace zebra_puzzle {

namespace {

enum Nationality { Englishman = 0, Spaniard, Ukrainian, Norwegian, Japanese };
enum Color { Red = 0, Green, Ivory, Yellow, Blue };
enum Pet { Dog = 0, Snails, Fox, Horse, Zebra };
enum Drink { Coffee = 0, Tea, Milk, OrangeJuice, Water };
enum Hobby { Dancing = 0, Painting, Reading, Football, Chess };

inline bool adjacent(int a, int b) {
    return (a + 1 == b) || (b + 1 == a);
}

inline int posOf(const std::array<int, 5>& a, int value) {
    for (int i = 0; i < 5; ++i) {
        if (a[i] == value) return i;
    }
    return -1;
}

}  // namespace

Solution solve() {
    static const char* kNationalityNames[5] = {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    // Each array maps house index (0..4, left to right) to the value enum.
    std::array<int, 5> nat = {0, 1, 2, 3, 4};
    do {
        // 10. The Norwegian lives in the first house.
        if (posOf(nat, Norwegian) != 0) continue;

        std::array<int, 5> col = {0, 1, 2, 3, 4};
        do {
            // 6. The green house is immediately to the right of the ivory house.
            if (!(posOf(col, Green) == posOf(col, Ivory) + 1)) continue;

            // 2. The Englishman lives in the red house.
            if (posOf(nat, Englishman) != posOf(col, Red)) continue;

            // 15. The Norwegian lives next to the blue house.
            if (!adjacent(posOf(nat, Norwegian), posOf(col, Blue))) continue;

            std::array<int, 5> drink = {0, 1, 2, 3, 4};
            do {
                // 9. The person in the middle house drinks milk.
                if (posOf(drink, Milk) != 2) continue;

                // 5. The Ukrainian drinks tea.
                if (posOf(nat, Ukrainian) != posOf(drink, Tea)) continue;

                // 4. The person in the green house drinks coffee.
                if (posOf(col, Green) != posOf(drink, Coffee)) continue;

                std::array<int, 5> pet = {0, 1, 2, 3, 4};
                do {
                    // 3. The Spaniard owns the dog.
                    if (posOf(nat, Spaniard) != posOf(pet, Dog)) continue;

                    std::array<int, 5> hobby = {0, 1, 2, 3, 4};
                    do {
                        // 7. The snail owner likes to go dancing.
                        if (posOf(pet, Snails) != posOf(hobby, Dancing)) continue;

                        // 8. The person in the yellow house is a painter.
                        if (posOf(col, Yellow) != posOf(hobby, Painting)) continue;

                        // 11. The person who enjoys reading lives next to the person with the fox.
                        if (!adjacent(posOf(hobby, Reading), posOf(pet, Fox))) continue;

                        // 12. The painter's house is next to the house with the horse.
                        if (!adjacent(posOf(hobby, Painting), posOf(pet, Horse))) continue;

                        // 13. The person who plays football drinks orange juice.
                        if (posOf(hobby, Football) != posOf(drink, OrangeJuice)) continue;

                        // 14. The Japanese person plays chess.
                        if (posOf(nat, Japanese) != posOf(hobby, Chess)) continue;

                        // Found a consistent solution.
                        int water_house = posOf(drink, Water);
                        int zebra_house = posOf(pet, Zebra);

                        Solution s;
                        s.drinksWater = kNationalityNames[nat[water_house]];
                        s.ownsZebra = kNationalityNames[nat[zebra_house]];
                        return s;

                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(pet.begin(), pet.end()));
            } while (std::next_permutation(drink.begin(), drink.end()));
        } while (std::next_permutation(col.begin(), col.end()));
    } while (std::next_permutation(nat.begin(), nat.end()));

    // If somehow not found (should not happen), return empty strings.
    Solution s;
    s.drinksWater = "";
    s.ownsZebra = "";
    return s;
}

}  // namespace zebra_puzzle

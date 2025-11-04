#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

namespace zebra_puzzle {

Solution solve() {
    // Enumerations to identify attribute values
    enum Color  { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Nation { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Pet    { DOG, SNAILS, FOX, HORSE, ZEBRA };
    enum Drink  { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    enum Hobby  { DANCING, PAINTING, READING, FOOTBALL, CHESS };

    const std::string nation_names[] = {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    auto next_to = [](int a, int b) { return std::abs(a - b) == 1; };

    std::array<int, 5> color, nation, drink, hobby, pet, base;

    /* --- Color permutations (rule 6) ------------------------------------ */
    std::vector<std::array<int, 5>> color_perms;
    base = {0, 1, 2, 3, 4};
    do {
        int ivory = -1, green = -1;
        for (int i = 0; i < 5; ++i) {
            if (base[i] == IVORY) ivory = i;
            if (base[i] == GREEN) green = i;
        }
        if (green == ivory + 1) color_perms.push_back(base);
    } while (std::next_permutation(base.begin(), base.end()));

    /* --- Nation permutations (rule 10) ---------------------------------- */
    std::vector<std::array<int, 5>> nation_perms;
    base = {0, 1, 2, 3, 4};
    do {
        if (base[0] == NORWEGIAN) nation_perms.push_back(base);
    } while (std::next_permutation(base.begin(), base.end()));

    /* --- Search --------------------------------------------------------- */
    for (const auto& col : color_perms) {
        color = col;
        int red    = std::find(color.begin(), color.end(), RED)    - color.begin();
        int blue   = std::find(color.begin(), color.end(), BLUE)   - color.begin();
        int yellow = std::find(color.begin(), color.end(), YELLOW) - color.begin();
        int green  = std::find(color.begin(), color.end(), GREEN)  - color.begin();

        for (const auto& nat : nation_perms) {
            nation = nat;
            int english   = std::find(nation.begin(), nation.end(), ENGLISHMAN) - nation.begin();
            int spaniard  = std::find(nation.begin(), nation.end(), SPANIARD)   - nation.begin();
            int ukrainian = std::find(nation.begin(), nation.end(), UKRAINIAN)  - nation.begin();
            int japanese  = std::find(nation.begin(), nation.end(), JAPANESE)   - nation.begin();
            int norwegian = 0; // fixed by rule 10

            if (english != red) continue;                 // rule 2
            if (!next_to(norwegian, blue)) continue;      // rule 15

            /* Drinks: milk middle (rule 9), coffee/green (4), tea/Ukr. (5) */
            base = {0, 1, 2, 3, 4};
            do {
                if (base[2] != MILK) continue;
                if (base[green] != COFFEE) continue;
                if (base[ukrainian] != TEA) continue;
                drink = base;

                /* Hobbies: painter/yellow (8), football/OJ (13), chess/Jap (14) */
                std::array<int,5> hobby_base = {0,1,2,3,4};
                do {
                    if (hobby_base[yellow] != PAINTING) continue;
                    int oj = std::find(drink.begin(), drink.end(), ORANGE_JUICE) - drink.begin();
                    if (hobby_base[oj] != FOOTBALL) continue;
                    if (hobby_base[japanese] != CHESS) continue;
                    hobby = hobby_base;

                    /* Pets with remaining rules */
                    std::array<int,5> pet_base = {0,1,2,3,4};
                    do {
                        if (pet_base[spaniard] != DOG) continue;          // rule 3
                        int dancing = std::find(hobby.begin(), hobby.end(), DANCING) - hobby.begin();
                        if (pet_base[dancing] != SNAILS) continue;        // rule 7
                        int reading = std::find(hobby.begin(), hobby.end(), READING) - hobby.begin();
                        int fox     = std::find(pet_base.begin(), pet_base.end(), FOX) - pet_base.begin();
                        if (!next_to(reading, fox)) continue;             // rule 11
                        int painter = yellow;                             // rule 8
                        int horse   = std::find(pet_base.begin(), pet_base.end(), HORSE) - pet_base.begin();
                        if (!next_to(painter, horse)) continue;           // rule 12
                        pet = pet_base;

                        /* Solution found */
                        int water  = std::find(drink.begin(), drink.end(), WATER) - drink.begin();
                        int zebra  = std::find(pet.begin(),   pet.end(),   ZEBRA) - pet.begin();
                        return {nation_names[nation[water]], nation_names[nation[zebra]]};
                    } while (std::next_permutation(pet_base.begin(), pet_base.end()));
                } while (std::next_permutation(hobby_base.begin(), hobby_base.end()));
            } while (std::next_permutation(base.begin(), base.end()));
        }
    }
    return {}; // Should never reach if the puzzle is valid
}

} // namespace zebra_puzzle

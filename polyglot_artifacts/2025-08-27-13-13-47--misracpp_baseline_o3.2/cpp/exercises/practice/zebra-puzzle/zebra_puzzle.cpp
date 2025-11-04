#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

namespace zebra_puzzle {

enum Color { Red, Green, Ivory, Yellow, Blue };
enum Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum Pet { Dog, Snail, Fox, Horse, Zebra };
enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum Hobby { Reading, Dancing, Painting, Football, Chess };

static const std::array<std::string, 5> nationality_names{
    "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

Solution solve() {
    std::array<int, 5> colors{{Red, Green, Ivory, Yellow, Blue}};
    std::array<int, 5> nationalities{{Englishman, Spaniard, Ukrainian, Norwegian,
                                      Japanese}};
    std::array<int, 5> pets{{Dog, Snail, Fox, Horse, Zebra}};
    std::array<int, 5> drinks{{Coffee, Tea, Milk, OrangeJuice, Water}};
    std::array<int, 5> hobbies{{Reading, Dancing, Painting, Football, Chess}};

    do {  // colors
        int greenHouse = -1, ivoryHouse = -1, redHouse = -1, yellowHouse = -1,
            blueHouse = -1;
        for (int h = 0; h < 5; ++h) {
            switch (colors[h]) {
                case Green:
                    greenHouse = h;
                    break;
                case Ivory:
                    ivoryHouse = h;
                    break;
                case Red:
                    redHouse = h;
                    break;
                case Yellow:
                    yellowHouse = h;
                    break;
                case Blue:
                    blueHouse = h;
                    break;
            }
        }
        if (greenHouse != ivoryHouse + 1) continue;  // #6

        std::sort(nationalities.begin(), nationalities.end());
        do {  // nationalities
            int englishHouse = -1, spaniardHouse = -1, ukrainianHouse = -1,
                norwegianHouse = -1, japaneseHouse = -1;
            for (int h = 0; h < 5; ++h) {
                switch (nationalities[h]) {
                    case Englishman:
                        englishHouse = h;
                        break;
                    case Spaniard:
                        spaniardHouse = h;
                        break;
                    case Ukrainian:
                        ukrainianHouse = h;
                        break;
                    case Norwegian:
                        norwegianHouse = h;
                        break;
                    case Japanese:
                        japaneseHouse = h;
                        break;
                }
            }
            if (englishHouse != redHouse) continue;             // #2
            if (norwegianHouse != 0) continue;                  // #10
            if (std::abs(norwegianHouse - blueHouse) != 1) continue;  // #15

            std::sort(pets.begin(), pets.end());
            do {  // pets
                int dogHouse = -1, snailHouse = -1, foxHouse = -1,
                    horseHouse = -1, zebraHouse = -1;
                for (int h = 0; h < 5; ++h) {
                    switch (pets[h]) {
                        case Dog:
                            dogHouse = h;
                            break;
                        case Snail:
                            snailHouse = h;
                            break;
                        case Fox:
                            foxHouse = h;
                            break;
                        case Horse:
                            horseHouse = h;
                            break;
                        case Zebra:
                            zebraHouse = h;
                            break;
                    }
                }
                if (spaniardHouse != dogHouse) continue;  // #3

                std::sort(drinks.begin(), drinks.end());
                do {  // drinks
                    int coffeeHouse = -1, teaHouse = -1, milkHouse = -1,
                        ojHouse = -1, waterHouse = -1;
                    for (int h = 0; h < 5; ++h) {
                        switch (drinks[h]) {
                            case Coffee:
                                coffeeHouse = h;
                                break;
                            case Tea:
                                teaHouse = h;
                                break;
                            case Milk:
                                milkHouse = h;
                                break;
                            case OrangeJuice:
                                ojHouse = h;
                                break;
                            case Water:
                                waterHouse = h;
                                break;
                        }
                    }
                    if (coffeeHouse != greenHouse) continue;     // #4
                    if (ukrainianHouse != teaHouse) continue;    // #5
                    if (milkHouse != 2) continue;                // #9

                    std::sort(hobbies.begin(), hobbies.end());
                    do {  // hobbies
                        int readingHouse = -1, dancingHouse = -1,
                            paintingHouse = -1, footballHouse = -1,
                            chessHouse = -1;
                        for (int h = 0; h < 5; ++h) {
                            switch (hobbies[h]) {
                                case Reading:
                                    readingHouse = h;
                                    break;
                                case Dancing:
                                    dancingHouse = h;
                                    break;
                                case Painting:
                                    paintingHouse = h;
                                    break;
                                case Football:
                                    footballHouse = h;
                                    break;
                                case Chess:
                                    chessHouse = h;
                                    break;
                            }
                        }
                        if (snailHouse != dancingHouse) continue;           // #7
                        if (yellowHouse != paintingHouse) continue;         // #8
                        if (std::abs(readingHouse - foxHouse) != 1) continue;  // #11
                        if (std::abs(paintingHouse - horseHouse) != 1) continue;  // #12
                        if (footballHouse != ojHouse) continue;             // #13
                        if (japaneseHouse != chessHouse) continue;          // #14

                        // All constraints satisfied
                        Solution s;
                        s.drinksWater = nationality_names[nationalities[waterHouse]];
                        s.ownsZebra = nationality_names[nationalities[zebraHouse]];
                        return s;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(drinks.begin(), drinks.end()));
            } while (std::next_permutation(pets.begin(), pets.end()));
        } while (std::next_permutation(nationalities.begin(),
                                       nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // Puzzle guarantees a solution, but return empty if not found
    return {};
}

}  // namespace zebra_puzzle

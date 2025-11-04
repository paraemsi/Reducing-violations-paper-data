#include "zebra_puzzle.h"

namespace zebra_puzzle {

Solution solve() {
    enum Color { Red, Green, Ivory, Yellow, Blue };
    enum Nationality { Englishman, Spaniard, Ukrainian, Japanese, Norwegian };
    enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
    enum Pet { Dog, Snails, Fox, Horse, Zebra };
    enum Hobby { Dancing, Painting, Reading, Football, Chess };

    auto adjacent = [](int a, int b) { return a + 1 == b || b + 1 == a; };

    // Fixed facts:
    const int first_house = 0;
    const int middle_house = 2;
    const int blue_pos = 1;  // Must be next to Norwegian in the first house

    for (int ivory_pos = 0; ivory_pos <= 3; ++ivory_pos) {
        int green_pos = ivory_pos + 1;

        // Blue must be 1; ensure no color conflicts with blue
        if (ivory_pos == blue_pos || green_pos == blue_pos) continue;

        // Choose positions for red and yellow among remaining slots
        for (int red_pos = 0; red_pos < 5; ++red_pos) {
            if (red_pos == blue_pos || red_pos == ivory_pos || red_pos == green_pos) continue;

            for (int yellow_pos = 0; yellow_pos < 5; ++yellow_pos) {
                if (yellow_pos == blue_pos || yellow_pos == ivory_pos || yellow_pos == green_pos || yellow_pos == red_pos) continue;

                // Nationalities
                int posNat[5] = {-1, -1, -1, -1, -1};
                posNat[Norwegian] = first_house;
                // Englishman lives in the red house
                posNat[Englishman] = red_pos;
                if (posNat[Englishman] == posNat[Norwegian]) continue;  // distinct people

                // Remaining positions to assign: Spaniard, Ukrainian, Japanese
                int remPosNat[3];
                {
                    int idx = 0;
                    for (int p = 0; p < 5; ++p) {
                        if (p != posNat[Norwegian] && p != posNat[Englishman]) {
                            remPosNat[idx++] = p;
                        }
                    }
                }
                // Iterate all permutations of the remaining three nationalities
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (j == i) continue;
                        int k = 3 - i - j;
                        posNat[Spaniard] = remPosNat[i];
                        posNat[Ukrainian] = remPosNat[j];
                        posNat[Japanese] = remPosNat[k];

                        // Drinks
                        int posDrink[5] = {-1, -1, -1, -1, -1};
                        posDrink[Milk] = middle_house;          // middle house drinks milk
                        posDrink[Coffee] = green_pos;            // green house drinks coffee
                        posDrink[Tea] = posNat[Ukrainian];       // Ukrainian drinks tea

                        // Ensure uniqueness among set drinks
                        if (posDrink[Milk] == posDrink[Coffee] || posDrink[Milk] == posDrink[Tea] || posDrink[Coffee] == posDrink[Tea]) {
                            continue;
                        }

                        // Choose orange juice position among remaining; football will be here
                        for (int orange_pos = 0; orange_pos < 5; ++orange_pos) {
                            if (orange_pos == posDrink[Milk] || orange_pos == posDrink[Coffee] || orange_pos == posDrink[Tea]) continue;
                            posDrink[OrangeJuice] = orange_pos;

                            // Determine water position as the remaining drink position
                            int pos_used_drink[5] = {0, 0, 0, 0, 0};
                            pos_used_drink[posDrink[Milk]] = 1;
                            pos_used_drink[posDrink[Coffee]] = 1;
                            pos_used_drink[posDrink[Tea]] = 1;
                            pos_used_drink[posDrink[OrangeJuice]] = 1;
                            int water_pos = -1;
                            for (int p = 0; p < 5; ++p) {
                                if (!pos_used_drink[p]) {
                                    water_pos = p;
                                    break;
                                }
                            }
                            posDrink[Water] = water_pos;

                            // Hobbies
                            int posHobby[5] = {-1, -1, -1, -1, -1};
                            posHobby[Painting] = yellow_pos;                // yellow house is a painter
                            posHobby[Chess] = posNat[Japanese];             // Japanese plays chess
                            if (posHobby[Painting] == posHobby[Chess]) continue;

                            posHobby[Football] = posDrink[OrangeJuice];     // football drinks orange juice
                            if (posHobby[Football] == posHobby[Painting] || posHobby[Football] == posHobby[Chess]) continue;

                            // Remaining two hobbies: Dancing and Reading
                            int remPosHobby[2];
                            {
                                int idx = 0;
                                for (int p = 0; p < 5; ++p) {
                                    if (p != posHobby[Painting] && p != posHobby[Chess] && p != posHobby[Football]) {
                                        remPosHobby[idx++] = p;
                                    }
                                }
                                if (idx != 2) continue; // sanity
                            }
                            for (int t = 0; t < 2; ++t) {
                                int posDancing = remPosHobby[t];
                                int posReading = remPosHobby[1 - t];
                                posHobby[Dancing] = posDancing;
                                posHobby[Reading] = posReading;

                                // Pets
                                int posPet[5] = {-1, -1, -1, -1, -1};
                                posPet[Dog] = posNat[Spaniard];      // Spaniard owns the dog
                                posPet[Snails] = posHobby[Dancing];  // Snails owner likes dancing
                                if (posPet[Dog] == posPet[Snails]) continue;

                                // Remaining pets: Fox, Horse, Zebra
                                int remPosPet[3];
                                {
                                    int idx = 0;
                                    for (int p = 0; p < 5; ++p) {
                                        if (p != posPet[Dog] && p != posPet[Snails]) {
                                            remPosPet[idx++] = p;
                                        }
                                    }
                                }
                                for (int a = 0; a < 3; ++a) {
                                    for (int b = 0; b < 3; ++b) {
                                        if (b == a) continue;
                                        int c = 3 - a - b;
                                        int posFox = remPosPet[a];
                                        int posHorse = remPosPet[b];
                                        int posZebra = remPosPet[c];

                                        // Reading next to Fox
                                        if (!adjacent(posHobby[Reading], posFox)) continue;
                                        // Painter's house next to Horse
                                        if (!adjacent(posHobby[Painting], posHorse)) continue;

                                        // Green house drinks coffee is already enforced.
                                        // Norwegian next to blue is enforced by blue_pos=1 and Norwegian at 0.

                                        // At this point, all constraints satisfied; compute solution
                                        int natAtPos[5] = {-1, -1, -1, -1, -1};
                                        for (int n = 0; n < 5; ++n) {
                                            natAtPos[posNat[n]] = n;
                                        }

                                        Solution sol;
                                        static const char* natNames[5] = {
                                            "Englishman", "Spaniard", "Ukrainian", "Japanese", "Norwegian"
                                        };
                                        sol.drinksWater = natNames[natAtPos[posDrink[Water]]];
                                        sol.ownsZebra = natNames[natAtPos[posZebra]];
                                        return sol;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Should never reach here if the puzzle has a unique solution.
    return Solution{};
}

}  // namespace zebra_puzzle

#include "yacht.h"
#include <array>
#include <numeric>
#include <string>

namespace yacht {

static std::array<int, 7> count_faces(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    counts.fill(0);
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
    }
    return counts;
}

int score(const std::vector<int>& dice, const std::string& cat) {
    auto counts = count_faces(dice);
    int sum = std::accumulate(dice.begin(), dice.end(), 0);

    category catEnum;
    if      (cat == "ones")            catEnum = category::ones;
    else if (cat == "twos")            catEnum = category::twos;
    else if (cat == "threes")          catEnum = category::threes;
    else if (cat == "fours")           catEnum = category::fours;
    else if (cat == "fives")           catEnum = category::fives;
    else if (cat == "sixes")           catEnum = category::sixes;
    else if (cat == "full house")      catEnum = category::full_house;
    else if (cat == "four of a kind")  catEnum = category::four_of_a_kind;
    else if (cat == "little straight") catEnum = category::little_straight;
    else if (cat == "big straight")    catEnum = category::big_straight;
    else if (cat == "choice")          catEnum = category::choice;
    else if (cat == "yacht")           catEnum = category::yacht;
    else                               return 0;

    switch (catEnum) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;
        case category::full_house: {
            bool has3 = false, has2 = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has3 = true;
                else if (counts[face] == 2) has2 = true;
                else if (counts[face] == 5) {
                    // A Yacht is not a full house
                    return 0;
                }
            }
            return (has3 && has2) ? sum : 0;
        }
        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }
        case category::little_straight: {
            if (counts[1]==1 && counts[2]==1 && counts[3]==1 && counts[4]==1 && counts[5]==1 && counts[6]==0) {
                return 30;
            }
            return 0;
        }
        case category::big_straight: {
            if (counts[1]==0 && counts[2]==1 && counts[3]==1 && counts[4]==1 && counts[5]==1 && counts[6]==1) {
                return 30;
            }
            return 0;
        }
        case category::choice:
            return sum;
        case category::yacht:
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
        default:
            return 0;
    }
}

}  // namespace yacht

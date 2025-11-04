#include "yacht.h"
#include <array>
#include <numeric>
#include <string>
#include <stdexcept>

namespace yacht {

static std::array<int, 7> count_faces(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    counts.fill(0);
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d] += 1;
        }
    }
    return counts;
}

static category parse_category(const std::string& cat) {
    if (cat == "ones") return category::ones;
    if (cat == "twos") return category::twos;
    if (cat == "threes") return category::threes;
    if (cat == "fours") return category::fours;
    if (cat == "fives") return category::fives;
    if (cat == "sixes") return category::sixes;
    if (cat == "full house") return category::full_house;
    if (cat == "four of a kind") return category::four_of_a_kind;
    if (cat == "little straight") return category::little_straight;
    if (cat == "big straight") return category::big_straight;
    if (cat == "choice") return category::choice;
    if (cat == "yacht") return category::yacht;
    throw std::invalid_argument("Unknown category: " + cat);
}

int score(const std::vector<int>& dice, const std::string& cat) {
    return score(dice, parse_category(cat));
}

int score(const std::vector<int>& dice, const char* cat) {
    return score(dice, std::string(cat));
}

int score(const std::vector<int>& dice, category cat) {
    auto counts = count_faces(dice);
    int sum = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return 1 * counts[1];
        case category::twos:   return 2 * counts[2];
        case category::threes: return 3 * counts[3];
        case category::fours:  return 4 * counts[4];
        case category::fives:  return 5 * counts[5];
        case category::sixes:  return 6 * counts[6];
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int p = 1; p <= 6; ++p) {
                if (counts[p] == 3) has_three = true;
                else if (counts[p] == 2) has_two = true;
                else if (counts[p] == 5) {
                    return 0; // Yacht is not a full house
                }
            }
            return (has_three && has_two) ? sum : 0;
        }
        case category::four_of_a_kind: {
            for (int p = 1; p <= 6; ++p) {
                if (counts[p] >= 4) return 4 * p;
            }
            return 0;
        }
        case category::little_straight: {
            for (int p = 1; p <= 5; ++p) {
                if (counts[p] != 1) return 0;
            }
            return counts[6] == 0 ? 30 : 0;
        }
        case category::big_straight: {
            for (int p = 2; p <= 6; ++p) {
                if (counts[p] != 1) return 0;
            }
            return counts[1] == 0 ? 30 : 0;
        }
        case category::choice:
            return sum;
        case category::yacht: {
            for (int p = 1; p <= 6; ++p) {
                if (counts[p] == 5) return 50;
            }
            return 0;
        }
    }
    return 0;
}

}  // namespace yacht

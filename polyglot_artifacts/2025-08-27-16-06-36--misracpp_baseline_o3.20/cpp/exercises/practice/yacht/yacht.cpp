#include "yacht.h"

#include <array>
#include <numeric>
#include <string>
#include <stdexcept>

namespace yacht {

namespace {
constexpr int NUM_FACES{6};

/**
 * Build a frequency table for the dice.
 */
std::array<int, NUM_FACES + 1> make_histogram(const std::vector<int>& dice)
{
    std::array<int, NUM_FACES + 1> counts{};
    for (int die : dice) {
        if (die >= 1 && die <= NUM_FACES) {
            ++counts[die];
        }
    }
    return counts;
}
} // namespace

static int score_impl(const std::vector<int>& dice, category cat)
{
    auto counts = make_histogram(dice);
    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
    case category::ones:
    case category::twos:
    case category::threes:
    case category::fours:
    case category::fives:
    case category::sixes: {
        int face = static_cast<int>(cat) + 1; // enum order: ones == 0
        return counts[face] * face;
    }

    case category::full_house: {
        bool has_three{false}, has_two{false};
        for (int face = 1; face <= NUM_FACES; ++face) {
            if (counts[face] == 3)
                has_three = true;
            else if (counts[face] == 2)
                has_two = true;
        }
        return (has_three && has_two) ? total : 0;
    }

    case category::four_of_a_kind: {
        for (int face = 1; face <= NUM_FACES; ++face) {
            if (counts[face] >= 4)
                return face * 4;
        }
        return 0;
    }

    case category::little_straight:
        return (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1)
                   ? 30
                   : 0;

    case category::big_straight:
        return (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 &&
                counts[5] == 1 && counts[6] == 1)
                   ? 30
                   : 0;

    case category::choice:
        return total;

    case category::yacht:
        for (int face = 1; face <= NUM_FACES; ++face) {
            if (counts[face] == 5)
                return 50;
        }
        return 0;
    }

    return 0; // should never reach here
}

int score(const std::vector<int>& dice, const std::string& category_name)
{
    category cat;
    if (category_name == "ones")
        cat = category::ones;
    else if (category_name == "twos")
        cat = category::twos;
    else if (category_name == "threes")
        cat = category::threes;
    else if (category_name == "fours")
        cat = category::fours;
    else if (category_name == "fives")
        cat = category::fives;
    else if (category_name == "sixes")
        cat = category::sixes;
    else if (category_name == "full house")
        cat = category::full_house;
    else if (category_name == "four of a kind")
        cat = category::four_of_a_kind;
    else if (category_name == "little straight")
        cat = category::little_straight;
    else if (category_name == "big straight")
        cat = category::big_straight;
    else if (category_name == "choice")
        cat = category::choice;
    else if (category_name == "yacht")
        cat = category::yacht;
    else
        throw std::invalid_argument("Unknown category name");
    return score_impl(dice, cat);
}

}  // namespace yacht

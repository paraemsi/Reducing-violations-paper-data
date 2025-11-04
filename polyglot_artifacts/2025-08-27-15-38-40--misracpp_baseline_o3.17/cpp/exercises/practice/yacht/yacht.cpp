#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace yacht {

// helper: build frequency table
static std::unordered_map<int, int> counts(const std::vector<int>& dice) {
    std::unordered_map<int, int> freq;
    for (int d : dice) {
        ++freq[d];
    }
    return freq;
}

static category parse_category(const std::string& name) {
    static const std::unordered_map<std::string, category> mapping{
        {"ones", category::ones},
        {"twos", category::twos},
        {"threes", category::threes},
        {"fours", category::fours},
        {"fives", category::fives},
        {"sixes", category::sixes},
        {"full house", category::full_house},
        {"four of a kind", category::four_of_a_kind},
        {"little straight", category::little_straight},
        {"big straight", category::big_straight},
        {"choice", category::choice},
        {"yacht", category::yacht}
    };
    auto it = mapping.find(name);
    if (it == mapping.end()) {
        throw std::invalid_argument("unknown category");
    }
    return it->second;
}

int score(const std::vector<int>& dice, const std::string& cat_str) {
    const category cat = parse_category(cat_str);
    const auto freq = counts(dice);

    switch (cat) {
        // ones-sixes
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            int face = static_cast<int>(cat) + 1;  // enum order places ones at 0
            auto it = freq.find(face);
            int count = (it != freq.end()) ? it->second : 0;
            return face * count;
        }

        case category::full_house: {
            if (freq.size() == 2) {
                // there must be counts 3 and 2
                bool has_three = false;
                bool has_two   = false;
                for (const auto& p : freq) {
                    if (p.second == 3) {
                        has_three = true;
                    } else if (p.second == 2) {
                        has_two = true;
                    } else {
                        return 0;  // some other count present
                    }
                }
                if (has_three && has_two) {
                    return std::accumulate(dice.begin(), dice.end(), 0);
                }
            }
            return 0;
        }

        case category::four_of_a_kind: {
            for (const auto& p : freq) {
                if (p.second >= 4) {
                    return p.first * 4;
                }
            }
            return 0;
        }

        case category::little_straight: {
            std::vector<int> sorted = dice;
            std::sort(sorted.begin(), sorted.end());
            return (sorted == std::vector<int>{1, 2, 3, 4, 5}) ? 30 : 0;
        }

        case category::big_straight: {
            std::vector<int> sorted = dice;
            std::sort(sorted.begin(), sorted.end());
            return (sorted == std::vector<int>{2, 3, 4, 5, 6}) ? 30 : 0;
        }

        case category::choice:
            return std::accumulate(dice.begin(), dice.end(), 0);

        case category::yacht: {
            return (freq.size() == 1) ? 50 : 0;
        }
    }
    return 0;  // unreachable, but silences compiler warnings
}

}  // namespace yacht

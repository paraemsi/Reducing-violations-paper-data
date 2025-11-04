#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

namespace {
    // Helper: count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6> count_faces(const DiceArray& dice) {
        std::array<std::uint8_t, 6> counts = {0, 0, 0, 0, 0, 0};
        for(const DieValue value : dice) {
            if((value >= 1U) && (value <= 6U)) {
                ++counts[static_cast<std::size_t>(value) - 1U];
            }
        }
        return counts;
    }
}

std::uint32_t score(const DiceArray& dice, const char* category) {
    // Map string to enum
    struct CategoryMapEntry {
        const char* name;
        Category cat;
    };
    static const CategoryMapEntry category_map[] = {
        {"ones", Category::Ones},
        {"twos", Category::Twos},
        {"threes", Category::Threes},
        {"fours", Category::Fours},
        {"fives", Category::Fives},
        {"sixes", Category::Sixes},
        {"full house", Category::FullHouse},
        {"four of a kind", Category::FourOfAKind},
        {"little straight", Category::LittleStraight},
        {"big straight", Category::BigStraight},
        {"choice", Category::Choice},
        {"yacht", Category::Yacht}
    };

    Category cat = Category::Ones; // default
    bool found = false;
    for(const auto& entry : category_map) {
        // Compare as lowercase, since test strings are lowercase
        const char* a = entry.name;
        const char* b = category;
        while((*a != '\0') && (*b != '\0') && (*a == *b)) {
            ++a;
            ++b;
        }
        if((*a == '\0') && (*b == '\0')) {
            cat = entry.cat;
            found = true;
            break;
        }
    }
    if(!found) {
        // Unknown category string, return 0
        return 0U;
    }

    const std::array<std::uint8_t, 6> counts = count_faces(dice);
    std::uint32_t result = 0U;

    switch(cat) {
        case Category::Ones:
            result = static_cast<std::uint32_t>(counts[0]) * 1U;
            break;
        case Category::Twos:
            result = static_cast<std::uint32_t>(counts[1]) * 2U;
            break;
        case Category::Threes:
            result = static_cast<std::uint32_t>(counts[2]) * 3U;
            break;
        case Category::Fours:
            result = static_cast<std::uint32_t>(counts[3]) * 4U;
            break;
        case Category::Fives:
            result = static_cast<std::uint32_t>(counts[4]) * 5U;
            break;
        case Category::Sixes:
            result = static_cast<std::uint32_t>(counts[5]) * 6U;
            break;
        case Category::FullHouse: {
            bool has_three = false;
            bool has_two = false;
            std::uint32_t sum = 0U;
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 3U) {
                    has_three = true;
                }
                if(counts[i] == 2U) {
                    has_two = true;
                }
                sum = sum + (static_cast<std::uint32_t>(counts[i]) * (i + 1U));
            }
            if(has_three && has_two) {
                result = sum;
            }
            break;
        }
        case Category::FourOfAKind: {
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] >= 4U) {
                    result = (i + 1U) * 4U;
                    break;
                }
            }
            break;
        }
        case Category::LittleStraight:
            if((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U)) {
                result = 30U;
            }
            break;
        case Category::BigStraight:
            if((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U)) {
                result = 30U;
            }
            break;
        case Category::Choice: {
            std::uint32_t sum = 0U;
            for(std::size_t i = 0U; i < 5U; ++i) {
                sum = sum + static_cast<std::uint32_t>(dice[i]);
            }
            result = sum;
            break;
        }
        case Category::Yacht:
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 5U) {
                    result = 50U;
                }
            }
            break;
        default:
            // result = 0U;
            break;
    }
    return result;
}

}  // namespace yacht

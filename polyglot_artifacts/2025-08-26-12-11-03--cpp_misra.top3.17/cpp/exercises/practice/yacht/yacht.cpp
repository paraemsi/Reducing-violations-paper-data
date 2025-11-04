#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <map>

namespace yacht {

namespace {
    // Helper: count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6U> count_faces(const Dice& dice)
    {
        std::array<std::uint8_t, 6U> counts = {0U, 0U, 0U, 0U, 0U, 0U};
        for(const Die d : dice) {
            if((d >= 1U) && (d <= 6U)) {
                ++(counts[d - 1U]);
            }
        }
        return counts;
    }
}

std::uint32_t score(const Dice& dice, const char* category)
{
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
        // Use std::strcmp for C string comparison
        if(std::strcmp(category, entry.name) == 0) {
            cat = entry.cat;
            found = true;
            break;
        }
    }
    if(!found) {
        return 0U;
    }

    const std::array<std::uint8_t, 6U> counts = count_faces(dice);

    switch(cat) {
        case Category::Ones:
            return (static_cast<std::uint32_t>(counts[0U]) * 1U);
        case Category::Twos:
            return (static_cast<std::uint32_t>(counts[1U]) * 2U);
        case Category::Threes:
            return (static_cast<std::uint32_t>(counts[2U]) * 3U);
        case Category::Fours:
            return (static_cast<std::uint32_t>(counts[3U]) * 4U);
        case Category::Fives:
            return (static_cast<std::uint32_t>(counts[4U]) * 5U);
        case Category::Sixes:
            return (static_cast<std::uint32_t>(counts[5U]) * 6U);
        case Category::FullHouse: {
            bool has_three = false;
            bool has_two = false;
            for(std::uint8_t c : counts) {
                if(c == 3U) {
                    has_three = true;
                } else if(c == 2U) {
                    has_two = true;
                }
            }
            if(has_three && has_two) {
                std::uint32_t sum = 0U;
                for(const Die d : dice) {
                    sum += static_cast<std::uint32_t>(d);
                }
                return sum;
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for(std::size_t i = 0U; i < counts.size(); ++i) {
                if(counts[i] >= 4U) {
                    return (static_cast<std::uint32_t>(i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
            // 1-2-3-4-5: counts[0..4] == 1, counts[5] == 0
            if((counts[0U] == 1U) && (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 0U)) {
                return 30U;
            }
            return 0U;
        case Category::BigStraight:
            // 2-3-4-5-6: counts[0] == 0, counts[1..5] == 1
            if((counts[0U] == 0U) && (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U)) {
                return 30U;
            }
            return 0U;
        case Category::Choice: {
            std::uint32_t sum = 0U;
            for(const Die d : dice) {
                sum += static_cast<std::uint32_t>(d);
            }
            return sum;
        }
        case Category::Yacht:
            for(std::uint8_t c : counts) {
                if(c == 5U) {
                    return 50U;
                }
            }
            return 0U;
        default:
            return 0U;
    }
}

}  // namespace yacht

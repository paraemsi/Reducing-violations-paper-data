#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, const std::string& cat) -> std::uint32_t
{
    std::array<std::uint32_t, 7U> counts{};
    counts.fill(0U);

    for (std::uint8_t v : dice) {
        std::size_t idx = static_cast<std::size_t>(v);
        if ((idx >= 1U) && (idx <= 6U)) {
            counts[idx] = (counts[idx] + 1U);
        } else {
            // Invalid die value (outside 1..6). Spec guarantees valid input; ignore gracefully.
        }
    }

    std::uint32_t sum = 0U;
    for (std::uint8_t v : dice) {
        sum = (sum + static_cast<std::uint32_t>(v));
    }

    std::uint32_t result = 0U;

    // Map category name to enum
    category cat_enum = category::choice;
    bool recognized = false;
    if ((cat == "ones")) {
        cat_enum = category::ones;
        recognized = true;
    } else if ((cat == "twos")) {
        cat_enum = category::twos;
        recognized = true;
    } else if ((cat == "threes")) {
        cat_enum = category::threes;
        recognized = true;
    } else if ((cat == "fours")) {
        cat_enum = category::fours;
        recognized = true;
    } else if ((cat == "fives")) {
        cat_enum = category::fives;
        recognized = true;
    } else if ((cat == "sixes")) {
        cat_enum = category::sixes;
        recognized = true;
    } else if ((cat == "full house")) {
        cat_enum = category::full_house;
        recognized = true;
    } else if ((cat == "four of a kind")) {
        cat_enum = category::four_of_a_kind;
        recognized = true;
    } else if ((cat == "little straight")) {
        cat_enum = category::little_straight;
        recognized = true;
    } else if ((cat == "big straight")) {
        cat_enum = category::big_straight;
        recognized = true;
    } else if ((cat == "choice")) {
        cat_enum = category::choice;
        recognized = true;
    } else if ((cat == "yacht")) {
        cat_enum = category::yacht;
        recognized = true;
    } else {
        recognized = false;
    }

    if (!recognized) {
        return 0U;
    }

    switch (cat_enum) {
        case category::ones: {
            result = (1U * counts[1U]);
            break;
        }
        case category::twos: {
            result = (2U * counts[2U]);
            break;
        }
        case category::threes: {
            result = (3U * counts[3U]);
            break;
        }
        case category::fours: {
            result = (4U * counts[4U]);
            break;
        }
        case category::fives: {
            result = (5U * counts[5U]);
            break;
        }
        case category::sixes: {
            result = (6U * counts[6U]);
            break;
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint32_t face = 1U; face <= 6U; ++face) {
                std::size_t idx = static_cast<std::size_t>(face);
                if (counts[idx] == 3U) {
                    has_three = true;
                } else {
                    if (counts[idx] == 2U) {
                        has_two = true;
                    }
                }
            }
            if (has_three && has_two) {
                result = sum;
            } else {
                result = 0U;
            }
            break;
        }
        case category::four_of_a_kind: {
            for (std::uint32_t face = 1U; face <= 6U; ++face) {
                std::size_t idx = static_cast<std::size_t>(face);
                if (counts[idx] >= 4U) {
                    result = (4U * face);
                    break;
                }
            }
            break;
        }
        case category::little_straight: {
            bool ok = ((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U));
            if (ok) {
                result = 30U;
            } else {
                result = 0U;
            }
            break;
        }
        case category::big_straight: {
            bool ok = ((counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U));
            if (ok) {
                result = 30U;
            } else {
                result = 0U;
            }
            break;
        }
        case category::choice: {
            result = sum;
            break;
        }
        case category::yacht: {
            for (std::uint32_t face = 1U; face <= 6U; ++face) {
                std::size_t idx = static_cast<std::size_t>(face);
                if (counts[idx] == 5U) {
                    result = 50U;
                    break;
                }
            }
            break;
        }
        default: {
            result = 0U;
            break;
        }
    }

    return result;
}

}  // namespace yacht

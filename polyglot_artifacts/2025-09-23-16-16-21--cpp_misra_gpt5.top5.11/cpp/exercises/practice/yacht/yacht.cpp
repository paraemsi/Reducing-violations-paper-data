#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>

namespace yacht {
namespace detail {

static constexpr std::uint32_t straight_score = 30U;
static constexpr std::uint32_t yacht_score = 50U;

std::uint32_t compute_score_from_counts(
    const std::array<std::uint32_t, 7U>& counts,
    category cat,
    std::uint32_t total) noexcept
{
    switch (cat) {
        case category::ones: {
            return (counts[static_cast<std::size_t>(1U)] * 1U);
        }
        case category::twos: {
            return (counts[static_cast<std::size_t>(2U)] * 2U);
        }
        case category::threes: {
            return (counts[static_cast<std::size_t>(3U)] * 3U);
        }
        case category::fours: {
            return (counts[static_cast<std::size_t>(4U)] * 4U);
        }
        case category::fives: {
            return (counts[static_cast<std::size_t>(5U)] * 5U);
        }
        case category::sixes: {
            return (counts[static_cast<std::size_t>(6U)] * 6U);
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;

            for (std::uint32_t face = 1U; face <= 6U; face = face + 1U) {
                const std::uint32_t c =
                    counts[static_cast<std::size_t>(face)];
                if (c == 3U) {
                    has_three = true;
                } else if (c == 2U) {
                    has_two = true;
                }
            }

            if ((has_three == true) && (has_two == true)) {
                return total;
            } else {
                return 0U;
            }
        }
        case category::four_of_a_kind: {
            for (std::uint32_t face = 1U; face <= 6U; face = face + 1U) {
                const std::uint32_t c =
                    counts[static_cast<std::size_t>(face)];
                if (c >= 4U) {
                    return (4U * face);
                }
            }
            return 0U;
        }
        case category::little_straight: {
            const bool is_little =
                (counts[static_cast<std::size_t>(1U)] == 1U) &&
                (counts[static_cast<std::size_t>(2U)] == 1U) &&
                (counts[static_cast<std::size_t>(3U)] == 1U) &&
                (counts[static_cast<std::size_t>(4U)] == 1U) &&
                (counts[static_cast<std::size_t>(5U)] == 1U) &&
                (counts[static_cast<std::size_t>(6U)] == 0U);

            if (is_little == true) {
                return straight_score;
            } else {
                return 0U;
            }
        }
        case category::big_straight: {
            const bool is_big =
                (counts[static_cast<std::size_t>(1U)] == 0U) &&
                (counts[static_cast<std::size_t>(2U)] == 1U) &&
                (counts[static_cast<std::size_t>(3U)] == 1U) &&
                (counts[static_cast<std::size_t>(4U)] == 1U) &&
                (counts[static_cast<std::size_t>(5U)] == 1U) &&
                (counts[static_cast<std::size_t>(6U)] == 1U);

            if (is_big == true) {
                return straight_score;
            } else {
                return 0U;
            }
        }
        case category::choice: {
            return total;
        }
        case category::yacht: {
            for (std::uint32_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[static_cast<std::size_t>(face)] == 5U) {
                    return yacht_score;
                }
            }
            return 0U;
        }
        default: {
            return 0U;
        }
    }
}

}  // namespace detail
}  // namespace yacht

#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace yacht {

namespace {
constexpr std::int32_t kScoreYacht = static_cast<std::int32_t>(50);
constexpr std::int32_t kStraightScore = static_cast<std::int32_t>(30);
constexpr std::int32_t kFaceMin = static_cast<std::int32_t>(1);
constexpr std::int32_t kFaceMax = static_cast<std::int32_t>(6);
constexpr std::int32_t kDiceCount = static_cast<std::int32_t>(5);

using Counts = std::array<std::int32_t, 7>;

auto make_counts(const std::array<std::int32_t, 5>& dice) -> Counts {
    Counts counts{};
    // counts[0] unused
    for (const std::int32_t d : dice) {
        if ((d >= kFaceMin) && (d <= kFaceMax)) {
            counts[static_cast<std::size_t>(d)] += static_cast<std::int32_t>(1);
        } else {
            // Out-of-range die ignored per input contract.
        }
    }
    return counts;
}

auto sum_dice(const std::array<std::int32_t, 5>& dice) -> std::int32_t {
    std::int32_t total = static_cast<std::int32_t>(0);
    for (const std::int32_t d : dice) {
        total = (total + d);
    }
    return total;
}
}  // namespace

auto score(const std::array<std::int32_t, 5>& dice, category cat) noexcept -> std::int32_t {
    const Counts counts = make_counts(dice);
    switch (cat) {
        case category::ones: {
            return (static_cast<std::int32_t>(1) * counts[static_cast<std::size_t>(1)]);
        }
        case category::twos: {
            return (static_cast<std::int32_t>(2) * counts[static_cast<std::size_t>(2)]);
        }
        case category::threes: {
            return (static_cast<std::int32_t>(3) * counts[static_cast<std::size_t>(3)]);
        }
        case category::fours: {
            return (static_cast<std::int32_t>(4) * counts[static_cast<std::size_t>(4)]);
        }
        case category::fives: {
            return (static_cast<std::int32_t>(5) * counts[static_cast<std::size_t>(5)]);
        }
        case category::sixes: {
            return (static_cast<std::int32_t>(6) * counts[static_cast<std::size_t>(6)]);
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::int32_t face = kFaceMin; face <= kFaceMax; face = (face + static_cast<std::int32_t>(1))) {
                const std::int32_t c = counts[static_cast<std::size_t>(face)];
                if (c == static_cast<std::int32_t>(3)) {
                    has_three = true;
                } else if (c == static_cast<std::int32_t>(2)) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return sum_dice(dice);
            } else {
                return static_cast<std::int32_t>(0);
            }
        }
        case category::four_of_a_kind: {
            for (std::int32_t face = kFaceMin; face <= kFaceMax; face = (face + static_cast<std::int32_t>(1))) {
                if (counts[static_cast<std::size_t>(face)] >= static_cast<std::int32_t>(4)) {
                    return (static_cast<std::int32_t>(4) * face);
                }
            }
            return static_cast<std::int32_t>(0);
        }
        case category::little_straight: {
            bool ok = true;
            for (std::int32_t face = kFaceMin; face <= (kFaceMax - static_cast<std::int32_t>(1)); face = (face + static_cast<std::int32_t>(1))) {
                if (counts[static_cast<std::size_t>(face)] != static_cast<std::int32_t>(1)) {
                    ok = false;
                }
            }
            if (counts[static_cast<std::size_t>(6)] != static_cast<std::int32_t>(0)) {
                ok = false;
            }
            if (ok) {
                return kStraightScore;
            } else {
                return static_cast<std::int32_t>(0);
            }
        }
        case category::big_straight: {
            bool ok = true;
            if (counts[static_cast<std::size_t>(1)] != static_cast<std::int32_t>(0)) {
                ok = false;
            }
            for (std::int32_t face = static_cast<std::int32_t>(2); face <= kFaceMax; face = (face + static_cast<std::int32_t>(1))) {
                if (counts[static_cast<std::size_t>(face)] != static_cast<std::int32_t>(1)) {
                    ok = false;
                }
            }
            if (ok) {
                return kStraightScore;
            } else {
                return static_cast<std::int32_t>(0);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::int32_t face = kFaceMin; face <= kFaceMax; face = (face + static_cast<std::int32_t>(1))) {
                if (counts[static_cast<std::size_t>(face)] == kDiceCount) {
                    return kScoreYacht;
                }
            }
            return static_cast<std::int32_t>(0);
        }
        default: {
            return static_cast<std::int32_t>(0);
        }
    }
}

auto score(const std::array<std::int32_t, 5>& dice, const char* cat) noexcept -> std::int32_t {
    if ((cat == nullptr)) {
        return static_cast<std::int32_t>(0);
    }

    category mapped = category::choice;
    if ((std::strcmp(cat, "ones") == 0)) {
        mapped = category::ones;
    } else if ((std::strcmp(cat, "twos") == 0)) {
        mapped = category::twos;
    } else if ((std::strcmp(cat, "threes") == 0)) {
        mapped = category::threes;
    } else if ((std::strcmp(cat, "fours") == 0)) {
        mapped = category::fours;
    } else if ((std::strcmp(cat, "fives") == 0)) {
        mapped = category::fives;
    } else if ((std::strcmp(cat, "sixes") == 0)) {
        mapped = category::sixes;
    } else if ((std::strcmp(cat, "full house") == 0)) {
        mapped = category::full_house;
    } else if ((std::strcmp(cat, "four of a kind") == 0)) {
        mapped = category::four_of_a_kind;
    } else if ((std::strcmp(cat, "little straight") == 0)) {
        mapped = category::little_straight;
    } else if ((std::strcmp(cat, "big straight") == 0)) {
        mapped = category::big_straight;
    } else if ((std::strcmp(cat, "choice") == 0)) {
        mapped = category::choice;
    } else if ((std::strcmp(cat, "yacht") == 0)) {
        mapped = category::yacht;
    } else {
        return static_cast<std::int32_t>(0);
    }
    return score(dice, mapped);
}

}  // namespace yacht

#include "allergies.h"
#include <array>

namespace allergies {

std::size_t allergen_hash::operator()(allergen a) const noexcept {
    switch (a) {
        case allergen::eggs:
            return static_cast<std::size_t>(0);
        case allergen::peanuts:
            return static_cast<std::size_t>(1);
        case allergen::shellfish:
            return static_cast<std::size_t>(2);
        case allergen::strawberries:
            return static_cast<std::size_t>(3);
        case allergen::tomatoes:
            return static_cast<std::size_t>(4);
        case allergen::chocolate:
            return static_cast<std::size_t>(5);
        case allergen::pollen:
            return static_cast<std::size_t>(6);
        case allergen::cats:
            return static_cast<std::size_t>(7);
        default:
            return static_cast<std::size_t>(0);
    }
}

namespace {
constexpr std::uint32_t known_mask =
    ((static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(8)) - static_cast<std::uint32_t>(1));

constexpr std::uint32_t mask_for(allergen a) noexcept {
    switch (a) {
        case allergen::eggs:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(0));
        case allergen::peanuts:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(1));
        case allergen::shellfish:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(2));
        case allergen::strawberries:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(3));
        case allergen::tomatoes:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(4));
        case allergen::chocolate:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(5));
        case allergen::pollen:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(6));
        case allergen::cats:
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(7));
        default:
            return static_cast<std::uint32_t>(0);
    }
}

constexpr std::array<allergen, 8U> all_items = {
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
};

}  // namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score} {
}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    const std::uint32_t masked_score = (score_ & known_mask);
    const std::uint32_t m = mask_for(item);
    return ((masked_score & m) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen, allergen_hash> allergy_test::get_allergies() const {
    std::unordered_set<allergen, allergen_hash> result{};
    const std::uint32_t masked_score = (score_ & known_mask);

    for (const auto a : all_items) {
        const std::uint32_t m = mask_for(a);
        if ((masked_score & m) != static_cast<std::uint32_t>(0)) {
            result.emplace(a);
        } else {
            // no-op
        }
    }

    return result;
}

}  // namespace allergies

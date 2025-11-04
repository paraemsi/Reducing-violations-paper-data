#include "allergies.h"

#include <array>
#include <cstdint>
#include <unordered_set>

namespace allergies {

namespace {
constexpr std::uint32_t mask_for(allergen a) noexcept
{
    switch (a) {
        case allergen::eggs:
            return (static_cast<std::uint32_t>(1) << 0);
        case allergen::peanuts:
            return (static_cast<std::uint32_t>(1) << 1);
        case allergen::shellfish:
            return (static_cast<std::uint32_t>(1) << 2);
        case allergen::strawberries:
            return (static_cast<std::uint32_t>(1) << 3);
        case allergen::tomatoes:
            return (static_cast<std::uint32_t>(1) << 4);
        case allergen::chocolate:
            return (static_cast<std::uint32_t>(1) << 5);
        case allergen::pollen:
            return (static_cast<std::uint32_t>(1) << 6);
        case allergen::cats:
            return (static_cast<std::uint32_t>(1) << 7);
        default:
            return static_cast<std::uint32_t>(0);
    }
}
} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score}
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    const std::uint32_t mask = mask_for(item);
    return (((score_ & mask) != static_cast<std::uint32_t>(0)));
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
    std::unordered_set<allergen> result{};
    const std::array<allergen, 8U> items = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const auto a : items) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies

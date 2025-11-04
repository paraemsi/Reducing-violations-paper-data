#include "allergies.h"
#include <array>

namespace allergies {

namespace {
    constexpr std::array<allergen, 8U> all_allergens = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };
}

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_(score)
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    const std::uint16_t mask16 = static_cast<std::uint16_t>(item);
    const std::uint32_t mask = static_cast<std::uint32_t>(mask16);
    const std::uint32_t masked = (score_ & mask);
    return (masked != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
    std::unordered_set<allergen> result{};
    for (const auto a : all_allergens) {
        if (is_allergic_to(a)) {
            (void)result.emplace(a);
        } else {
            // no action required
        }
    }
    return result;
}

}  // namespace allergies

#include "allergies.h"

#include <array>
#include <cstddef>

namespace allergies {

namespace {
// Array containing all recognised allergens.
constexpr std::array<allergen, 8U> all_allergens{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};
} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score{score} {}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    const std::uint32_t item_value{static_cast<std::uint32_t>(item)};
    return ( (m_score & item_value) != 0U );
}

std::unordered_set<allergen> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<allergen> result{};
    for(const allergen a : all_allergens) {
        if (is_allergic_to(a)) {
            (void)result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies


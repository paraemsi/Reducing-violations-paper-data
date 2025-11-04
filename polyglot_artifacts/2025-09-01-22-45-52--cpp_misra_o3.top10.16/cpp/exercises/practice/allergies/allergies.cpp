#include "allergies.h"

#include <array>
#include <unordered_set>
#include <cstdint>
#include <functional>

namespace allergies {

namespace
{
    constexpr std::array<allergen, 8U> k_all_allergens{{
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
    : m_score{score}
{
}

bool allergy_test::is_allergic_to(const allergen item) const noexcept
{
    return ((m_score & static_cast<std::uint32_t>(item)) != 0U);
}

std::unordered_set<allergen, allergen_hash> allergy_test::get_allergies() const
{
    std::unordered_set<allergen, allergen_hash> result{};
    for (const allergen item : k_all_allergens)
    {
        if (is_allergic_to(item))
        {
            (void)result.emplace(item);
        }
    }
    return result;
}

} // namespace allergies

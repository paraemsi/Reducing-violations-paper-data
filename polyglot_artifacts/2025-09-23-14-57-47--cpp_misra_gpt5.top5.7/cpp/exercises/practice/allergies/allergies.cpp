#include "allergies.h"
#include <array>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) { }

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    return ((static_cast<std::uint32_t>(m_score) & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0U));
}

allergen_set allergy_test::get_allergies() const noexcept
{
    allergen_set result{};

    const std::array<allergen, static_cast<std::size_t>(8U)> items = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const auto& item : items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies

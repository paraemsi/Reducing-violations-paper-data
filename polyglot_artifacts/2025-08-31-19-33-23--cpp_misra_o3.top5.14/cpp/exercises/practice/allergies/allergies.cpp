#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score)
{
    /* Constructor body intentionally left empty */
}

auto allergy_test::is_allergic_to(allergen item) const noexcept -> bool
{
    const std::uint32_t item_value = static_cast<std::uint32_t>(item);
    return ((m_score & item_value) != static_cast<std::uint32_t>(0U));
}

auto allergy_test::get_allergies() const -> std::unordered_set<allergen, allergen_hash>
{
    std::unordered_set<allergen, allergen_hash> result {};
    constexpr std::array<allergen, 8U> all_items {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const allergen item : all_items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies

#include "allergies.h"

namespace allergies {

/* List of all recognised allergens – keeps ordering deterministic. */
static constexpr std::array<allergen, 8U> ALL_ALLERGENS{
    allergen::eggs,       allergen::peanuts,  allergen::shellfish,
    allergen::strawberries, allergen::tomatoes, allergen::chocolate,
    allergen::pollen,     allergen::cats};

/* Constructor */
allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) {}

/* Check if a particular allergen bit is set. */
bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    /* Parenthesise bitwise & before comparison to satisfy MISRA rule */
    return ((static_cast<std::uint32_t>(item) & m_score) != 0U);
}

/* Return a set containing all allergens present in the score. */
std::unordered_set<allergen> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<allergen> result{};
    for (allergen item : ALL_ALLERGENS) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies

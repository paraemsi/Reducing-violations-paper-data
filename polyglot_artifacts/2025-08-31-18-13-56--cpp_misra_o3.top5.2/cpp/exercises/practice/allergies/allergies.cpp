#include "allergies.h"
#include <array>

namespace allergies {

allergy_test::allergy_test(score_type score_in) : m_score{score_in}
{
}

bool allergy_test::is_allergic_to(allergen item) const
{
    return ((m_score & static_cast<score_type>(item)) != 0u);
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
    std::unordered_set<allergen> result{};

    const std::array<allergen, 8u> all_items{
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats};

    for (allergen item : all_items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies

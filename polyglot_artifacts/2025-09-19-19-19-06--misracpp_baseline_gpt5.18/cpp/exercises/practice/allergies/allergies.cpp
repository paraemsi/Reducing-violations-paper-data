#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(int score) : m_score{score} {}

bool allergy_test::is_allergic_to(allergen a) const {
    const int masked = m_score & 0xFF; // Ignore scores for unknown allergens
    return (masked & static_cast<int>(a)) != 0;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;

    constexpr allergen known[] = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (auto a : known) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies

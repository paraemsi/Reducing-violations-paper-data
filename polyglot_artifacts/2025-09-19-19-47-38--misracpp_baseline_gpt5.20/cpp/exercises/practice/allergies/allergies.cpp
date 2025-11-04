#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(unsigned int score) noexcept
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen a) const noexcept {
    return (score_ & static_cast<unsigned int>(a)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;

    const allergen all[] = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const auto a : all) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies

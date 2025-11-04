#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{ score } { }

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    return ((score_ & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result{};

    const allergen all_items[] = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const allergen a : all_items) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        } else {
            // no-op
        }
    }

    return result;
}

}  // namespace allergies

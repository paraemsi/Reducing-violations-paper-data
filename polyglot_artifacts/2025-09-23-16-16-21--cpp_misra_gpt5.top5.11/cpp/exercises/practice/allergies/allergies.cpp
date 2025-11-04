#include "allergies.h"

#include <array>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) {
}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    const std::uint32_t mask = static_cast<std::uint32_t>(item);
    return ((m_score & mask) != static_cast<std::uint32_t>(0U));
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result{};

    static constexpr std::array<allergen, 8U> all_items = {
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
            (void)result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies

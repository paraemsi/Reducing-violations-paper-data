#include "allergies.h"

#include <array>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) {}

bool allergy_test::is_allergic_to(allergy item) const noexcept {
    return ((m_score & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergy> allergy_test::get_allergies() const {
    static constexpr std::array<allergy, 8U> items{
        allergy::eggs,
        allergy::peanuts,
        allergy::shellfish,
        allergy::strawberries,
        allergy::tomatoes,
        allergy::chocolate,
        allergy::pollen,
        allergy::cats
    };

    std::unordered_set<allergen> result{};
    for (const auto item : items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies

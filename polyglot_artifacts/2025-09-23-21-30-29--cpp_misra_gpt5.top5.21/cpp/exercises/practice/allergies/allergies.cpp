#include "allergies.h"
#include <array>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{(score & static_cast<std::uint32_t>(0xFFU))} {
}

bool allergy_test::is_allergic_to(allergen a) const noexcept {
    return ((score_ & static_cast<std::uint32_t>(a)) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result{};
    constexpr std::array<allergen, 8U> all{
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const allergen a : all) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies

#include "allergies.h"
#include <array>

namespace {
    using allergies::allergen;

    constexpr unsigned int mask_for(allergen a) {
        return 1u << static_cast<unsigned int>(a);
    }

    constexpr std::array<allergen, 8> all_allergens{
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };
}

namespace allergies {

allergy_test::allergy_test(unsigned int score)
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & mask_for(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    for (auto a : all_allergens) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies

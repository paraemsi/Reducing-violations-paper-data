#include "allergies.h"

namespace allergies {

namespace {
constexpr unsigned int bit_for(allergen a) noexcept {
    switch (a) {
        case allergen::eggs: return 1u;
        case allergen::peanuts: return 2u;
        case allergen::shellfish: return 4u;
        case allergen::strawberries: return 8u;
        case allergen::tomatoes: return 16u;
        case allergen::chocolate: return 32u;
        case allergen::pollen: return 64u;
        case allergen::cats: return 128u;
    }
    return 0u; // Unreachable; silences warnings
}
} // namespace

allergy_test::allergy_test(unsigned int score)
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen a) const {
    return (score_ & bit_for(a)) != 0u;
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
    for (allergen a : all) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies

#include "allergies.h"

namespace {
constexpr unsigned int kAllergenMask = 0xFFu;

constexpr unsigned int allergen_value(allergies::allergen a) {
    switch (a) {
        case allergies::allergen::eggs: return 1u;
        case allergies::allergen::peanuts: return 2u;
        case allergies::allergen::shellfish: return 4u;
        case allergies::allergen::strawberries: return 8u;
        case allergies::allergen::tomatoes: return 16u;
        case allergies::allergen::chocolate: return 32u;
        case allergies::allergen::pollen: return 64u;
        case allergies::allergen::cats: return 128u;
    }
    return 0u; // Unreachable, but silences warnings.
}

constexpr allergies::allergen kAllAllergens[] = {
    allergies::allergen::eggs,
    allergies::allergen::peanuts,
    allergies::allergen::shellfish,
    allergies::allergen::strawberries,
    allergies::allergen::tomatoes,
    allergies::allergen::chocolate,
    allergies::allergen::pollen,
    allergies::allergen::cats
};
}  // namespace

namespace allergies {

allergy_test::allergy_test(unsigned int score)
    : score_{score & kAllergenMask} {}

bool allergy_test::is_allergic_to(allergen a) const {
    return (score_ & allergen_value(a)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    for (auto a : kAllAllergens) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies

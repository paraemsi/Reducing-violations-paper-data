#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_(score) {}

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & score_for(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    if (is_allergic_to(allergen::eggs)) result.emplace(allergen::eggs);
    if (is_allergic_to(allergen::peanuts)) result.emplace(allergen::peanuts);
    if (is_allergic_to(allergen::shellfish)) result.emplace(allergen::shellfish);
    if (is_allergic_to(allergen::strawberries)) result.emplace(allergen::strawberries);
    if (is_allergic_to(allergen::tomatoes)) result.emplace(allergen::tomatoes);
    if (is_allergic_to(allergen::chocolate)) result.emplace(allergen::chocolate);
    if (is_allergic_to(allergen::pollen)) result.emplace(allergen::pollen);
    if (is_allergic_to(allergen::cats)) result.emplace(allergen::cats);
    return result;
}

unsigned int allergy_test::score_for(allergen item) {
    switch (item) {
        case allergen::eggs: return 1u;
        case allergen::peanuts: return 2u;
        case allergen::shellfish: return 4u;
        case allergen::strawberries: return 8u;
        case allergen::tomatoes: return 16u;
        case allergen::chocolate: return 32u;
        case allergen::pollen: return 64u;
        case allergen::cats: return 128u;
    }
    return 0u;
}

}  // namespace allergies

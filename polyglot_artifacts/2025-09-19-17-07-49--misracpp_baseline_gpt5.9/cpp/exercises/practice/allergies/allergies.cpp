#include "allergies.h"

#include <array>

namespace allergies {

namespace {
constexpr unsigned int value_of(allergen a) {
    switch (a) {
        case allergen::eggs:         return 1u;
        case allergen::peanuts:      return 2u;
        case allergen::shellfish:    return 4u;
        case allergen::strawberries: return 8u;
        case allergen::tomatoes:     return 16u;
        case allergen::chocolate:    return 32u;
        case allergen::pollen:       return 64u;
        case allergen::cats:         return 128u;
    }
    return 0u; // Unreachable; placate some compilers.
}

constexpr std::array<allergen, 8> all_items{
    allergen::eggs, allergen::peanuts, allergen::shellfish, allergen::strawberries,
    allergen::tomatoes, allergen::chocolate, allergen::pollen, allergen::cats
};
} // namespace

allergy_test::allergy_test(unsigned int score)
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & value_of(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    result.reserve(all_items.size());
    for (auto item : all_items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies

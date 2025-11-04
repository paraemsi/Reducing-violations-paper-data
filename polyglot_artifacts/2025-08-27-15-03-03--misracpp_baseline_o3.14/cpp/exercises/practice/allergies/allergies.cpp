#include "allergies.h"

#include <array>

namespace allergies {

namespace {

constexpr std::array<allergen, 8> kAllAllergens{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};

} // namespace

// Constructor
allergy_test::allergy_test(unsigned int score) noexcept
: score_{score} {}

// Determine if allergic to a specific allergen
bool allergy_test::is_allergic_to(allergen item) const noexcept {
    return static_cast<bool>(score_ & static_cast<unsigned int>(item));
}

// Return an unordered_set with all allergies
std::unordered_set<allergen> allergy_test::get_allergies() const noexcept {
    std::unordered_set<allergen> result;
    for (auto item : kAllAllergens) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies


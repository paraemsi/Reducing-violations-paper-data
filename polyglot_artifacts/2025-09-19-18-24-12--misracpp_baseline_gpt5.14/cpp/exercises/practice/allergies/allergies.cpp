#include "allergies.h"

#include <array>

namespace allergies {

namespace {
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
}  // namespace

allergy_test::allergy_test(unsigned int score) noexcept
    : score_{score & 0xFFu} {}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    return (score_ & static_cast<unsigned int>(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    result.reserve(all_allergens.size());
    for (auto a : all_allergens) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies

#include "allergies.h"
#include <array>

namespace {
constexpr unsigned int allergen_value(allergies::allergen a) noexcept {
    return 1u << static_cast<unsigned>(a);
}

constexpr std::array<allergies::allergen, 8> all_allergens{
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

allergy_test::allergy_test(unsigned int score) noexcept
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    return (score_ & allergen_value(item)) != 0u;
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

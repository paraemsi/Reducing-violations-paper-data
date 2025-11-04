#include "allergies.h"
#include <array>

namespace allergies {

namespace {
constexpr std::array<allergen, 8> all_known_allergens{
    allergen::eggs, allergen::peanuts, allergen::shellfish, allergen::strawberries,
    allergen::tomatoes, allergen::chocolate, allergen::pollen, allergen::cats};
}

allergy_test::allergy_test(unsigned int score) : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const {
  return (score_ & static_cast<unsigned int>(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
  std::unordered_set<allergen> result;
  for (auto a : all_known_allergens) {
    if (is_allergic_to(a)) {
      result.emplace(a);
    }
  }
  return result;
}

}  // namespace allergies

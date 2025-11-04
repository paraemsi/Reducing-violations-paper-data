#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(unsigned int score)
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & static_cast<unsigned int>(item)) != 0;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    for (allergen item :
         {allergen::eggs, allergen::peanuts, allergen::shellfish,
          allergen::strawberries, allergen::tomatoes, allergen::chocolate,
          allergen::pollen, allergen::cats}) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies

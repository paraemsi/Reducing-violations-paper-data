#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(std::uint32_t score)
    : score_{score} { }

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & static_cast<std::uint32_t>(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result{};
    for (auto a : {allergen::eggs, allergen::peanuts, allergen::shellfish,
                   allergen::strawberries, allergen::tomatoes, allergen::chocolate,
                   allergen::pollen, allergen::cats}) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies

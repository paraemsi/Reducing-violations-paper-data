#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(unsigned int score) noexcept
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    return (static_cast<unsigned int>(item) & score_) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> items;
    for (unsigned int bit = static_cast<unsigned int>(allergen::eggs);
         bit <= static_cast<unsigned int>(allergen::cats);
         bit <<= 1u) {
        allergen a = static_cast<allergen>(bit);
        if (is_allergic_to(a)) {
            items.emplace(a);
        }
    }
    return items;
}

}  // namespace allergies

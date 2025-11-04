#include "allergies.h"
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & static_cast<unsigned int>(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    for (unsigned int bit = 1u; bit <= static_cast<unsigned int>(allergen::cats); bit <<= 1u) {
        allergen current = static_cast<allergen>(bit);
        if (is_allergic_to(current)) {
            result.emplace(current);
        }
    }
    return result;
}

}  // namespace allergies

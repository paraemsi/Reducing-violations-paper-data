#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_{score} {}

bool allergy_test::is_allergic_to(allergen key) const {
    return (score_ & static_cast<unsigned int>(key)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;
    for (unsigned int bit = 1u; bit <= static_cast<unsigned int>(allergen::cats); bit <<= 1u) {
        if ((score_ & bit) != 0u) {
            result.emplace(static_cast<allergen>(bit));
        }
    }
    return result;
}

}  // namespace allergies

#include "allergies.h"
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) : score_(score & 255U) {
    // Mask to only consider allergens up to 128 (cats)
    // 255 = 0xFF = sum of all valid allergen values (1+2+4+8+16+32+64+128)
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    std::uint32_t allergen_value = 0U;
    
    if (allergen == "eggs") {
        allergen_value = 1U;
    } else if (allergen == "peanuts") {
        allergen_value = 2U;
    } else if (allergen == "shellfish") {
        allergen_value = 4U;
    } else if (allergen == "strawberries") {
        allergen_value = 8U;
    } else if (allergen == "tomatoes") {
        allergen_value = 16U;
    } else if (allergen == "chocolate") {
        allergen_value = 32U;
    } else if (allergen == "pollen") {
        allergen_value = 64U;
    } else if (allergen == "cats") {
        allergen_value = 128U;
    } else {
        return false;
    }
    
    return (score_ & allergen_value) != 0U;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> allergies;
    
    if ((score_ & 1U) != 0U) {
        allergies.emplace("eggs");
    }
    if ((score_ & 2U) != 0U) {
        allergies.emplace("peanuts");
    }
    if ((score_ & 4U) != 0U) {
        allergies.emplace("shellfish");
    }
    if ((score_ & 8U) != 0U) {
        allergies.emplace("strawberries");
    }
    if ((score_ & 16U) != 0U) {
        allergies.emplace("tomatoes");
    }
    if ((score_ & 32U) != 0U) {
        allergies.emplace("chocolate");
    }
    if ((score_ & 64U) != 0U) {
        allergies.emplace("pollen");
    }
    if ((score_ & 128U) != 0U) {
        allergies.emplace("cats");
    }
    
    return allergies;
}

}  // namespace allergies

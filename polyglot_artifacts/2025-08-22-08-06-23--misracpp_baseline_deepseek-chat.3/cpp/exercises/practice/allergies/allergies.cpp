#include "allergies.h"
#include <map>
#include <string>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_(score) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    unsigned int masked_score = score_ & 0xFF;
    if (allergen == "eggs") return masked_score & 1;
    if (allergen == "peanuts") return masked_score & 2;
    if (allergen == "shellfish") return masked_score & 4;
    if (allergen == "strawberries") return masked_score & 8;
    if (allergen == "tomatoes") return masked_score & 16;
    if (allergen == "chocolate") return masked_score & 32;
    if (allergen == "pollen") return masked_score & 64;
    if (allergen == "cats") return masked_score & 128;
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> allergies;
    unsigned int masked_score = score_ & 0xFF;
    
    // Check each possible allergen
    if (masked_score & 1) allergies.emplace("eggs");
    if (masked_score & 2) allergies.emplace("peanuts");
    if (masked_score & 4) allergies.emplace("shellfish");
    if (masked_score & 8) allergies.emplace("strawberries");
    if (masked_score & 16) allergies.emplace("tomatoes");
    if (masked_score & 32) allergies.emplace("chocolate");
    if (masked_score & 64) allergies.emplace("pollen");
    if (masked_score & 128) allergies.emplace("cats");
    
    return allergies;
}

}  // namespace allergies

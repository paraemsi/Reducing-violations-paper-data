#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(unsigned score) : score(score & 255) {
    // Mask the score to only consider values up to 255 (ignore 256 and above)
}

bool allergy_test::is_allergic_to(std::string allergen) const {
    // Define allergen values
    if (allergen == "eggs") return score & 1;
    if (allergen == "peanuts") return score & 2;
    if (allergen == "shellfish") return score & 4;
    if (allergen == "strawberries") return score & 8;
    if (allergen == "tomatoes") return score & 16;
    if (allergen == "chocolate") return score & 32;
    if (allergen == "pollen") return score & 64;
    if (allergen == "cats") return score & 128;
    
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> allergies;
    
    if (score & 1) allergies.emplace("eggs");
    if (score & 2) allergies.emplace("peanuts");
    if (score & 4) allergies.emplace("shellfish");
    if (score & 8) allergies.emplace("strawberries");
    if (score & 16) allergies.emplace("tomatoes");
    if (score & 32) allergies.emplace("chocolate");
    if (score & 64) allergies.emplace("pollen");
    if (score & 128) allergies.emplace("cats");
    
    return allergies;
}

}  // namespace allergies

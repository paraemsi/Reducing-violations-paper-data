#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score(score) {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    // First, get all allergies and check if the allergen is in the set
    std::unordered_set<std::string> allergies = get_allergies();
    return allergies.find(allergen) != allergies.end();
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    // Define the allergen scores
    static const std::pair<unsigned int, std::string> allergens[] = {
        {1, "eggs"},
        {2, "peanuts"},
        {4, "shellfish"},
        {8, "strawberries"},
        {16, "tomatoes"},
        {32, "chocolate"},
        {64, "pollen"},
        {128, "cats"}
    };
    
    std::unordered_set<std::string> result;
    // Mask the score to only consider up to 255
    unsigned int masked_score = score & 0xFF;
    
    // Check each allergen
    for (const auto& item : allergens) {
        if (masked_score & item.first) {
            result.emplace(item.second);
        }
    }
    return result;
}

}  // namespace allergies

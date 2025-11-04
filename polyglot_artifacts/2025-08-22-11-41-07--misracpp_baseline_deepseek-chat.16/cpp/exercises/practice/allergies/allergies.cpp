#include "allergies.h"
#include <map>
#include <string>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_(score & 0xFF) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    // Map allergens to their values
    static const std::map<std::string, unsigned int> allergen_values = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    auto it = allergen_values.find(allergen);
    if (it != allergen_values.end()) {
        // Check if the corresponding bit is set
        return (score_ & it->second) != 0;
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> allergies;
    
    // Check each possible allergen
    const std::pair<std::string, unsigned int> allergen_list[] = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    for (const auto& item : allergen_list) {
        if ((score_ & item.second) != 0) {
            allergies.emplace(item.first);
        }
    }
    
    return allergies;
}

}  // namespace allergies

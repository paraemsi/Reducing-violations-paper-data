#include "allergies.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <utility>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(int score) : score_(static_cast<std::uint8_t>((score & 0xFF))) {
    // Masking is done during initialization to ignore higher bits
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    // Map allergens to their scores
    static const std::vector<std::pair<std::string, std::uint8_t>> allergens = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };
    
    for (const auto& item : allergens) {
        if (item.first == allergen) {
            // Ensure proper parentheses
            return ((score_ & item.second) != 0U);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    // Map allergens to their scores
    static const std::vector<std::pair<std::string, std::uint8_t>> allergens = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };
    
    for (const auto& item : allergens) {
        // Ensure proper parentheses
        if ((score_ & item.second) != 0U) {
            result.emplace(item.first);
        }
    }
    return result;
}

}  // namespace allergies

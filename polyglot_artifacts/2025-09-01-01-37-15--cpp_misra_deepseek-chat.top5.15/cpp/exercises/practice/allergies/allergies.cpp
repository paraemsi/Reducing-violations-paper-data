#include "allergies.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <utility>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_(static_cast<std::uint8_t>(score & 0xFFU)) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    // Define all allergens and their scores
    const std::vector<std::pair<std::string, std::uint8_t>> allergens = {
        {"eggs", static_cast<std::uint8_t>(1U)},
        {"peanuts", static_cast<std::uint8_t>(2U)},
        {"shellfish", static_cast<std::uint8_t>(4U)},
        {"strawberries", static_cast<std::uint8_t>(8U)},
        {"tomatoes", static_cast<std::uint8_t>(16U)},
        {"chocolate", static_cast<std::uint8_t>(32U)},
        {"pollen", static_cast<std::uint8_t>(64U)},
        {"cats", static_cast<std::uint8_t>(128U)}
    };
    
    for (const auto& item : allergens) {
        if (item.first == allergen) {
            return ((score_ & item.second) != 0U);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    // Define all allergens and their scores
    const std::vector<std::pair<std::string, std::uint8_t>> allergens = {
        {"eggs", static_cast<std::uint8_t>(1U)},
        {"peanuts", static_cast<std::uint8_t>(2U)},
        {"shellfish", static_cast<std::uint8_t>(4U)},
        {"strawberries", static_cast<std::uint8_t>(8U)},
        {"tomatoes", static_cast<std::uint8_t>(16U)},
        {"chocolate", static_cast<std::uint8_t>(32U)},
        {"pollen", static_cast<std::uint8_t>(64U)},
        {"cats", static_cast<std::uint8_t>(128U)}
    };
    
    for (const auto& item : allergens) {
        if ((score_ & item.second) != 0U) {
            result.emplace(item.first);
        }
    }
    return result;
}

}  // namespace allergies

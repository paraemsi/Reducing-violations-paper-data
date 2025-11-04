#include "allergies.h"
#include <string>
#include <unordered_set>
#include <map>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) : score_(static_cast<std::uint8_t>(score & 0xFFU)) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    static const std::map<std::string, std::uint8_t> allergen_values = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };
    
    auto it = allergen_values.find(allergen);
    if (it != allergen_values.end()) {
        return (score_ & it->second) != 0U;
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    static const std::map<std::uint8_t, std::string> value_allergens = {
        {1U, "eggs"},
        {2U, "peanuts"},
        {4U, "shellfish"},
        {8U, "strawberries"},
        {16U, "tomatoes"},
        {32U, "chocolate"},
        {64U, "pollen"},
        {128U, "cats"}
    };
    
    std::unordered_set<std::string> result;
    for (const auto& pair : value_allergens) {
        if ((score_ & pair.first) != 0U) {
            result.emplace(pair.second);
        }
    }
    return result;
}

}  // namespace allergies

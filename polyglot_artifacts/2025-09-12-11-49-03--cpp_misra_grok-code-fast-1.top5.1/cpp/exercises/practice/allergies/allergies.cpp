#include "allergies.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstdint>

namespace allergies {

    static const std::unordered_map<std::string, std::uint32_t> allergen_scores = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };

    allergy_test::allergy_test(std::uint32_t score) : score_(score) {}

    bool allergy_test::is_allergic_to(const std::string& allergen) const {
        auto it = allergen_scores.find(allergen);
        if (it == allergen_scores.end()) {
            return false;
        }
        if ((score_ & it->second) != 0U) {
            return true;
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const {
        std::unordered_set<std::string> result;
        for (const auto& pair : allergen_scores) {
            if ((score_ & pair.second) != 0U) {
                result.emplace(pair.first);
            }
        }
        return result;
    }

}  // namespace allergies

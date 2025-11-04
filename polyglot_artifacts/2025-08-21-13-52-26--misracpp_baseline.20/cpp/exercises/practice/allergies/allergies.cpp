#include "allergies.h"

namespace allergies {

    // List of allergens and their corresponding values, in order
    const std::vector<std::pair<std::string, unsigned int>> allergy_test::allergen_list = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };

    allergy_test::allergy_test(unsigned int score)
        : score_(score)
    {}

    bool allergy_test::is_allergic_to(const std::string& allergen) const {
        for (const auto& item : allergen_list) {
            if (item.first == allergen) {
                return (score_ & item.second) != 0;
            }
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const {
        std::unordered_set<std::string> result;
        for (const auto& item : allergen_list) {
            if ((score_ & item.second) != 0) {
                result.emplace(item.first);
            }
        }
        return result;
    }

}  // namespace allergies

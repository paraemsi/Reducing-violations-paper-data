#include "allergies.h"

namespace allergies {

    const std::vector<std::string> allergen_list = {
        "eggs",        // 1
        "peanuts",     // 2
        "shellfish",   // 4
        "strawberries",// 8
        "tomatoes",    // 16
        "chocolate",   // 32
        "pollen",      // 64
        "cats"         // 128
    };

    allergy_test::allergy_test(unsigned int score)
        : score_(score) {}

    bool allergy_test::is_allergic_to(const std::string& allergen) const {
        for (size_t i = 0; i < allergen_list.size(); ++i) {
            if (allergen_list[i] == allergen) {
                return (score_ & (1u << i)) != 0;
            }
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const {
        std::unordered_set<std::string> result;
        for (size_t i = 0; i < allergen_list.size(); ++i) {
            if ((score_ & (1u << i)) != 0) {
                result.emplace(allergen_list[i]);
            }
        }
        return result;
    }

}  // namespace allergies

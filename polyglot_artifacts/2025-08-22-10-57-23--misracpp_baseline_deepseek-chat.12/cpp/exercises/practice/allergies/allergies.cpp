#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

using namespace std;

allergy_test::allergy_test(unsigned int score) : score_(score & 255) {
}

bool allergy_test::is_allergic_to(const string& allergen) const {
    static const unordered_map<string, unsigned int> allergen_scores = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        return (score_ & it->second) != 0;
    }
    return false;
}

unordered_set<string> allergy_test::get_allergies() const {
    unordered_set<string> allergies;
    static const unordered_map<string, unsigned int> allergen_scores = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    for (const auto& pair : allergen_scores) {
        if (score_ & pair.second) {
            allergies.emplace(pair.first);
        }
    }
    return allergies;
}

}  // namespace allergies

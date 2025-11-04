#include "allergies.h"
#include <map>
#include <string>

namespace allergies {

using namespace std;

allergy_test::allergy_test(unsigned int score) : score_(score & 0xFF) {
}

bool allergy_test::is_allergic_to(const string& allergen) const {
    static const map<string, unsigned int> allergen_values = {
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
        return (score_ & it->second) != 0;
    }
    return false;
}

unordered_set<string> allergy_test::get_allergies() const {
    unordered_set<string> allergies;
    
    // Check each possible allergen
    if (score_ & 1) allergies.emplace("eggs");
    if (score_ & 2) allergies.emplace("peanuts");
    if (score_ & 4) allergies.emplace("shellfish");
    if (score_ & 8) allergies.emplace("strawberries");
    if (score_ & 16) allergies.emplace("tomatoes");
    if (score_ & 32) allergies.emplace("chocolate");
    if (score_ & 64) allergies.emplace("pollen");
    if (score_ & 128) allergies.emplace("cats");
    
    return allergies;
}

}  // namespace allergies

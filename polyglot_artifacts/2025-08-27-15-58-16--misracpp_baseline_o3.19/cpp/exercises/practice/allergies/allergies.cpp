#include "allergies.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <utility>   // for std::pair

namespace allergies {

namespace {
const std::vector<std::pair<std::string, unsigned int>> allergen_list{
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}
};
} // namespace

// Constructor
Allergies::Allergies(unsigned int score) : score_{score & 0xFFu} {}

// Check single allergen
bool Allergies::is_allergic_to(const std::string& item) const {
    for (const auto& [name, value] : allergen_list) {
        if (name == item) {
            return (score_ & value) != 0u;
        }
    }
    return false;
}

// List all allergens present in the score
std::vector<std::string> Allergies::list() const {
    std::vector<std::string> result;
    for (const auto& [name, value] : allergen_list) {
        if ((score_ & value) != 0u) {
            result.push_back(name);
        }
    }
    return result;
}

// unordered_set version used by the tests
std::unordered_set<std::string> Allergies::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& [name, value] : allergen_list) {
        if ((score_ & value) != 0u) {
            result.emplace(name);
        }
    }
    return result;
}

// Factory helper that wraps the constructor (expected by tests)
Allergies allergy_test(unsigned int score) {
    return Allergies{score};
}

}  // namespace allergies

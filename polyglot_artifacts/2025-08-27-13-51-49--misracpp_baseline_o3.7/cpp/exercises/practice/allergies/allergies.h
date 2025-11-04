#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(unsigned int score);

    // Returns true if `allergen` is present in the stored score
    bool is_allergic_to(const std::string& allergen) const;

    // Returns a set with all allergens contained in the stored score
    std::unordered_set<std::string> get_allergies() const;

private:
    unsigned int score_;
    static const std::unordered_map<std::string, unsigned int> allergen_values_;
};

}  // namespace allergies

#endif // ALLERGIES_H

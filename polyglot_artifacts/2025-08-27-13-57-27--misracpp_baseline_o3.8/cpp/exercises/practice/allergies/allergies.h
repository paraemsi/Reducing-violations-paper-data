#if !defined(ALLERGIES_H)
#define ALLERGIES_H
#include <vector>
#include <string>
#include <unordered_set>

namespace allergies {

enum allergen {
    eggs = 1,
    peanuts = 2,
    shellfish = 4,
    strawberries = 8,
    tomatoes = 16,
    chocolate = 32,
    pollen = 64,
    cats = 128
};

class allergy_test {
public:
    explicit allergy_test(int score);
    bool is_allergic_to(allergen a) const;
    bool is_allergic_to(const std::string& allergen_name) const;
    std::unordered_set<std::string> get_allergies() const;
private:
    int score_;
};

}  // namespace allergies

#endif // ALLERGIES_H

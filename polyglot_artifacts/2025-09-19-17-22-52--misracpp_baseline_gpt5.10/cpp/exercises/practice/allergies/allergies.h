#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>

namespace allergies {

enum class allergen : unsigned int {
    eggs = 1u,
    peanuts = 2u,
    shellfish = 4u,
    strawberries = 8u,
    tomatoes = 16u,
    chocolate = 32u,
    pollen = 64u,
    cats = 128u
};

class allergy_test {
public:
    explicit allergy_test(unsigned int score);
    bool is_allergic_to(allergen item) const;
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies


#endif // ALLERGIES_H

#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <functional>  // std::hash specialization
#include <cstddef>     // std::size_t

namespace allergies {

enum class allergen {
    eggs = 1,
    peanuts = 2,
    shellfish = 4,
    strawberries = 8,
    tomatoes = 16,
    chocolate = 32,
    pollen = 64,
    cats = 128
};

// Provide std::hash specialization for allergen before it is used in unordered_set

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

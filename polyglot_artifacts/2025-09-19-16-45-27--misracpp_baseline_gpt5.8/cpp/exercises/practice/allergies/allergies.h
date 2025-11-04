#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstddef>

namespace allergies {

enum class allergen : unsigned int {
    eggs = 1,
    peanuts = 2,
    shellfish = 4,
    strawberries = 8,
    tomatoes = 16,
    chocolate = 32,
    pollen = 64,
    cats = 128
};

struct allergen_hash {
    std::size_t operator()(allergen a) const noexcept {
        return static_cast<unsigned int>(a);
    }
};

class allergy_test {
public:
    explicit allergy_test(unsigned int score);
    bool is_allergic_to(allergen item) const;
    std::unordered_set<allergen, allergen_hash> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies


#endif // ALLERGIES_H

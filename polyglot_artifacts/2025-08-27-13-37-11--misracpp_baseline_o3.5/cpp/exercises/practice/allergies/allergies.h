#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstdint>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs        = 1,
    peanuts     = 2,
    shellfish   = 4,
    strawberries = 8,
    tomatoes    = 16,
    chocolate   = 32,
    pollen      = 64,
    cats        = 128
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score);

    bool is_allergic_to(allergen item) const;
    std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

#endif // ALLERGIES_H

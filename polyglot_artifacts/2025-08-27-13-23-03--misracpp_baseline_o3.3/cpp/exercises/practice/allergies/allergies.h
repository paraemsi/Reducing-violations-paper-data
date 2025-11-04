#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <array>
#include <string>

namespace allergies {

// Each allergen maps to its corresponding score value.
enum class Allergen : unsigned int {
    eggs        = 1,
    peanuts     = 2,
    shellfish   = 4,
    strawberries= 8,
    tomatoes    = 16,
    chocolate   = 32,
    pollen      = 64,
    cats        = 128
};

class Allergies {
public:
    explicit Allergies(unsigned int score);

    // Return true if the given allergen bit is present in the stored score.
    bool is_allergic_to(const std::string& allergen) const;

    // Return a set containing all allergens represented in the stored score.
    std::unordered_set<std::string> get_allergies() const;

private:
    bool is_allergic_to(Allergen allergen) const;
    unsigned int score_;
};

// Alias expected by automated tests
using allergy_test = Allergies;

}  // namespace allergies

// Allow Allergen to be used in unordered containers.
namespace std {
template<>
struct hash<allergies::Allergen> {
    std::size_t operator()(const allergies::Allergen& a) const noexcept {
        return static_cast<std::size_t>(a);
    }
};
}  // namespace std

#endif // ALLERGIES_H

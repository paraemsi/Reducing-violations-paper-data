#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstddef>
#include <unordered_set>

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


class allergy_test {
public:
    explicit allergy_test(unsigned int score);

    // Returns true if the tested person is allergic to the given allergen
    bool is_allergic_to(allergen key) const;

    // Returns the set of all allergens this person is allergic to
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

// Provide a std::hash specialization so that `allergen` can be used as the key
// in unordered associative containers (e.g. std::unordered_set).
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<std::size_t>(a);
    }
};
}  // namespace std

#endif // ALLERGIES_H

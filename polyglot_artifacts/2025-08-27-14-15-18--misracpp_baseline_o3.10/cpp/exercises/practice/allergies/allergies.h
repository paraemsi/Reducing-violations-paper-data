#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <vector>
#include <string>
#include <functional>

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

class allergies {
public:
    explicit allergies(unsigned int score);

    // Return true if `allergen` is present in the person's allergy set.
    bool is_allergic_to(allergen allergen) const;
    bool is_allergic_to(const std::string& allergen_name) const;

    // Return the list of allergens the person is allergic to in the canonical order.
    std::vector<std::string> get_allergies() const;

private:
    unsigned int score_;
    std::unordered_set<allergen> allergies_;

    void compute_allergies();
};
using allergy_test = allergies;

}  // namespace allergies


#endif // ALLERGIES_H

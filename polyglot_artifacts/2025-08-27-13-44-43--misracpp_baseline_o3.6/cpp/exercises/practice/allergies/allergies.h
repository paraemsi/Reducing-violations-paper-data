#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <vector>
#include <unordered_set>
#include <string>
#include <cstddef>
#include <functional>

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

class allergy_test {
public:
    explicit allergy_test(unsigned int score);

    bool is_allergic_to(allergen a) const;
    bool is_allergic_to(const std::string& allergen_name) const;

    std::vector<allergen> get_allergens() const;
    std::unordered_set<std::string> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

namespace std {
template <>
struct hash<allergies::allergen> {
    size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<size_t>(a);
    }
};
}  // namespace std

#endif // ALLERGIES_H

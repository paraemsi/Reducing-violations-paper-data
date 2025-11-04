#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstddef>  // for std::size_t
#include <functional>  // for std::hash specialization

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

    bool is_allergic_to(allergen item) const;

    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

// Enable use of allergies::allergen in unordered containers
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(allergies::allergen a) const noexcept {
        return static_cast<std::size_t>(a);
    }
};
}  // namespace std

#endif // ALLERGIES_H

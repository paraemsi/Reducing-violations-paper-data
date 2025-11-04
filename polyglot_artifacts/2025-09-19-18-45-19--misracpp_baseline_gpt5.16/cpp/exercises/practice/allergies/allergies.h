#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <functional>
#include <cstddef>

namespace allergies {

enum class allergen {
    eggs,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats
};

class allergy_test {
public:
    explicit allergy_test(unsigned int score);
    bool is_allergic_to(allergen item) const;
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
    static unsigned int score_for(allergen item);
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

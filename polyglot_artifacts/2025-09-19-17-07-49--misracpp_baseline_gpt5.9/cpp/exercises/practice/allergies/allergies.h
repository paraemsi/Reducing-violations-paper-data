#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <functional>
#include <cstddef>
#include <type_traits>

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

}  // namespace allergies

namespace std {
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        using UT = std::underlying_type_t<allergies::allergen>;
        return static_cast<std::size_t>(static_cast<UT>(a));
    }
};
}  // namespace std

namespace allergies {

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

#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <cstddef>
#include <functional>

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

struct allergen_hash {
    std::size_t operator()(allergen a) const noexcept;
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen, allergen_hash> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies


#endif // ALLERGIES_H

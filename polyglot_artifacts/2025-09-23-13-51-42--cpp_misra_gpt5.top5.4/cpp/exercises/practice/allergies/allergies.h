#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <functional>
#include <cstddef>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

namespace std {
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen a) const noexcept {
        return static_cast<std::size_t>(static_cast<std::uint32_t>(a));
    }
};
}  // namespace std

#endif // ALLERGIES_H

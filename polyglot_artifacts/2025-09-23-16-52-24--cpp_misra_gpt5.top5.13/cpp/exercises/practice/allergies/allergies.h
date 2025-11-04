#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <functional>

namespace allergies {

enum class allergen : std::uint8_t {
    eggs = static_cast<std::uint8_t>(1),
    peanuts = static_cast<std::uint8_t>(2),
    shellfish = static_cast<std::uint8_t>(4),
    strawberries = static_cast<std::uint8_t>(8),
    tomatoes = static_cast<std::uint8_t>(16),
    chocolate = static_cast<std::uint8_t>(32),
    pollen = static_cast<std::uint8_t>(64),
    cats = static_cast<std::uint8_t>(128)
};

}  // namespace allergies

namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<std::size_t>(static_cast<std::uint8_t>(a));
    }
};
}  // namespace std

namespace allergies {
class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

#endif // ALLERGIES_H

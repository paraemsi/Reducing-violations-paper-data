#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <unordered_set>
#include <vector>
#include <functional>

namespace allergies {

/*  Enumeration representing each allergen as a unique bit value.  */
enum class allergen : std::uint32_t {
    eggs         = 1U,
    peanuts      = 2U,
    shellfish    = 4U,
    strawberries = 8U,
    tomatoes     = 16U,
    chocolate    = 32U,
    pollen       = 64U,
    cats         = 128U
};

}  // namespace allergies

/*  Hash specialisation to allow use of allergen inside unordered containers. */
namespace std {
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return std::hash<std::uint32_t>{}(static_cast<std::uint32_t>(a));
    }
};
} // namespace std

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score_in);

    bool is_allergic_to(allergen allergen_key) const;

    std::vector<allergen> get_allergies() const;

private:
    std::uint32_t m_score;
    std::unordered_set<allergen> m_allergy_set;
};

}  // namespace allergies

#endif // ALLERGIES_H

#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstdint>
#include <functional>

namespace allergies {

// Bit values representing each allergen the test knows about.
enum class allergen : std::uint8_t {
    eggs        = 1,
    peanuts     = 2,
    shellfish   = 4,
    strawberries= 8,
    tomatoes    = 16,
    chocolate   = 32,
    pollen      = 64,
    cats        = 128
};

// Encapsulates a person's allergy score and related queries.
class allergy_test {
public:
    explicit allergy_test(std::uint32_t score);

    // Return true if the stored score contains the specified allergen bit.
    bool is_allergic_to(allergen item) const;

    // Return a set containing every allergen present in the stored score.
    std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

// Provide a std::hash specialization so allergen can be used in unordered containers.
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<std::size_t>(a);
    }
};
}  // namespace std

#endif // ALLERGIES_H

#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstdint>
#include <cstddef>
#include <string>

namespace allergies {

// Each allergen and its corresponding score value
enum class Allergen : std::uint8_t {
    eggs        = 1,
    peanuts     = 2,
    shellfish   = 4,
    strawberries= 8,
    tomatoes    = 16,
    chocolate   = 32,
    pollen      = 64,
    cats        = 128
};

// Hash functor so we can store enum class values in unordered containers
struct EnumClassHash {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

class Allergies {
public:
    explicit Allergies(unsigned int score);

    // Check if the tested person is allergic to a particular allergen
    bool is_allergic_to(Allergen item) const;
    bool is_allergic_to(const std::string& item) const;

    // Return the complete set of allergens the person is allergic to
    std::unordered_set<std::string> get_allergies() const;

private:
    std::unordered_set<Allergen, EnumClassHash> allergies_;
};

// ------------------------------------------------------------------
// Back-compatibility aliases expected by some test suites.
// ------------------------------------------------------------------
using allergy_test = Allergies;

}  // namespace allergies

#endif // ALLERGIES_H

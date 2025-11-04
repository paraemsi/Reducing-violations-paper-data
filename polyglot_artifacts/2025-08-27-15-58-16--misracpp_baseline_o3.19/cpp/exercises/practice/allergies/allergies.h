#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>

namespace allergies {

// Class representing the results of an allergy test.
class Allergies {
public:
    explicit Allergies(unsigned int score);

    // Returns true if the subject is allergic to `item`.
    bool is_allergic_to(const std::string& item) const;

    // Returns all allergens the subject is allergic to, in ascending score order.
    std::vector<std::string> list() const;
    // Returns all allergens as an unordered_set (used by the test-suite)
    std::unordered_set<std::string> get_allergies() const;

private:
    // Only keep the 8 least-significant bits that map to known allergens.
    unsigned int score_;
};

// Factory helper expected by the exercism test-suite
Allergies allergy_test(unsigned int score);

}  // namespace allergies

#endif // ALLERGIES_H

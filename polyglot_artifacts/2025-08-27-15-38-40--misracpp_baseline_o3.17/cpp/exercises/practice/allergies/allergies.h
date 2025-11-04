#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(unsigned int score);

    // Returns true if the person is allergic to the given item
    bool is_allergic_to(const std::string& item) const;

    // Returns a vector containing all allergens the person is allergic to
    std::vector<std::string> get_allergies() const;

private:
    unsigned int score_;
    std::unordered_set<std::string> allergies_;
};

}  // namespace allergies

#endif // ALLERGIES_H

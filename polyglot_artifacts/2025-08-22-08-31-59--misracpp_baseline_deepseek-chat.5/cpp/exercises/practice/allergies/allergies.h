#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>

namespace allergies {

class allergy_test {
private:
    unsigned int score_;
public:
    allergy_test(unsigned int score);
    bool is_allergic_to(const std::string& allergen) const;
    std::unordered_set<std::string> get_allergies() const;
};

}  // namespace allergies

#endif // ALLERGIES_H

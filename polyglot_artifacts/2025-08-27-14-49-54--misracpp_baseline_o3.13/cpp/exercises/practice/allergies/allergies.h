#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(unsigned int score);

    bool is_allergic_to(const std::string& item) const;
    std::unordered_set<std::string> get_allergies() const;

private:
    unsigned int score_;
    static const std::unordered_map<std::string, unsigned int> allergen_map_;
};

}  // namespace allergies

#endif // ALLERGIES_H

#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(unsigned int score) noexcept;

    bool is_allergic_to(const std::string& item) const;

    std::unordered_set<std::string> get_allergies() const;

private:
    unsigned int score_;
    static unsigned int mask_for(const std::string& item);
};

}  // namespace allergies

#endif // ALLERGIES_H

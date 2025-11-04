#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(unsigned int score) noexcept;

    bool is_allergic_to(const std::string& item) const noexcept;
    bool allergic_to(const std::string& item) const noexcept;

    std::unordered_set<std::string> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

#endif // ALLERGIES_H

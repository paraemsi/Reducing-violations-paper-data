#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace allergies {

class allergy_test {
private:
    std::uint8_t score_;
public:
    explicit allergy_test(std::uint32_t score);
    bool is_allergic_to(const std::string& allergen) const;
    std::unordered_set<std::string> get_allergies() const;
};

}  // namespace allergies

#endif // ALLERGIES_H

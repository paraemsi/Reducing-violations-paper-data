#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <string>

namespace allergies {

 // Allergy item names are represented as strings.

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(const std::string& item) const noexcept;

    std::unordered_set<std::string> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies


#endif // ALLERGIES_H

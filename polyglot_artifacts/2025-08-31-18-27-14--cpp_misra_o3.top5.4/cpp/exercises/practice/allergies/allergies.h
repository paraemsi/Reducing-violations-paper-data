#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace allergies {

class Allergies {
public:
    explicit Allergies(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& item) const noexcept;

    [[nodiscard]] std::unordered_set<std::string> get_allergies() const noexcept;

private:
    void populate_allergens(std::uint32_t score) noexcept;

    std::unordered_set<std::string> allergens_;
};

Allergies allergy_test(std::uint32_t score) noexcept;

}  // namespace allergies

#endif // ALLERGIES_H

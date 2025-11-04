#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

class phone_number final {
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;
    [[nodiscard]] auto pretty() const -> std::string;

private:
    std::string m_number{};                       /* Stored 10-digit cleaned number */

    static auto clean(const std::string& input) -> std::string;
    static auto is_valid(const std::string& digits) -> bool;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <cstdint>
#include <locale>
#include <stdexcept>
#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;
    [[nodiscard]] auto pretty() const -> std::string;

private:
    std::string m_digits;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

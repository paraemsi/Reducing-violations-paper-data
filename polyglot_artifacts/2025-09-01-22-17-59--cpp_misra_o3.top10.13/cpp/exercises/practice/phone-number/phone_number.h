#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

class phone_number
{
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string digits_;

    static constexpr bool is_digit_char(char ch) noexcept;
    static bool has_valid_prefix(const std::string& num) noexcept;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

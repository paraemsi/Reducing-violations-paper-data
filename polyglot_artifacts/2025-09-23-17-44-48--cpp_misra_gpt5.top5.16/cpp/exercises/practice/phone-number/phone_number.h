#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number final {
public:
    explicit phone_number(const std::string& input);
    std::string number() const noexcept;
    std::string area_code() const noexcept;
    std::string pretty() const noexcept;

private:
    std::string cleaned_;

    static bool is_decimal_digit(char ch) noexcept;
    static bool is_permitted_separator(char ch) noexcept;
    static bool has_valid_structure(const std::string& digits) noexcept;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

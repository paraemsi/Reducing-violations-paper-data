#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <string_view>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(std::string_view input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string m_clean_number;

    static bool is_digit(char c) noexcept;
    static bool is_valid_first_digit(char c) noexcept;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

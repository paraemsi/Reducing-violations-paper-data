#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& raw_number);

    [[nodiscard]] std::string number() const noexcept;
    [[nodiscard]] std::string area_code() const noexcept;
    [[nodiscard]] std::string pretty() const noexcept;

private:
    std::string number_;

    static bool is_digit(char c) noexcept;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

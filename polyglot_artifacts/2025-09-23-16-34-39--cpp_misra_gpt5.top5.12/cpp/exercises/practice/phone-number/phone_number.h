#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);
    std::string number() const;
    std::string area_code() const;
    explicit operator std::string() const;

private:
    std::string digits_;

    static std::string clean(const std::string& input);
    static std::string invalid_number() noexcept;
    static bool is_valid_area_or_exchange_start_char(char ch) noexcept;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

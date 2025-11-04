#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);
    std::string number() const;
    std::string area_code() const;
    std::string pretty() const;

private:
    std::string cleaned_;

    static bool contains_alpha(const std::string& s) noexcept;
    static std::string only_digits(const std::string& s);
    static bool valid_nxx_rules(const std::string& digits) noexcept;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

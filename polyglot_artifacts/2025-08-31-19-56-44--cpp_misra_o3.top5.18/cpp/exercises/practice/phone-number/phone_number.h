#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstddef>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string digits_;

    static std::string clean(const std::string& input);
    static bool is_valid(const std::string& digits);
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

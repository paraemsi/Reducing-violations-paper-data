#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);
    auto number() const -> std::string;
    auto area_code() const -> std::string;
    operator std::string() const;

private:
    std::string digits_;
};

auto clean(const std::string& input) -> std::string;

}  // namespace phone_number

#endif // PHONE_NUMBER_H

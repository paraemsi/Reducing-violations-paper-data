#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

auto clean(const std::string& input) -> std::string;

class phone_number {
public:
    explicit phone_number(const std::string& input);
    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty() const -> std::string;

private:
    std::string digits_;
};

} // namespace phone_number

#endif // PHONE_NUMBER_H

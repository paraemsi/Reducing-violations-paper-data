#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#include <string>
#include <string_view>
#include <cstdint>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(std::string_view input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] explicit operator std::string() const;

private:
    std::string digits_{};

    static auto clean_input(std::string_view input) -> std::string;
    static auto valid_number(const std::string& digits) -> bool;
};

} // namespace phone_number

#endif // PHONE_NUMBER_H

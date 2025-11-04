#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

auto clean(std::string const& number) -> std::string;

class phone_number
{
public:
    explicit phone_number(std::string const& number);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;
    [[nodiscard]] auto pretty() const -> std::string;

private:
    std::string _number;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

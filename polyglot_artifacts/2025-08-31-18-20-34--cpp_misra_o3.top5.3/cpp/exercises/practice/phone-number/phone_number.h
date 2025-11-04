#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <string_view>

namespace phone_number {

class phone_number final
{
public:
    explicit phone_number(std::string_view input);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;
    [[nodiscard]] auto pretty() const -> std::string;

private:
    std::string cleaned_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

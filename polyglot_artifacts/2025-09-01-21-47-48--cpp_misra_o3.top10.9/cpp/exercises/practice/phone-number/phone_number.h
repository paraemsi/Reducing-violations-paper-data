#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number
{
public:
    explicit phone_number(const std::string& raw);

    [[nodiscard]] auto number() const -> std::string;
    [[nodiscard]] auto area_code() const -> std::string;

    explicit operator std::string() const;

private:
    std::string m_number;

    static auto clean(const std::string& raw) -> std::string;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

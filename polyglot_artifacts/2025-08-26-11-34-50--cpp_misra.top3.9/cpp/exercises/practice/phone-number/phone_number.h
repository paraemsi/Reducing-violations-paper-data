#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

class phone_number
{
public:
    explicit phone_number(std::string const& input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string m_number;
};

[[nodiscard]] std::string clean(std::string const& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H

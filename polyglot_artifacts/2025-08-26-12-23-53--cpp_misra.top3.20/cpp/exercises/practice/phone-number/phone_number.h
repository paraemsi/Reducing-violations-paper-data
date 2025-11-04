#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

using phone_str_t = std::string;

class phone_number
{
public:
    explicit phone_number(phone_str_t const& input);

    auto number() const -> phone_str_t;

private:
    phone_str_t number_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

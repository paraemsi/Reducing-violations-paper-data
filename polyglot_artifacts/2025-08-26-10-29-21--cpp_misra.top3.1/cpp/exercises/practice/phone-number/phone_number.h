#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

typedef std::string phone_string_t;

class phone_number
{
public:
    explicit phone_number(phone_string_t const& input);
    phone_string_t number() const;
    phone_string_t area_code() const;
    phone_string_t pretty() const;

private:
    phone_string_t m_number;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

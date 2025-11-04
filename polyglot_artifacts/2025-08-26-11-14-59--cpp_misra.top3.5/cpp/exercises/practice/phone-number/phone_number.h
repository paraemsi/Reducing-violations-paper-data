#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

typedef std::string phone_str_t;

class phone_number
{
public:
    explicit phone_number(const phone_str_t& input);
    phone_str_t number() const;
    phone_str_t area_code() const;
    phone_str_t pretty() const;

private:
    phone_str_t m_number;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

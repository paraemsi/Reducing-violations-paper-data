#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

#if defined(__cplusplus) && (__cplusplus >= 201703L)
#define PHONE_NODISCARD [[nodiscard]]
#else
#define PHONE_NODISCARD
#endif

namespace phone_number {

class phone_number
{
public:
    explicit phone_number(const ::std::string& input);

    PHONE_NODISCARD ::std::string number() const;
    PHONE_NODISCARD ::std::string area_code() const;
    PHONE_NODISCARD ::std::string pretty() const;

private:
    ::std::string m_number;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H
#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& raw_input);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string m_clean;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

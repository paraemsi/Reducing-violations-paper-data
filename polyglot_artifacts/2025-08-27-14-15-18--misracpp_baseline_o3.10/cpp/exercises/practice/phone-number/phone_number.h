#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
  public:
    explicit phone_number(const std::string &input);
    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

  private:
    std::string digits_;
    static std::string clean_number(const std::string &input);
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H

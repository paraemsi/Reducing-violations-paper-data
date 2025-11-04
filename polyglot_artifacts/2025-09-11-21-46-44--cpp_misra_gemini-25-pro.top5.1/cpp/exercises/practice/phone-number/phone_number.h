#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
   public:
    explicit phone_number(const std::string& text);
    const std::string& number() const { return cleaned_number; }
    std::string area_code() const { return cleaned_number.substr(0, 3); }
    explicit operator std::string() const;

   private:
    const std::string cleaned_number;
};

}  // namespace phone_number

#endif  // PHONE_NUMBER_H

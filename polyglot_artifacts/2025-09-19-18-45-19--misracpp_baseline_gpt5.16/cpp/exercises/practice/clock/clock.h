#ifndef DATE_INDEPENDENT_CLOCK_H
#define DATE_INDEPENDENT_CLOCK_H

#include <string>
#include <ostream>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute);
    static clock at(int hour, int minute = 0);
    clock plus(int minutes) const;
    clock minus(int minutes) const;
    operator std::string() const;
    bool operator==(const clock& rhs) const;
    bool operator!=(const clock& rhs) const;
private:
    int total_minutes_;
};

std::string to_string(const clock& c);
std::ostream& operator<<(std::ostream& os, const clock& c);

}  // namespace date_independent

#endif // DATE_INDEPENDENT_CLOCK_H

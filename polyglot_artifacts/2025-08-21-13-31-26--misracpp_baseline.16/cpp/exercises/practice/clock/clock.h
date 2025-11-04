#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute);

    static clock at(int hour, int minute);

    clock plus(int minutes) const;
    clock minus(int minutes) const;

    std::string to_string() const;
    operator std::string() const { return to_string(); }

    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H

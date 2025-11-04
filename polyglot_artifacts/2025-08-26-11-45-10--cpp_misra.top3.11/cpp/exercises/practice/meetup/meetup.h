#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <string>

namespace meetup {

using year_t = std::int32_t;
using month_t = std::uint8_t;
using day_t = std::uint8_t;

// Forward declaration of scheduler class
class scheduler;

}  // namespace meetup

#endif // MEETUP_H

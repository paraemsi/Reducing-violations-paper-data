#include "gigasecond.h"

namespace gigasecond {

time_point advance(time_point t) {
    return t + boost::posix_time::seconds(1'000'000'000);
}

}  // namespace gigasecond

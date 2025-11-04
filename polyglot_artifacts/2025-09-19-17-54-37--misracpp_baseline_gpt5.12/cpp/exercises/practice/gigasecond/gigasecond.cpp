#include "gigasecond.h"

namespace gigasecond {

using boost::posix_time::ptime;

ptime advance(ptime tp) {
    return tp + boost::posix_time::seconds{1000000000};
}

}  // namespace gigasecond

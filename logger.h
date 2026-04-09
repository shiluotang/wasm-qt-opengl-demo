#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

namespace {
std::string timestamp_cxxstr(std::time_t t = std::time(NULL)) {
    std::vector<char> buffer(0xff);
    struct tm *tm_ptr = std::localtime(&t);
    std::strftime(&buffer[0], buffer.size(), "%Y-%m-%d %H:%M:%S %z", tm_ptr);
    return &buffer[0];
}
} // namespace anonymous

#define LOGD(x) \
    do { \
        std::ostringstream __logger_oss; \
        __logger_oss << timestamp_cxxstr() \
            << " " << __FILE__ << ":" << __LINE__ \
            << " " << x \
            << std::endl; \
        std::cout << __logger_oss.str() << std::flush; \
    } while (false)
#define DUMP(x) LOGD(#x << " = " << x)
#endif // LOGGER_H_INCLUDED

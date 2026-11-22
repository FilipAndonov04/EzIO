#include "Verify.hpp"

#include <stdexcept>

namespace ezio {

void verify(bool condition, const char* msg) {
    if (!condition) {
        throw std::runtime_error(msg);
    }
}

}
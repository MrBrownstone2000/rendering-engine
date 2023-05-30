#include "demangle.hpp"

#include <cxxabi.h>

namespace test
{
    const char* Demangle(const char* name)
    {
        return abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
    }
}

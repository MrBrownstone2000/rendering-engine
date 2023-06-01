#include "pch.hpp"
#include "debug.hpp"

#include <cxxabi.h>

namespace engine::util
{
    const char* Demangle(const char* name)
    {
        return abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
    }
}

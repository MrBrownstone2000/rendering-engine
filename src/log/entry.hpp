#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include "level.hpp"
#include "../util/stacktrace.hpp"

#include <chrono>
#include <optional>

namespace engine::log
{
    struct Entry
    {
        Level m_level;
        std::stringstream m_oss;
        const char* m_fileName;
        const char* m_functionName;
        int m_sourceLine;
        std::chrono::system_clock::time_point m_timestamp;
        std::optional<StackTrace> m_trace;

        Entry& operator=(const Entry& rhs);
        Entry(const Entry& rhs);
        Entry() = default;

    };
}

#endif

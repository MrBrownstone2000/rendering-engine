#include "textFormatter.hpp"
#include "level.hpp"
#include "entry.hpp"

#include <chrono>
#include <format>

namespace engine::log
{
    std::string TextFormatter::Format(const Entry& e) const
    {
        return std::format("@{} {{{}}} {}\n  >> at {} : in {}, line {}",
                GetLevelName(e.m_level),
                std::chrono::zoned_time(std::chrono::current_zone(), e.m_timestamp),
                e.m_message,
                e.m_fileName,
                e.m_functionName,
                e.m_sourceLine);
    }
}

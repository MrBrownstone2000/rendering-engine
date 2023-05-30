#include "textFormatter.hpp"
#include "level.hpp"
#include "entry.hpp"

namespace engine::log
{
    std::string TextFormatter::Format(const Entry& e) const
    {
        std::ostringstream oss;
        oss << std::format("@{} {{{}}} {}\n  >> at {} : in {}, line {}\n",
                GetLevelName(e.m_level),
                std::chrono::zoned_time(std::chrono::current_zone(), e.m_timestamp),
                e.m_message,
                e.m_fileName,
                e.m_functionName,
                e.m_sourceLine);
        if (e.m_trace)
            oss << e.m_trace->Print() << std::endl;
        return oss.str();
    }
}

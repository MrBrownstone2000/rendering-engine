#include "pch.hpp"
#include "textFormatter.hpp"

#include "level.hpp"
#include "entry.hpp"

namespace engine::log
{
    std::string TextFormatter::Format(const Entry& e) const
    {
        // Indent message
        std::stringstream tmp, msg;
        tmp << e.m_oss.str();
        char line[64];
        while (tmp.getline(line, 64))
        {
            msg << "  " << line << "\n"; 
        }

        // Select color
        std::string color;
        switch (e.m_level)
        {
            case Level::Fatal:
                color = c_fatal;
                break;
            case Level::Error:
                color = c_error;
                break;
            case Level::Warn:
                color = c_warn;
                break;
            case Level::Info:
                color = c_info;
                break;
            case Level::Debug:
                color = c_debug;
                break;
            default:
                color = c_normal;
        }

        std::ostringstream oss;
        oss << std::format("{}@{}{} {{{}}}: \n{}    >> at {} : in {}, line {}\n",
                color, 
                GetLevelName(e.m_level),
                c_normal,
                std::chrono::zoned_time(std::chrono::current_zone(), e.m_timestamp),
                msg.str(),
                e.m_fileName,
                e.m_functionName,
                e.m_sourceLine);
        if (e.m_trace)
            oss << e.m_trace->print() << std::endl;
        return oss.str();
    }
}

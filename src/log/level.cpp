#include "level.hpp"

namespace engine::log
{
    std::string GetLevelName(Level level)
    {
        switch (level)
        {
            case Level::Trace: return "Trace";
            case Level::Debug: return "Debug";
            case Level::Info: return "Info";
            case Level::Warn: return "Warn";
            case Level::Error: return "Error";
            case Level::Fatal: return "Fatal";
            default: return "Unknown";
        }
    }
}

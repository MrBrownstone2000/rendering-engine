#include "pch.hpp"
#include "log/level.hpp"

namespace engine::log
{
    std::string GetLevelName(Level level)
    {
        switch (level)
        {
            case Level::Verbose: return "Verbose";
            case Level::Debug: return "Debug";
            case Level::Info: return "Info";
            case Level::Warn: return "Warn";
            case Level::Error: return "Error";
            case Level::Fatal: return "Fatal";
            default: return "Unknown";
        }
    }
}

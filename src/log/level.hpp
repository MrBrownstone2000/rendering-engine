#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include <string>

namespace engine::log
{
    enum class Level
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Fatal,
    };

    std::string GetLevelName(Level level);
}

#endif

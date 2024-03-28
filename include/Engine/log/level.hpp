#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include <string>

namespace engine::log
{
    enum class Level
    {
        None,
        Fatal,  // Big error, the program should terminate immediately
        Error,  // Error, the program should try to recover
        Warn,   // Potentially undesirable state
        Info,   // Tracks the flow of the program
        Debug,  // Tracing intermediate steps of a process
        Verbose,// Same as debug, but much more detailed
    };

    std::string GetLevelName(Level level);
}

#endif

#include "pch.hpp"
#include "boot.hpp"

#include "log/log.hpp"
#include "window/window.hpp"
#include "input/input.hpp"

namespace engine
{
    void Boot()
    {
        log::Boot();
        window::Boot();
        input::Boot();
    }
}

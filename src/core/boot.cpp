#include "pch.hpp"
#include "core/boot.hpp"

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

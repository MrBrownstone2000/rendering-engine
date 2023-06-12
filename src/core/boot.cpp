#include "boot.hpp"

#include "log/log.hpp"
#include "window/window.hpp"

namespace engine
{
    void Boot()
    {
        log::Boot();
        window::Boot();
    }
}

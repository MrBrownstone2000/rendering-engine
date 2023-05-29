#include "linuxDebugDriver.hpp"

#include <iostream>

namespace engine::log
{
    LinuxDebugDriver::LinuxDebugDriver(std::unique_ptr<ITextFormatter> formatter)
        : m_formatter(std::move(formatter))
    {
    }

    void LinuxDebugDriver::Submit(const Entry& entry)
    {
        if (m_formatter)
        {
            std::cout << m_formatter->Format(entry);
        }
    }

    void LinuxDebugDriver::SetFormatter(std::unique_ptr<ITextFormatter> formatter)
    {
        m_formatter = std::move(formatter);
    }
}
 

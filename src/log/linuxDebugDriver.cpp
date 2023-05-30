#include "linuxDebugDriver.hpp"

namespace engine::log
{
    LinuxDebugDriver::LinuxDebugDriver(std::shared_ptr<ITextFormatter> formatter)
        : m_formatter(std::move(formatter))
    {
    }

    void LinuxDebugDriver::Submit(const Entry& entry)
    {
        if (m_formatter)
        {
            std::cout << m_formatter->Format(entry) << std::endl;
        }
    }

    void LinuxDebugDriver::SetFormatter(std::shared_ptr<ITextFormatter> formatter)
    {
        m_formatter = std::move(formatter);
    }
}
 

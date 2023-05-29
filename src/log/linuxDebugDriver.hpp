#ifndef __DEBUGDRIVER_HPP__
#define __DEBUGDRIVER_HPP__

#include "driver.hpp"
#include "textFormatter.hpp"
#include <memory>

namespace engine::log
{
    class LinuxDebugDriver : public ITextDriver
    {
        public:
            LinuxDebugDriver(std::unique_ptr<ITextFormatter> formatter = {});

            void Submit(const Entry& entry);
            void SetFormatter(std::unique_ptr<ITextFormatter> formatter) override;

        private:
            std::unique_ptr<ITextFormatter> m_formatter;

    };
}

#endif

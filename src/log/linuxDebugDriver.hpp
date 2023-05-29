#ifndef __DEBUGDRIVER_HPP__
#define __DEBUGDRIVER_HPP__

#include "driver.hpp"
#include "textFormatter.hpp"
#include <memory>

namespace engine::log
{
    class IDebugDriver : public ITextDriver {};

    class LinuxDebugDriver : public IDebugDriver
    {
        public:
            LinuxDebugDriver(std::shared_ptr<ITextFormatter> formatter = {});

            void Submit(const Entry& entry) override;
            void Flush() override {}
            void SetFormatter(std::shared_ptr<ITextFormatter> formatter) override;

        private:
            std::shared_ptr<ITextFormatter> m_formatter;

    };
}

#endif

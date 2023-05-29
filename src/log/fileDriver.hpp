#ifndef __FILEDRIVER_HPP__
#define __FILEDRIVER_HPP__

#include "driver.hpp"
#include "textFormatter.hpp"

#include <filesystem>
#include <memory>
#include <fstream>

namespace engine::log
{
    class IFileDriver : public ITextDriver {};

    class FileDriver : public IFileDriver
    {
        public:
            FileDriver(std::filesystem::path path, std::shared_ptr<ITextFormatter> formatter = {});

            void Submit(const Entry& entry) override;
            void Flush() override;
            void SetFormatter(std::shared_ptr<ITextFormatter> formatter) override;

        private:
            std::shared_ptr<ITextFormatter> m_formatter;
            std::ofstream m_file;

    };
}

#endif

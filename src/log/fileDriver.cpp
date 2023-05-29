#include "fileDriver.hpp"
#include <filesystem>

namespace engine::log
{
    FileDriver::FileDriver(std::filesystem::path path, std::shared_ptr<ITextFormatter> formatter)
        : m_formatter(std::move(formatter))
    {
        std::filesystem::create_directory(path.parent_path());
        m_file.open(path, m_file.out | m_file.app);
    }

    void FileDriver::Submit(const Entry& entry)
    {
        if (m_formatter)
            m_file << m_formatter->Format(entry).c_str();
    }

    void FileDriver::SetFormatter(std::shared_ptr<ITextFormatter> formatter)
    {
        m_formatter = std::move(formatter);
    }
}

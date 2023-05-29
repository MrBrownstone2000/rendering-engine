#include "exception.hpp"

namespace engine::util
{
    BufferedException::BufferedException(std::string msg)
        : m_msg(std::move(msg))
    {
    }
    
    const char* BufferedException::what() const noexcept
    {
        using namespace std::string_literals;
        // TODO: https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
        m_buffer = "["s + typeid(const_cast<BufferedException&>(*this)).name() + "]"s;
        if (!m_msg.empty())
        {
            m_buffer += ": "s;
            m_buffer += m_msg;
        }

        return m_buffer.c_str();
    }
}

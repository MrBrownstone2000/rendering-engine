#include "exception.hpp"

#include "debug.hpp"

namespace engine::util
{
    BufferedException::BufferedException(std::string msg)
        : m_msg(std::move(msg))
    {
    }
    
    const char* BufferedException::what() const noexcept
    {
        using namespace std::string_literals;
        const char* exceptionType = typeid(const_cast<BufferedException&>(*this)).name();
        m_buffer = "["s + Demangle(exceptionType) + "]"s;
        if (!m_msg.empty())
        {
            m_buffer += ": "s;
            m_buffer += m_msg;
        }

        return m_buffer.c_str();
    }
}

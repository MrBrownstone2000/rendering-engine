#include "pch.hpp"
#include "assert.hpp"

#include "log/log.hpp"
#include "log/channel.hpp"

namespace engine
{
    namespace
    {
#ifdef NDEBUG
    constexpr int defaultTraceSkip = 3;
#else
    constexpr int defaultTraceSkip = 7;
#endif
    }

    Assertion::Assertion(std::string expr, const char* file, const char* function, int line,
                         Consequence consequence) 
        : m_file(file),
        m_function(function),
        m_line(line),
        m_consequence(consequence)
    {
        m_oss << expr << "\n";
    }

    Assertion::~Assertion()
    {
        engineLog.traceSkip(defaultTraceSkip)
            .msg(m_oss.str())
            .level(m_consequence == Consequence::Terminate ? log::Level::Fatal : log::Level::Error);

        if (m_consequence == Consequence::Terminate)
        {
            log::GetDefaultChannel()->Flush();
            std::exit(1);
        }
    }

    Assertion& Assertion::msg(std::string msg)
    {
        m_oss << "  Message: " << msg << "\n";
        return *this;
    }

    void Assertion::ex()
    {
        m_consequence = Consequence::Exception;
        throw FailedAssertion{};
    }
}

#include "stacktrace.hpp"

#include <sstream>

#define BACKWARD_HAS_BFD 1
#define BACKWARD_HAS_LIBUNWIND 1
#include "backward/backward.hpp"

namespace engine::util
{
    StackTrace::StackTrace()
    {
        m_trace = std::make_unique<backward::StackTrace>();
        m_trace->load_here(64);
        m_trace->skip_n_firsts(6);
    }

    StackTrace::StackTrace(const StackTrace& src)
        : m_trace( std::make_unique<backward::StackTrace>(*src.m_trace) )
    {
    }

    StackTrace& StackTrace::operator=(const StackTrace& src)
    {
        m_trace = std::make_unique<backward::StackTrace>(*src.m_trace);
        return *this;
    }

    StackTrace::~StackTrace()
    {
    }

    std::string StackTrace::Print() const
    {
        std::ostringstream oss;
        backward::Printer printer;
        printer.print(*m_trace, oss);
        return oss.str();
    }
}

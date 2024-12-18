#include "pch.hpp"
#include "util/stacktrace.hpp"

#define BACKWARD_HAS_BFD 1
#define BACKWARD_HAS_LIBUNWIND 1
#include "backward.hpp"

namespace engine
{
    StackTrace::StackTrace(int traceSkipDepth)
    {
        m_trace = std::make_unique<backward::StackTrace>();
        m_trace->load_here(64);
        m_trace->skip_n_firsts(traceSkipDepth);
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

    std::string StackTrace::print() const
    {
        std::ostringstream oss;
        backward::Printer printer;
        printer.print(*m_trace, oss);
        return oss.str();
    }
}

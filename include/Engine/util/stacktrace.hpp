#ifndef __STACKTRACE_HPP__
#define __STACKTRACE_HPP__

#include <memory>
#include <string>

namespace backward {
    class StackTrace;
}

namespace engine
{
    class StackTrace
    {
        public:
            StackTrace(int traceSkipDepth);
            StackTrace(const StackTrace& src);
            StackTrace& operator=(const StackTrace& src);
            ~StackTrace();

            std::string print() const;

        private:
            std::unique_ptr<backward::StackTrace> m_trace;
    };
}

#endif

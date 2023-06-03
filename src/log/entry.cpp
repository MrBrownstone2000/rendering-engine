#include "pch.hpp"
#include "entry.hpp"

namespace engine::log
{
    Entry& Entry::operator=(const Entry& rhs)
    {
        m_level = rhs.m_level;
        m_oss << rhs.m_oss.str();
        m_fileName = rhs.m_fileName;
        m_functionName = rhs.m_functionName;
        m_sourceLine = rhs.m_sourceLine;
        m_timestamp = rhs.m_timestamp;
        m_trace = rhs.m_trace;
        return *this;
    }

    Entry::Entry(const Entry& rhs)
    {
        m_level = rhs.m_level;
        m_oss << rhs.m_oss.str();
        m_fileName = rhs.m_fileName;
        m_functionName = rhs.m_functionName;
        m_sourceLine = rhs.m_sourceLine;
        m_timestamp = rhs.m_timestamp;
        m_trace = rhs.m_trace;
    }
}

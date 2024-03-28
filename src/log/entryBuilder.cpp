#include "pch.hpp"
#include "log/entryBuilder.hpp"

#include "log/channel.hpp"

using namespace std::literals;

namespace engine::log
{
    EntryBuilder::EntryBuilder(const char* fileName, const char* functionName, int sourceLine)
    {
        m_level = Level::Warn;
        m_fileName = fileName;
        m_functionName = functionName;
        m_sourceLine = sourceLine;
        m_timestamp = std::chrono::system_clock::now();
    }

    EntryBuilder& EntryBuilder::msg(const std::string& msg)
    {
        m_oss << msg << "\n";
        return *this;
    }

    EntryBuilder& EntryBuilder::level(Level lvl)
    {
        m_level = lvl;
        return *this;
    }

    EntryBuilder& EntryBuilder::chan(IChannel* pChan)
    {
        m_pDest = pChan;
        return *this;
    }

    EntryBuilder& EntryBuilder::traceSkip(int depth)
    {
        m_traceSkipDepth = depth;
        return *this;
    }

    EntryBuilder::~EntryBuilder()
    {
        if (m_pDest)
        {
            if (m_level <= Level::Error)
                m_trace.emplace(m_traceSkipDepth);
            m_pDest->Submit(*this);
        }
    }

    EntryBuilder& EntryBuilder::verbose(const std::string& msg)
    {
        return level(Level::Verbose).msg(msg);
    }

    EntryBuilder& EntryBuilder::debug(const std::string& msg)
    {
        return level(Level::Debug).msg(msg);
    }
    
    EntryBuilder& EntryBuilder::info(const std::string& msg)
    {
        return level(Level::Info).msg(msg);
    }
    
    EntryBuilder& EntryBuilder::warn(const std::string& msg)
    {
        return level(Level::Warn).msg(msg);
    }
    
    EntryBuilder& EntryBuilder::error(const std::string& msg)
    {
        return level(Level::Error).msg(msg);
    }
    
    EntryBuilder& EntryBuilder::fatal(const std::string& msg)
    {
        return level(Level::Fatal).msg(msg);
    }
    
}

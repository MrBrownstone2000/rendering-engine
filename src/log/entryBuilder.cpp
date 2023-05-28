#include "entryBuilder.hpp"

#include <algorithm>
#include <chrono>

#include "channel.hpp"

using namespace std::literals;

namespace engine::log
{
    EntryBuilder::EntryBuilder(const char* fileName, const char* functionName, int sourceLine)
        : Entry{
            .m_level = Level::Error,
            .m_message = ""s,
            .m_fileName = fileName,
            .m_functionName = functionName,
            .m_sourceLine = sourceLine,
            .m_timestamp = std::chrono::system_clock::now(),        
        }
    {
    }

    EntryBuilder& EntryBuilder::msg(const std::string& msg)
    {
        m_message = std::move(msg);
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

    EntryBuilder::~EntryBuilder()
    {
        if (m_pDest)
        {
            m_pDest->Submit(*this);
        }
    }

    EntryBuilder& EntryBuilder::trace(const std::string& msg)
    {
        return level(Level::Trace).msg(msg);
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

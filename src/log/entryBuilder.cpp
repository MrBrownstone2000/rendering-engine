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
}

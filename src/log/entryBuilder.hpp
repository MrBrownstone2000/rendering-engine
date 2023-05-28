#ifndef __ENTRYBUILDER_HPP__
#define __ENTRYBUILDER_HPP__

#include <string>

#include "entry.hpp"

namespace engine::log
{
    class IChannel;

    class EntryBuilder : private Entry
    {
        public:
            EntryBuilder(const char* fileName, const char* functionName, int sourceLine);

            EntryBuilder& msg(const std::string& msg);
            EntryBuilder& level(Level lvl);
            EntryBuilder& chan(IChannel* pChan);

            EntryBuilder& trace(const std::string& msg = "");
            EntryBuilder& debug(const std::string& msg = "");
            EntryBuilder& info(const std::string& msg = "");
            EntryBuilder& warn(const std::string& msg = "");
            EntryBuilder& error(const std::string& msg = "");
            EntryBuilder& fatal(const std::string& msg = "");

            ~EntryBuilder();

        private:
            IChannel* m_pDest = nullptr;
    };
}

#endif

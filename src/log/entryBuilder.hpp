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

            ~EntryBuilder();

        private:
            IChannel* m_pDest = nullptr;
    };
}

#endif

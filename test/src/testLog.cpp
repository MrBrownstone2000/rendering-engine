#include "engine/log/level.hpp"
#include "testCore/asserts.hpp"
#include "testCore/test.hpp"

#include "engine/log/entryBuilder.hpp"
#include "engine/log/channel.hpp"
#include <iostream>

using namespace engine;

#define engineLog log::EntryBuilder(__FILE__, __FUNCTION__, __LINE__)

class MockChannel : public log::IChannel
{
    public:
        void Submit(log::Entry& entry) override
        {
            m_entry = entry;
        }
        log::Entry m_entry;
};

TEST_MODULE(Logging)
{
    TEST(FluentLogs)
    {
        MockChannel chan;
        engineLog.level(log::Level::Info).msg("HI").chan(&chan);

        test::expect(chan.m_entry.m_level == log::Level::Info);
        test::expect_eq(chan.m_entry.m_message, "HI");
        test::expect_eq(chan.m_entry.m_sourceLine, 28);
    }
}

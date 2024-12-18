#include "UnitTests/asserts.hpp"
#include "UnitTests/test.hpp"

#include "Engine/log/level.hpp"
#include "Engine/log/entryBuilder.hpp"
#include "Engine/log/channel.hpp"

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

        void Flush() override {}
        void Attach(std::shared_ptr<log::IDriver>) override {}
        void Attach(std::shared_ptr<log::IPolicy>) override {}
        log::Entry m_entry;
};

template<>
inline std::string test::ToString<log::Level>(const log::Level& lvl)
{
    return log::GetLevelName(lvl);
}

TEST_MODULE(LogEntry)
{
    TEST(FluentLogs)
    {
        MockChannel chan;
        engineLog.level(log::Level::Info).msg("HI").chan(&chan);

        test::expect_eq(chan.m_entry.m_level, log::Level::Info);
        test::expect_eq(chan.m_entry.m_oss.str(), "HI\n");
        test::expect_eq(chan.m_entry.m_sourceLine, __LINE__ - 4);
    }

    TEST(SimplifiedFluentLogs)
    {
        MockChannel chan;
        engineLog.info("HI").chan(&chan);

        test::expect_eq(chan.m_entry.m_level, log::Level::Info);
        test::expect_eq(chan.m_entry.m_oss.str(), "HI\n");
        test::expect_eq(chan.m_entry.m_sourceLine, __LINE__ - 4);
    }
}

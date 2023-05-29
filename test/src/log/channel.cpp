#include "testCore/asserts.hpp"
#include "testCore/test.hpp"

#include "engine/log/level.hpp"
#include "engine/log/entryBuilder.hpp"
#include "engine/log/channel.hpp"
#include "engine/log/driver.hpp"
#include "engine/log/severityLevelPolicy.hpp"

#include <iostream>
#include <memory>

using namespace engine;

#define engineLog log::EntryBuilder(__FILE__, __FUNCTION__, __LINE__)

class MockDriver : public log::IDriver
{
    public:
        void Submit(const log::Entry& entry) override
        {
            m_entry = entry;
        }

        log::Entry m_entry;
};

template<>
inline std::string ToString<log::Level>(const log::Level& lvl)
{
    return log::GetLevelName(lvl);
}

TEST_MODULE(LogChannel)
{
    TEST(Forwarding)
    {
        log::Channel chan;
        auto d1 = std::make_shared<MockDriver>();
        auto d2 = std::make_shared<MockDriver>();
        chan.Attach(d1);
        chan.Attach(d2);

        engineLog.info("HI").chan(&chan);

        test::expect_eq(d1->m_entry.m_level, log::Level::Info);
        test::expect_eq(d1->m_entry.m_message, "HI");
        test::expect_eq(d1->m_entry.m_sourceLine, __LINE__ - 4);

        test::expect_eq(d2->m_entry.m_level, log::Level::Info);
        test::expect_eq(d2->m_entry.m_message, "HI");
        test::expect_eq(d2->m_entry.m_sourceLine, __LINE__ - 8);
    }

    TEST(SeverityLevelPolicy)
    {
        log::Channel chan;
        auto d = std::make_shared<MockDriver>();
        chan.Attach(d);
        chan.Attach(std::make_unique<log::SeverityLevelPolicy>(log::Level::Info));

        engineLog.info("HI").chan(&chan);

        test::expect_eq(d->m_entry.m_level, log::Level::Info);
        test::expect_eq(d->m_entry.m_message, "HI");
        test::expect_eq(d->m_entry.m_sourceLine, __LINE__ - 4);

        engineLog.debug("Hello").chan(&chan);

        test::expect_eq(d->m_entry.m_level, log::Level::Info);
        test::expect_eq(d->m_entry.m_message, "HI");
        test::expect_eq(d->m_entry.m_sourceLine, __LINE__ - 10);
    }
}


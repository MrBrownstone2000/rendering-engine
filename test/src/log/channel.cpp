#include "UnitTests/asserts.hpp"
#include "UnitTests/test.hpp"

#include "Engine/log/level.hpp"
#include "Engine/log/entryBuilder.hpp"
#include "Engine/log/channel.hpp"
#include "Engine/log/driver.hpp"
#include "Engine/log/severityLevelPolicy.hpp"

using namespace engine;

#define engineLog log::EntryBuilder(__FILE__, __FUNCTION__, __LINE__)

class MockDriver : public log::IDriver
{
    public:
        void Submit(const log::Entry& entry) override
        {
            m_entry = entry;
        }
        void Flush() override {}

        log::Entry m_entry;
};

template<>
inline std::string test::ToString<log::Level>(const log::Level& lvl)
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
        test::expect_eq(d1->m_entry.m_oss.str(), "HI\n");
        test::expect_eq(d1->m_entry.m_sourceLine, __LINE__ - 4);

        test::expect_eq(d2->m_entry.m_level, log::Level::Info);
        test::expect_eq(d2->m_entry.m_oss.str(), "HI\n");
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
        test::expect_eq(d->m_entry.m_oss.str(), "HI\n");
        test::expect_eq(d->m_entry.m_sourceLine, __LINE__ - 4);

        engineLog.debug("Hello").chan(&chan);

        test::expect_eq(d->m_entry.m_level, log::Level::Info);
        test::expect_eq(d->m_entry.m_oss.str(), "HI\n");
        test::expect_eq(d->m_entry.m_sourceLine, __LINE__ - 10);
    }
}


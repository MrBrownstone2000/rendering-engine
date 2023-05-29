#include "testCore/asserts.hpp"
#include "testCore/test.hpp"

#include "engine/log/level.hpp"
#include "engine/log/entry.hpp"
#include "engine/log/textFormatter.hpp"


#include <bits/chrono.h>
#include <chrono>
#include <iostream>

using namespace engine;

TEST_MODULE(LogFormatter)
{
    TEST(Format)
    {
        log::Entry entry {
            .m_level = log::Level::Info,
            .m_message = "Hi",
            .m_fileName = __FILE__,
            .m_functionName = __FUNCTION__,
            .m_sourceLine = __LINE__,
            .m_timestamp = std::chrono::system_clock::time_point{
                std::chrono::days{ 10000 }
            }
        };
        
        test::expect_eq("@Info {1997-05-19 02:00:00.000000000} Hi\n  >> at src/log/formatter.cpp : in test_Format, line 24",
                log::TextFormatter().Format(entry));
    }
}



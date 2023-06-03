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
        log::Entry entry;
        entry.m_level = log::Level::Info;
        entry.m_fileName = __FILE__;
        entry.m_functionName = __FUNCTION__;
        entry.m_sourceLine = __LINE__;
        entry.m_timestamp = std::chrono::system_clock::time_point{
                std::chrono::days{ 10000 }
            };

        entry.m_oss << "Hi";
        
        test::expect_eq("@Info {1997-05-19 02:00:00.000000000}: \n  Hi\n  >> at src/log/formatter.cpp : in test_Format, line 23\n",
                log::TextFormatter().Format(entry));
    }
}



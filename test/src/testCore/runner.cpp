#include "runner.hpp"

#include "testCore/factory.hpp"
#include "testCore/base.hpp"
#include "testCore/asserts.hpp"

#include <exception>
#include <iostream>

namespace test
{
    namespace {
        char green[] = "\033[1;38;5;46m";
        char redBold[] = "\033[1;38;5;196m";
        char red[] = "\033[38;5;196m";
        char underlineBold[] = "\033[1;4m";
        char normal[] = "\033[0m";
    }
    bool Run()
    {
        int fails = 0;
        for (const auto& m : TestFactory::GetModules())
        {
            std::cout << std::endl << underlineBold << "Testing Module: " << m.first << normal << std::endl;
            for (auto gen : m.second)
            {
                TestBase* test = gen();
                if (!test->Run())
                    ++fails;
                delete test;
            }
        }
        if (!fails)
        {
            std::cout << green << "All tests Passed" << std::endl;
            return true;
        }
        else
        {
            std::cout << redBold << "ERROR: " << fails << " test(s) Failed" << std::endl;
            return false;
        }
    }

    bool RunIndividualTest(const std::string& name, std::function<void()> testFunction)
    {
        try {
            testFunction();
        } catch(const test::assert_failed& e)
        {

            std::cout << "\t" << name << ": " << redBold << "FAIL" << normal << std::endl;
            std::cout << red << "Assertion Failed: " << normal << std::endl;
            std::cout << e.what() << std::endl;
            return false;
        }
        catch(const std::exception& e)
        {
            std::cout << "\t" << name << ": " << redBold << "FAIL" << normal << std::endl;
            std::cout << red << "Caught exception: " << normal << std::endl;
            std::cout << e.what() << std::endl;
            return false;
        }
        catch(...)
        {

            std::cout << "\t" << name << ": " << redBold << "FAIL" << normal << std::endl;
            std::cout << red << "Caught unknown exception" << normal << std::endl;
            return false;
        }
        std::cout << "\t" << name << ": " << green << "OK" << normal << std::endl;
        return true;
    }
}

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
        char white[] = "\033[0m";
    }
    void Run()
    {
        for (const auto& m : TestFactory::GetModules())
        {
            std::cout << "Testing Module: " << m.first << std::endl;
            for (auto gen : m.second)
            {
                TestBase* test = gen();
                test->Run();
                delete test;
            }
        }
    }

    bool RunIndividualTest(const std::string& name, std::function<void()> testFunction)
    {
        try {
            testFunction();
        } catch(const test::assert_failed& e)
        {

            std::cout << "\t" << name << ": " << redBold << "FAIL" << white << std::endl;
            std::cout << "\t\t" << red << "Assertion Failed" << white << std::endl;
            return false;
        }
        catch(const std::exception& e)
        {
            std::cout << "\t" << name << ": " << redBold << "FAIL" << white << std::endl;
            std::cout << "\t\t" << red << "Caught exception: " << white << e.what() << std::endl;
            return false;
        }
        catch(...)
        {

            std::cout << "\t" << name << ": " << redBold << "FAIL" << white << std::endl;
            std::cout << "\t\t" << red << "Caught unknown exception" << white << std::endl;
            return false;
        }
        std::cout << "\t" << name << ": " << green << "OK" << white << std::endl;
        return true;
    }
}

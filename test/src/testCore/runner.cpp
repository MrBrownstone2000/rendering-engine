#include "runner.hpp"

#include "testCore/factory.hpp"
#include "testCore/base.hpp"

#include <iostream>

namespace test
{
    void Run()
    {
        for (const auto& m : TestFactory::GetModules())
        {
            std::cout << "Module: " << m.first << std::endl;
            for (auto gen : m.second)
            {
                TestBase* test = gen();
                test->Run();
                delete test;
            }
        }
    }

    void RunIndividualTest(const std::string& module, const std::string& name, std::function<void()> testFunction)
    {
        std::cout << "M: " << module << ", N: " << name << std::endl;
        testFunction();
    }
}

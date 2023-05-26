#include "runner.hpp"

void TestAll()
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

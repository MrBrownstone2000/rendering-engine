#include "testCore/factory.hpp"
#include "testCore/testBase.hpp"

#include <iostream>

int main()
{
    std::cout << "Running tests..." << std::endl;
    size_t nb = TestFactory::GetCount();
    for (size_t i = 0; i < nb; ++i)
    {
        TestBase* test = TestFactory::Create(i);
        test->Run();
        delete test;
    }
    return 0;
}

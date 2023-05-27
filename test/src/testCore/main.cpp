#include "testCore/runner.hpp"

#include <iostream>

int main()
{
    std::cout << "===== Running Unit Tests =====" << std::endl;
    test::Run();
    return 0;
}

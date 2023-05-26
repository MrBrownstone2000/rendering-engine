#include "testCore/runner.hpp"

#include <iostream>

int main()
{
    std::cout << "Running tests..." << std::endl;
    test::Run();
    return 0;
}

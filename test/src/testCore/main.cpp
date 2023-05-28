#include "testCore/runner.hpp"

#include <iostream>

int main()
{
    if (test::Run())
        return 0;
    return 1;
}

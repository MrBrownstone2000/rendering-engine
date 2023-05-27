#ifndef __RUNNER_HPP__
#define __RUNNER_HPP__

#include <functional>
#include <string>

namespace test
{
    // Run all tests from all modules
    void Run();

    // Run a test from a module
    bool RunIndividualTest(const std::string& name, std::function<void()> testFunction);
}

#endif

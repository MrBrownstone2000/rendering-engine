#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <iostream>

// Basic auto registering factory framework
// Inspired by https://github.com/gsuberland/autoregistering-cpp-factory
namespace test
{
    class TestBase;

    // Cannot use std::function, because it has no operator==...
    using Generator = TestBase*(*)();
    using Map = std::map<std::string, std::vector<Generator>>;

    // Static Factory, responsible for storing Test Classes creation functions
    class TestFactory
    {
    public:
        TestFactory() = delete;

        static bool Register(Generator gen, const std::string& module)
        {
            auto& generators = GetModules()[module];

            auto it = std::find(generators.begin(), generators.end(), gen);
            if (it == generators.end())
            {
                generators.push_back(gen);
                return true;
            }
            return false;
        }

        static Map& GetModules()
        {
            static Map modules;
            return modules;
        }
    };

    // Makes it possible to register the Test Class, using CRTP
    template <const char* Module, class CTest> // CTest is derived from TestsBasec
    class RegisteredInFactory
    {
    protected:
        static bool _FACTORY_INIT;
    };

    template<const char* Module, class CTest>
    bool RegisteredInFactory<Module, CTest>::_FACTORY_INIT =
        TestFactory::Register(CTest::CreateInstance, Module);
}

// Access _FACTORY_INIT in Test Class constructor
// => runs Factory::Register()
#define TEST_FACTORY_INIT (void)_FACTORY_INIT

#endif

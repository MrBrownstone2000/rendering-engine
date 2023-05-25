#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

// Basic auto registering factory framework
// Inspired by https://github.com/gsuberland/autoregistering-cpp-factory

class TestBase;

// Cannot use std::function, because it has no operator==...
using Generator = TestBase*(*)();

// Static Factory, responsible for storing Test Classes creation functions
class TestFactory
{
public:
    TestFactory() = delete;

    static bool Register(Generator gen)
    {
        auto it = std::find(GetGenerator().begin(), GetGenerator().end(), gen);
        if (it == GetGenerator().end())
        {
            GetGenerator().push_back(gen);
            return true;
        }
        return false;
    }

    static TestBase* Create(size_t index)
    {
        assert(index < GetGenerator().size());
        return GetGenerator()[index]();
    }

    static size_t GetCount() { return GetGenerator().size(); }
    
private:
    static std::vector<Generator>& GetGenerator()
    {
        static std::vector<Generator> generators;
        return generators;
    }
};

// Makes it possible to register the Test Class, using CRTP
template <class CTest> // CTest is derived from TestsBasec
class RegisteredInFactory
{
protected:
    static bool _FACTORY_INIT;
};

template<class CTest>
bool RegisteredInFactory<CTest>::_FACTORY_INIT =
    TestFactory::Register(CTest::CreateInstance);

// Access _FACTORY_INIT in Test Class constructor
// => runs Factory::Register()
#define FACTORY_INIT (void)_FACTORY_INIT

#endif

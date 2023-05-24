#ifndef __TESTSINGLETON_HPP__
#define __TESTSINGLETON_HPP__

#include "test.hpp"
 
#include "engine/ioc/container.hpp"
#include "engine/ioc/singleton.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>

using namespace engine;

class TestSingleton : public Test
{
    public:
        bool init() override
        {
            return true;
        }

        void run() override
        {
            // PolymorphicResolveDirect
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();
                pSing = std::make_unique<ioc::Singletons>();

                pSing->Register<Base>([] { return std::make_shared<Derived>(); });
                assert(69 == pSing->Resolve<Base>()->test());
            }

            // PolymorphicResolveIndirect
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();
                pSing = std::make_unique<ioc::Singletons>();

                pIoC->Register<Base>([] { return std::make_shared<Derived>(); });
                pSing->Register<Base>([this] { return pIoC->Resolve<Base>(); });
                assert(69 == pSing->Resolve<Base>()->test());
            }

            // SimpleResolveFailure
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();
                pSing = std::make_unique<ioc::Singletons>();

                bool hasException = false;
                try
                {
                    pSing->Resolve<Base>()->test();
                }
                catch(std::runtime_error&)
                {
                    hasException = true;
                }
                assert(hasException);
            }

            // DependantResolve
            {
                // Init test method
                pIoC = std::make_unique<ioc::Container>();
                pSing = std::make_unique<ioc::Singletons>();

                pSing->Register<ParameterizedClass>([](){
                    return std::make_shared<ParameterizedClass>(ParameterizedClass::IocParams{ .s = "first" });
                });

                auto pFirst = pSing->Resolve<ParameterizedClass>();
                auto pSecond = pSing->Resolve<ParameterizedClass>();

                assert(pFirst->s == "first");
                assert(pSecond->s == "first");

                pFirst->s = "second";

                assert(pFirst->s == "second");
                assert(pSecond->s == "second");
            }
        }

        void shutdown() override
        {
        }
    private:
        std::unique_ptr<ioc::Container> pIoC;
        std::unique_ptr<ioc::Singletons> pSing;

    private:

    class Base
    {
        public:
            virtual int test() { return 42; }
            virtual ~Base() {}
    };

    class Derived : public Base
    {
        public:
            int test() override { return 69; }
    };

    struct ParameterizedClass
    {
        struct IocParams
        {
            std::string s;
        };
        ParameterizedClass(IocParams params) : s{ std::move(params.s) } {}
        std::string s;
    };

    struct Dependant
    {
        std::shared_ptr<Base> pDependency;
        Dependant(std::shared_ptr<Base> pDependency_in) : pDependency{ std::move(pDependency_in) } {}
    };

};

#endif
